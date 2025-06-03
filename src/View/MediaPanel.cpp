#include "MediaPanel.h"
#include "SetTypeAndIconOfMediaWidgetVisitor.h"
#include <stdexcept>

namespace View
{

    MediaPanel::MediaPanel(const std::vector<Media::AbstractMedia *> &medias, QWidget *parent)
        : QWidget(parent), mainLayout(nullptr), searchLayout(nullptr), searchBar(nullptr),
          returnBackButton(nullptr), mediaLayout(nullptr), scrollArea(nullptr), mediaWidgetContainer(nullptr),
          addMediaButton(nullptr), addWindow(nullptr), mediaWidget(nullptr)
    {
        createPanel(medias);
    }

    void MediaPanel::createPanel(const std::vector<Media::AbstractMedia *> &medias)
    {
        // Remove all dynamically allocated objects from before
        delete searchBar;
        delete returnBackButton;
        for (MediaWidget *widget : mediaWidgets)
        {
            delete widget;
        }
        mediaWidgets.clear();
        delete addMediaButton;
        delete addWindow;
        delete mediaLayout;
        delete mediaWidgetContainer;
        delete scrollArea;
        delete searchLayout;
        delete mainLayout;

        // Set pointers a nullptr
        searchBar = nullptr;
        returnBackButton = nullptr; 
        addMediaButton = nullptr;
        addWindow = nullptr;
        mediaLayout = nullptr;
        mediaWidgetContainer = nullptr;
        scrollArea = nullptr;
        searchLayout = nullptr;
        mainLayout = nullptr;

        // Search bar

        searchBar = new QLineEdit(this);
        searchBar->setEnabled(false);
        searchBar->setPlaceholderText("Search");
        searchBar->setFixedHeight(43);

        returnBackButton = new QPushButton(QIcon(":/Assets/Icons/back.png"), "", this);
        returnBackButton->setShortcut(Qt::Key_Escape);
        returnBackButton->setObjectName("backButton");

        returnBackButton->setEnabled(false);

        searchLayout = new QHBoxLayout();
        searchLayout->addWidget(searchBar);
        searchLayout->addWidget(returnBackButton);

        // Il vero e proprio pannello dei media

        scrollArea = new QScrollArea(this);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        if (!medias.empty())
        {
            mediaLayout = new QGridLayout();
            mediaLayout->setSpacing(30);

            int row = 0;
            int column = 0;
            const int maxColumns = 3; // Maximum number of columns before wrapping to the next row

            for (Media::AbstractMedia *media : medias)
            {
                mediaWidget = new MediaWidget(this);
                mediaWidget->setName(QString::fromStdString(media->getTitle()));
                mediaWidget->setId(media->getId());
                if (typeid(*media) == typeid(Media::Article))
                {
                    mediaWidget->setData(static_cast<Media::Article *>(media)->getPageCount(), " pg");
                }
                else if (typeid(*media) == typeid(Media::Audio))
                {
                    mediaWidget->setData(static_cast<Media::Audio *>(media)->getDuration(), " sec");
                }
                else if (typeid(*media) == typeid(Media::Book))
                {
                    mediaWidget->setData(static_cast<Media::Book *>(media)->getPageCount(), " pg");
                }
                else if (typeid(*media) == typeid(Media::Film))
                {
                    mediaWidget->setData(static_cast<Media::Film *>(media)->getDuration(), " min");
                }

                SetTypeAndIconOfMediaWidgetVisitor setTypeAndIconOfMediaWidgetVisitor(this);
                media->accept(setTypeAndIconOfMediaWidgetVisitor);

                mediaLayout->addWidget(mediaWidget, row, column); // Add widget to grid layout
                mediaWidgets.push_back(mediaWidget);              // Add widget to list

                // Update row and column
                column++;
                if (column >= maxColumns)
                {
                    column = 0;
                    row++;
                }

                mediaWidget = nullptr;
            }

            mediaWidgetContainer = new QWidget();
            mediaWidgetContainer->setObjectName("mediaWidgetContainer");
            mediaWidgetContainer->setLayout(mediaLayout);
            scrollArea->setWidget(mediaWidgetContainer);
        }

        // Add button

        addMediaButton = new QPushButton(QIcon(":/Assets/Icons/add.png"), "", this);
        addMediaButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));

        mainLayout = new QVBoxLayout(this);

        mainLayout->addLayout(searchLayout);
        mainLayout->addWidget(scrollArea);
        mainLayout->addWidget(addMediaButton);

        connect(returnBackButton, &QPushButton::clicked, this, &MediaPanel::returnBackFromSearch);
        connect(addMediaButton, &QPushButton::clicked, this, &MediaPanel::addMediaSlot);

        connect(searchBar, &QLineEdit::textChanged, this, &MediaPanel::afterTextChangedSlot);

        for (MediaWidget *mediaWidget : mediaWidgets)
        {
            connect(mediaWidget, &MediaWidget::selected, this, &MediaPanel::handleMediaWidgetSelected);
        }
    }

    // Update the search results
    void MediaPanel::updateSearchResults(const std::vector<Media::AbstractMedia *> &medias)
    {
        // Clear previous widgets and layout
        for (MediaWidget *widget : mediaWidgets)
        {
            delete widget;
        }
        mediaWidgets.clear();

        delete mediaLayout;
        delete mediaWidgetContainer;
        mediaLayout = nullptr;
        mediaWidgetContainer = nullptr;

        QString searchString = searchBar->text();

        // Map to associate each media with the length of the longest common substring
        QMultiMap<int, Media::AbstractMedia *> mediaMatchLengthMap;

        // Calculate the length of the longest common substring for each media
        for (auto it = medias.rbegin(); it != medias.rend(); ++it)
        {
            Media::AbstractMedia *media = *it;
            int maxLength = 0;
            QString mediaName = QString::fromStdString(media->getTitle());
            QString mediaId = QString::number(media->getId());
            QString mediaType;
            if (dynamic_cast<Media::Article *>(media))
                mediaType = "Article";
            else if (dynamic_cast<Media::Audio *>(media))
                mediaType = "Audio";
            else if (dynamic_cast<Media::Book *>(media))
                mediaType = "Book";
            else
                mediaType = "Film";

            // Calculate the length of the longest common substring between the name, ID, and type of the media
            int nameMatchLength = findLengthOfLongestCommonSubstring(searchString, mediaName);
            int idMatchLength = findLengthOfLongestCommonSubstring(searchString, mediaId);
            int typeMatchLength = findLengthOfLongestCommonSubstring(searchString, mediaType);

            int matchLength = qMax(nameMatchLength, qMax(idMatchLength, typeMatchLength));

            if (searchString.length() == 1)
            {
                if (matchLength > maxLength)
                    maxLength = matchLength;
                if (maxLength != 0)
                    mediaMatchLengthMap.insert(maxLength, media);
            }
            else
            {
                if (matchLength >= (searchString.length() / 2) && matchLength > maxLength)
                    maxLength = matchLength;
                if (maxLength >= (searchString.length() / 2))
                    mediaMatchLengthMap.insert(maxLength, media);
            }
        }

        // Get the keys of the map multiplier
        QList<int> sortedKeys = mediaMatchLengthMap.keys();

        // Remove duplicates from the list
        sortedKeys.erase(std::unique(sortedKeys.begin(), sortedKeys.end()), sortedKeys.end());

        // Sort the keys of the map multiplier in ascending order based on the length of the longest common substring
        std::sort(sortedKeys.begin(), sortedKeys.end());

        mediaLayout = new QGridLayout(); // Use QGridLayout instead of QFlowLayout

        int row = 0;
        int column = 0;
        const int maxColumns = 3; // Maximum number of columns before wrapping to the next row

        // Add medias to the scroll area layout based on the ordering
        for (int i = sortedKeys.size() - 1; i >= 0; --i)
        {
            // Get the medias corresponding to the key, which may be more than one because I'm using a QMultiMap
            std::vector<Media::AbstractMedia *> mediasForKey = getMediasForKey(mediaMatchLengthMap, sortedKeys[i]);

            for (Media::AbstractMedia *media : mediasForKey)
            {
                // Create a widget to display the media
                mediaWidget = new MediaWidget(this);

                mediaWidget->setName(QString::fromStdString(media->getTitle()));
                mediaWidget->setId(media->getId());
                if (typeid(*media) == typeid(Media::Article))
                {
                    mediaWidget->setData(static_cast<Media::Article *>(media)->getPageCount(), " pg");
                }
                else if (typeid(*media) == typeid(Media::Audio))
                {
                    mediaWidget->setData(static_cast<Media::Audio *>(media)->getDuration(), " sec");
                }
                else if (typeid(*media) == typeid(Media::Book))
                {
                    mediaWidget->setData(static_cast<Media::Book *>(media)->getPageCount(), " pg");
                }
                else if (typeid(*media) == typeid(Media::Film))
                {
                    mediaWidget->setData(static_cast<Media::Film *>(media)->getDuration(), " min");
                }

                SetTypeAndIconOfMediaWidgetVisitor setTypeAndIconOfMediaWidgetVisitor(this);
                media->accept(setTypeAndIconOfMediaWidgetVisitor);

                mediaLayout->addWidget(mediaWidget, row, column); // Add widget to grid layout
                mediaWidgets.push_back(mediaWidget);              // Add to MediaWidgets vector

                // Update row and column
                column++;
                if (column >= maxColumns)
                {
                    column = 0;
                    row++;
                }

                // Now that it made a shallow copy, mediaWidget can "cut its string"
                mediaWidget = nullptr;
            }
        }

        mediaWidgetContainer = new QWidget();
        mediaWidgetContainer->setObjectName("mediaWidgetContainer");
        mediaWidgetContainer->setLayout(mediaLayout);
        scrollArea->setWidget(mediaWidgetContainer);

        // Connect signals and slots for the newly added mediaWidgets
        for (MediaWidget *mediaWidget : mediaWidgets)
        {
            connect(mediaWidget, &MediaWidget::selected, this, &MediaPanel::handleMediaWidgetSelected);
        }

        emit searchResults(mediaWidgets);
    }

    // Finds the length of the longest common substring between two given strings
    // Time complexity: O(m*n)
    // Space complexity: O(m*n)
    int MediaPanel::findLengthOfLongestCommonSubstring(const QString &str1, const QString &str2)
    {
        // Initialize variables
        int m = str1.length();
        int n = str2.length();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        int maxLength = 0;

        // Calculate lengths of longest common substrings
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (str1[i - 1] == str2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    maxLength = std::max(maxLength, dp[i][j]);
                }
            }
        }

        return maxLength;
    }

    // Extract all medias associated with a specific key from the multi-map
    std::vector<Media::AbstractMedia *> MediaPanel::getMediasForKey(const QMultiMap<int, Media::AbstractMedia *> &mediaMap, int key)
    {
        std::vector<Media::AbstractMedia *> result;

        // Get an interval of iterators that covers all values associated with the specified key
        auto range = mediaMap.equal_range(key);

        // Iterate through the elements in the interval
        for (auto it = range.first; it != range.second; ++it)
        {
            result.push_back(it.value()); // Add the media to the vector
        }

        return result;
    }

    // Set the icon of the media widget
    void MediaPanel::setIconOfMediaWidget(const QIcon &icon)
    {
        mediaWidget->setIcon(icon);
    }

    // Handle mouse press event
    void MediaPanel::mousePressEvent(QMouseEvent *event)
    {
        // Enable the search bar if the mouse click is within it
        if (searchBar->rect().contains(event->pos()))
        {
            searchBar->setEnabled(true);
        }
        else
        {
            // Propagate the event to the parent widget
            QWidget::mousePressEvent(event);
        }
    }

    // Slot for afterTextChanged signal
    void MediaPanel::afterTextChangedSlot()
    {
        emit areThereAnyMedias();
    }

    // Handle afterTextChanged signal
    void MediaPanel::afterTextChanged(const bool &thereAreMedias)
    {
        QString text = searchBar->text();

        if (thereAreMedias)
        {
            search();
        }
    }

    // Handle the 'Search' button click or Enter key press
    void MediaPanel::search()
    {
        returnBackButton->setEnabled(true);

        QString searchString = searchBar->text();

        emit searchSignal();
    }

    // Handle the 'Return Back' button click
    void MediaPanel::returnBackFromSearch()
    {
        searchBar->clear();
        returnBackButton->setEnabled(false);

        emit returnBackSignal();
    }

    // Handle the selection of a MediaWidget
    void MediaPanel::handleMediaWidgetSelected(MediaWidget *sender)
    {
        if (!sender)
        {
            qWarning() << "MediaWidget pointer is null!";
            return;
        }

        try
        {
            emit mediaSelected(sender->getId());
        }
        catch (const std::exception &e)
        {
            return;
        }
    }

    // Slot for handling the 'Add Media' button click
    void MediaPanel::addMediaSlot()
    {
        // Create a new add media dialog window
        addWindow = new AddMediaDialogueWindow();

        // Connect signals and slots
        connect(addWindow, &AddMediaDialogueWindow::createAndAddSignal, this, &MediaPanel::createAndAddMediaSlot);
        connect(this, &MediaPanel::finallyYouCanCreateAndAddMedia, addWindow, &AddMediaDialogueWindow::createAndAddMedia);
        connect(addWindow, &AddMediaDialogueWindow::mediaAdded, this, &MediaPanel::handleMediaAdded);

        // Show the dialog
        addWindow->exec();
    }

    // Slot for handling the create and add media signal
    void MediaPanel::createAndAddMediaSlot()
    {
        emit createAndAddMediaSignal();
    }

    // Slot for handling the name and ID uniqueness check signal
    void MediaPanel::youCanCheckIfNameAndIDAreUnique(const std::vector<Media::AbstractMedia *> &medias)
    {
        emit finallyYouCanCreateAndAddMedia(medias);
    }

    // Slot for handling the media added signal
    void MediaPanel::handleMediaAdded(Media::AbstractMedia *media)
    {
        // Refresh the media panel to show the new media
        emit mediaAdded(media);
    }

    // Update the name of a media widget
    void MediaPanel::modifyOneName(const std::string &previousName, const std::string &newName)
    {
        // Iterate through all media widgets
        for (MediaWidget *mediaWidget : mediaWidgets)
        {
            // If the current media widget name matches the previous name, update it with the new name
            if (mediaWidget->getName() == previousName)
            {
                mediaWidget->setName(QString::fromStdString(newName));
                return;
            }
        }
    }

    // Set the colors of the media widgets
    void MediaPanel::setColors(Media::AbstractMedia *previousMedia, Media::AbstractMedia *newMedia)
    {
        try
        {
            if (previousMedia != nullptr)
            { // If this is the first media created, no predecessor is selected
                // Search for the previousMedia in the mediaWidgets
                for (MediaWidget *widget : mediaWidgets)
                {
                    if (widget->getId() == previousMedia->getId())
                    {
                        widget->setBackGroundColor(QColor("#FFFFFF")); // Set the widget border color to white
                        break;
                    }
                }
            }

            // Search for the newMedia in the mediaWidgets
            for (MediaWidget *widget : mediaWidgets)
            {
                if (widget->getId() == newMedia->getId())
                {
                    widget->setBackGroundColor(QColor("#3E0040")); // Set the backgroundWidget border color to dark purple
                    break;
                }
            }
        }
        catch (const std::exception &e)
        { // If the ID can't be read, no color is changed
            return;
        }
    }

    // Destructor that deletes all dynamically allocated objects
    MediaPanel::~MediaPanel()
    {
        delete searchBar;
        // delete goButton;
        delete returnBackButton;

        for (MediaWidget *widget : mediaWidgets)
        {
            delete widget;
        }
        mediaWidgets.clear();

        delete addMediaButton;

        delete addWindow;

        delete mediaLayout;
        delete mediaWidgetContainer;
        delete scrollArea;
        delete searchLayout;
        delete mainLayout;
    }

}

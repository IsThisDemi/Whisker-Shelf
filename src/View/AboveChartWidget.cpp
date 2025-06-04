// The AboveChartWidget class is a widget that displays above a chart all the
// necessary information about the media.

#include "AboveChartWidget.h"
#include "AboveChartLabelsCreatorVisitor.h"
namespace View
{

    // Constructor that initializes the widget and creates the grey panel.
    AboveChartWidget::AboveChartWidget(QWidget *parent) : QWidget(parent),
                                                          greyPanel(nullptr),
                                                          layout(nullptr),
                                                          mediaTitleLabel(nullptr),
                                                          mediaIDLabel(nullptr),
                                                          mediaDescriptionLabel(nullptr),
                                                          mediaAuthorLabel(nullptr),
                                                          mediaValue1Label(nullptr),
                                                          mediaValue2Label(nullptr),
                                                          mediaValue3Label(nullptr),
                                                          mediaValue4Label(nullptr),
                                                          simulateButton(nullptr),
                                                          modifyButton(nullptr),
                                                          deleteButton(nullptr),
                                                          modifyWindow(nullptr)
    {
        createGreyPanel();
    }

    // Function that creates the grey panel.
    // This function removes all the dynamically allocated objects from before,
    // sets them to nullptr and then creates a new grey panel.
    void AboveChartWidget::createGreyPanel()
    {
        // Remove all dynamically allocated objects from before.
        delete greyPanel;
        delete mediaTitleLabel;
        delete mediaIDLabel;
        delete mediaDescriptionLabel;
        delete mediaAuthorLabel;
        delete mediaValue1Label;
        delete mediaValue2Label;
        delete mediaValue3Label;
        delete mediaValue4Label;
        delete simulateButton;
        delete modifyButton;
        delete deleteButton;
        delete modifyWindow;
        delete layout;

        // Set all pointers to nullptr.
        greyPanel = nullptr;
        mediaTitleLabel = nullptr;
        mediaIDLabel = nullptr;
        mediaDescriptionLabel = nullptr;
        mediaAuthorLabel = nullptr;
        mediaValue1Label = nullptr;
        mediaValue2Label = nullptr;
        mediaValue3Label = nullptr;
        mediaValue4Label = nullptr;
        simulateButton = nullptr;
        modifyButton = nullptr;
        deleteButton = nullptr;
        modifyWindow = nullptr;
        layout = nullptr;

        // Create the grey panel.
        greyPanel = new QFrame(this);
        greyPanel->setObjectName("emptyPanel");
        greyPanel->setGeometry(0, 0, 714, 85);
        greyPanel->show();
    }

    // Creates the above chart for a given sensor.

    void AboveChartWidget::createAboveChartForMedia(Media::AbstractMedia *media)
    {
        // Remove dynamically allocated objects from before.
        delete greyPanel;
        delete mediaTitleLabel;
        delete mediaIDLabel;
        delete mediaDescriptionLabel;
        delete mediaAuthorLabel;
        delete mediaValue1Label;
        delete mediaValue2Label;
        delete mediaValue3Label;
        delete mediaValue4Label;
        delete simulateButton;
        delete modifyButton;
        delete deleteButton;
        delete modifyWindow;
        delete layout;

        // Set pointers to nullptr.
        greyPanel = nullptr;
        mediaTitleLabel = nullptr;
        mediaIDLabel = nullptr;
        mediaDescriptionLabel = nullptr;
        mediaAuthorLabel = nullptr;
        mediaValue1Label = nullptr;
        mediaValue2Label = nullptr;
        mediaValue3Label = nullptr;
        mediaValue4Label = nullptr;
        simulateButton = nullptr;
        modifyButton = nullptr;
        deleteButton = nullptr;
        modifyWindow = nullptr;
        layout = nullptr;

        // Create visual buttons.
        simulateButton = new QPushButton(QIcon(":/Assets/Icons/play.png"), tr("Simulate"), this);
        modifyButton = new QPushButton(QIcon(":/Assets/Icons/edit.png"), tr("Edit"), this);
        deleteButton = new QPushButton(QIcon(":/Assets/Icons/delete.png"), tr("Delete"), this);

        // Assign shortcuts to QPushButtons.
        simulateButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
        modifyButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
        deleteButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));

        // Create labels for media data.
        mediaTitleLabel = new QLabel(QString::fromStdString(media->getTitle()), this);
        QFont fontLabel = QFont();
        fontLabel.setPointSize(20);

        mediaIDLabel = new QLabel(QString("ID: %1").arg(media->getId()), this);
        mediaIDLabel->setFont(fontLabel);

        mediaDescriptionLabel = new QLabel(QString("Description: %1").arg(QString::fromStdString(media->getDescription())), this);
        mediaDescriptionLabel->setFont(fontLabel);
        mediaDescriptionLabel->setWordWrap(true);

        mediaAuthorLabel = new QLabel(QString("Author: %1").arg(QString::fromStdString(media->getAuthor())), this);
        mediaAuthorLabel->setFont(fontLabel);
        mediaDescriptionLabel->setWordWrap(true);

        AboveChartLabelsCreatorVisitor aboveChartLabelsCreatorVisitor(this);
        media->accept(aboveChartLabelsCreatorVisitor);

        // Set font size for media title label.
        QFont fontTitle = mediaTitleLabel->font();
        fontTitle.setPointSize(36);
        mediaTitleLabel->setFont(fontTitle);
        mediaTitleLabel->setObjectName("mediaTitleLabel");

        // Create layouts to organize widgets.
        layout = new QGridLayout(this);

        // Add widgets to the data layout.
        layout->addWidget(mediaTitleLabel, 0, 0);
        layout->addWidget(modifyButton, 0, 1);
        layout->addWidget(deleteButton, 0, 2);
        layout->addWidget(simulateButton, 0, 3);
        layout->addWidget(mediaIDLabel, 1, 0);
        layout->addWidget(mediaAuthorLabel, 1, 1);
        layout->addWidget(mediaDescriptionLabel, 1, 2, 3, 2, Qt::AlignTop);
        layout->addWidget(mediaValue1Label, 2, 0);
        layout->addWidget(mediaValue2Label, 3, 0);
        layout->addWidget(mediaValue3Label, 2, 1);
        layout->addWidget(mediaValue4Label, 3, 1);

        // Set the main layout for the widget.
        setLayout(layout);

        // Connect button signals to slots.
        connect(simulateButton, &QPushButton::clicked, this, &AboveChartWidget::simulateSlot);
        connect(modifyButton, &QPushButton::clicked, this, &AboveChartWidget::modifySlot);
        connect(deleteButton, &QPushButton::clicked, this, &AboveChartWidget::deleteSlot);
    }

    // Create the rest of labels for Article
    void AboveChartWidget::createTheRestOfLabelsArticle(const std::string &journalName, const std::string &volumeNumber, const unsigned int &pageCount, const std::string &doi)
    {
        QFont font;
        font.setPointSize(20);

        mediaValue1Label = new QLabel(QString("Journal: %1").arg(QString::fromStdString(journalName)), this);
        mediaValue1Label->setFont(font);
        mediaValue2Label = new QLabel(QString("Volume: %1").arg(QString::fromStdString(volumeNumber)), this);
        mediaValue2Label->setFont(font);
        mediaValue3Label = new QLabel(QString("Pages: %1").arg(pageCount), this);
        mediaValue3Label->setFont(font);
        mediaValue4Label = new QLabel(QString("DOI: %1").arg(QString::fromStdString(doi)), this);
        mediaValue4Label->setFont(font);
    }

    // Create the rest of labels for Audio
    void AboveChartWidget::createTheRestOfLabelsAudio(const std::string &format, const std::string &artist, const std::string &album, const double &duration)
    {
        QFont font;
        font.setPointSize(20);

        mediaValue1Label = new QLabel(QString("Format: %1").arg(QString::fromStdString(format)), this);
        mediaValue1Label->setFont(font);
        mediaValue2Label = new QLabel(QString("Artist: %1").arg(QString::fromStdString(artist)), this);
        mediaValue2Label->setFont(font);
        mediaValue3Label = new QLabel(QString("Album: %1").arg(QString::fromStdString(album)), this);
        mediaValue3Label->setFont(font);
        mediaValue4Label = new QLabel(QString("Duration: %1").arg(QString::number(duration)) + " min", this);
        mediaValue4Label->setFont(font);
    }

    // Create the rest of labels for Book
    void AboveChartWidget::createTheRestOfLabelsBook(const std::string &publisher, const std::string &genre, const std::string &isbn, const double &pageCount)
    {
        QFont font;
        font.setPointSize(20);

        mediaValue1Label = new QLabel(QString("Publisher: %1").arg(QString::fromStdString(publisher)), this);
        mediaValue1Label->setFont(font);
        mediaValue2Label = new QLabel(QString("Genre: %1").arg(QString::fromStdString(genre)), this);
        mediaValue2Label->setFont(font);
        mediaValue3Label = new QLabel(QString("ISBN: %1").arg(QString::fromStdString(isbn)), this);
        mediaValue3Label->setFont(font);
        mediaValue4Label = new QLabel(QString("Pages: %1").arg(QString::number(pageCount)), this);
        mediaValue4Label->setFont(font);
    }

    // Create the rest of labels for Film
    void AboveChartWidget::createTheRestOfLabelsFilm(const std::string &director, const std::string &genre, const double &duration, const double &budget)
    {
        QFont font;
        font.setPointSize(20);

        mediaValue1Label = new QLabel(QString("Director: %1").arg(QString::fromStdString(director)), this);
        mediaValue1Label->setFont(font);
        mediaValue2Label = new QLabel(QString("Genre: %1").arg(QString::fromStdString(genre)), this);
        mediaValue2Label->setFont(font);
        mediaValue3Label = new QLabel(QString("Duration: %1").arg(QString::number(duration)) + " min", this);
        mediaValue3Label->setFont(font);
        mediaValue4Label = new QLabel(QString("Budget: $%1").arg(QString::number(budget)), this);
        mediaValue4Label->setFont(font);
    }

    // Get the ID of the selected media
    unsigned int AboveChartWidget::getId() const
    {
        if (mediaIDLabel != nullptr)
        {
            bool ok = true;
            QString idText = mediaIDLabel->text();
            QString idSubstring = idText.mid(4);
            unsigned int id = idSubstring.toUInt(&ok);
            if (ok)
            {
                return id;
            }
            else
            {
                qWarning() << "Invalid media ID!";
                throw std::exception();
            }
        }
        else
        {
            qWarning() << "No media selected in AboveChartWidget!";
            throw std::exception();
        }
    }

    // Slot for modifying sensor
    void AboveChartWidget::modifySlot()
    {
        emit modifySignal();
    }

    // Function for modifying sensor
    // Takes pointer to abstract sensor as parameter
    // Handles different types of sensors
    void AboveChartWidget::modify(Media::AbstractMedia *media)
    {
        // Handle article
        if (dynamic_cast<Media::Article *>(media))
        {
            Media::Article *article = static_cast<Media::Article *>(media);

            modifyWindow = new ModifyMediaDialogueWindow(article->getId(), "Article", article->getTitle(), article->getDescription(), article->getAuthor(),
                                                          article->getPageCount(), 0, "", 0);

            connect(modifyWindow, &ModifyMediaDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
            connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifyMediaDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaModified, this, &AboveChartWidget::saveModifySlot);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaNameModified, this, &AboveChartWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
        // Handle audio
        else if (dynamic_cast<Media::Audio *>(media))
        {
            Media::Audio *audio = static_cast<Media::Audio *>(media);

            modifyWindow = new ModifyMediaDialogueWindow(audio->getId(), "Audio", audio->getTitle(), audio->getDescription(), audio->getAuthor(),
                                                          audio->getDuration(), 0, audio->getFormat(), 0);

            connect(modifyWindow, &ModifyMediaDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
            connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifyMediaDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaModified, this, &AboveChartWidget::saveModifySlot);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaNameModified, this, &AboveChartWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
        // Handle book
        else if (dynamic_cast<Media::Book *>(media))
        {
            Media::Book *book = static_cast<Media::Book *>(media);

            modifyWindow = new ModifyMediaDialogueWindow(book->getId(), "Book", book->getTitle(), book->getDescription(), book->getAuthor(),
                                                          book->getPageCount(), 0, "", 0);

            connect(modifyWindow, &ModifyMediaDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
            connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifyMediaDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaModified, this, &AboveChartWidget::saveModifySlot);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaNameModified, this, &AboveChartWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
        // Handle film
        else if (dynamic_cast<Media::Film *>(media))
        {
            Media::Film *film = static_cast<Media::Film *>(media);

            modifyWindow = new ModifyMediaDialogueWindow(film->getId(), "Film", film->getTitle(), film->getDescription(), film->getAuthor(),
                                                          film->getDuration(), 0, film->getGenre(), 0);

            connect(modifyWindow, &ModifyMediaDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
            connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifyMediaDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaModified, this, &AboveChartWidget::saveModifySlot);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaNameModified, this, &AboveChartWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
    }

    // Signal when apply changes button is pressed
    void AboveChartWidget::applyChangesSlot()
    {
        emit applyChangesSignal();
    }

    // Signal to check if name is unique
    void AboveChartWidget::youCanCheckIfNameIsUnique(const std::vector<Media::AbstractMedia *> &medias)
    {
        emit finallyYouCanApplyChanges(medias);
    }

    // Signal to save modifications
    void AboveChartWidget::saveModifySlot(const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, const double &value4)
    {
        emit saveModifySignal(name, description, brand, value1, value2, value3, value4);
    }

    // Update media data and widget
    void AboveChartWidget::saveModify(Media::AbstractMedia *media, const std::string &name, const std::string &description, const std::string &brand, const double &value1, [[maybe_unused]] const double &value2, const std::string &value3, [[maybe_unused]] const double &value4)
    {
        if (dynamic_cast<Media::Article *>(media))
        {
            Media::Article *article = static_cast<Media::Article *>(media);

            article->setTitle(name);
            article->setDescription(description);
            article->setAuthor(brand);
            article->setPageCount(value1);
        }
        else if (dynamic_cast<Media::Audio *>(media))
        {
            Media::Audio *audio = static_cast<Media::Audio *>(media);

            audio->setTitle(name);
            audio->setDescription(description);
            audio->setAuthor(brand);
            audio->setDuration(value1);
            audio->setFormat(value3);
        }
        else if (dynamic_cast<Media::Book *>(media))
        {
            Media::Book *book = static_cast<Media::Book *>(media);

            book->setTitle(name);
            book->setDescription(description);
            book->setAuthor(brand);
            book->setPageCount(value1);
        }
        else if (dynamic_cast<Media::Film *>(media))
        {
            Media::Film *film = static_cast<Media::Film *>(media);

            film->setTitle(name);
            film->setDescription(description);
            film->setAuthor(brand);
            film->setDuration(value1);
            film->setGenre(value3);
        }

        // Update widget
        setMediaTitleLabel(name);
        setDescriptionLabel(description);
        setMediaAuthorLabel(brand);
        if (dynamic_cast<Media::Article *>(media))
        {
            setMediaValue1Label("Article", value1);
        }
        if (dynamic_cast<Media::Audio *>(media))
        {
            setMediaValue1Label("Audio", value1);
            setMediaValue3Label("Audio", value3);
        }
        if (dynamic_cast<Media::Book *>(media))
        {
            setMediaValue1Label("Book", value1);
        }
        if (dynamic_cast<Media::Film *>(media))
        {
            setMediaValue1Label("Film", value1);
            setMediaValue3Label("Film", value3);
        }

        // Notify main window of changes
        emit setIsSaved(false);
    }

    // Slot for handling name modification
    void AboveChartWidget::nameModifiedSlot(const std::string &previousName, const std::string &newName)
    {
        emit nameHasBeenModified(previousName, newName);
    }

    // Slot for handling delete button
    void AboveChartWidget::deleteSlot()
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Media", "Are you sure you want to delete this media permanently?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            emit mediaDeleted();
        }
    }

    // Slot for handling simulate button
    void AboveChartWidget::simulateSlot()
    {
        emit simulate();
    }

    // Set media title label
    void AboveChartWidget::setMediaTitleLabel(const std::string &title)
    {
        mediaTitleLabel->setText(QString::fromStdString(title));
    }

    // Set media description label
    void AboveChartWidget::setDescriptionLabel(const std::string &description)
    {
        mediaDescriptionLabel->setText("Description: " + QString::fromStdString(description));
    }

    // Set media author label
    void AboveChartWidget::setMediaAuthorLabel(const std::string &author)
    {
        mediaAuthorLabel->setText("Author: " + QString::fromStdString(author));
    }

    // Set media value 1 label
    void AboveChartWidget::setMediaValue1Label(const std::string &type, const double &value)
    {
        if (type == "Article" || type == "Book")
            mediaValue1Label->setText("Pages: " + QString::number(value));
        if (type == "Audio" || type == "Film")
            mediaValue1Label->setText("Duration: " + QString::number(value) + " min");
    }

    // Set media value 2 label
    void AboveChartWidget::setMediaValue2Label(const std::string &type, const double &value)
    {
        if (type == "Film")
            mediaValue2Label->setText("Rating: " + QString::number(value) + "/10");
    }

    // Set media value 3 label
    void AboveChartWidget::setMediaValue3Label(const std::string &type, const std::string &value)
    {
        if (type == "Audio")
            mediaValue3Label->setText("Format: " + QString::fromStdString(value));
        if (type == "Film")
            mediaValue3Label->setText("Genre: " + QString::fromStdString(value));
    }

    // Set media value 4 label
    void AboveChartWidget::setMediaValue4Label([[maybe_unused]] const std::string &type, [[maybe_unused]] const double &value)
    {
        // Currently not used for any media type
    }
    // Destructor
    AboveChartWidget::~AboveChartWidget()
    {
        delete greyPanel;

        delete mediaTitleLabel;
        delete mediaIDLabel;
        delete mediaDescriptionLabel;
        delete mediaAuthorLabel;
        delete mediaValue1Label;
        delete mediaValue2Label;
        delete mediaValue3Label;
        delete mediaValue4Label;

        delete simulateButton;
        delete modifyButton;
        delete deleteButton;

        delete modifyWindow;

        delete layout;
    }
}
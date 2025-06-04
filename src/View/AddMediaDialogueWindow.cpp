#include "AddMediaDialogueWindow.h"
#include <QDate>
#include <QWidget>
#include <QFileDialog>
#include <QImageReader>

namespace View
{
    // AddMediaDialogueWindow constructor
    // Set window title, create layouts, add widgets and connect signals
    AddMediaDialogueWindow::AddMediaDialogueWindow(AbstractDialogueWindow* parent)
        : AbstractDialogueWindow(parent)
    {
        setWindowTitle("Add a new media");

        // Create main layout
        mainLayout = new QVBoxLayout(this);
        mainLayout->setObjectName("AddMediaDialogueWindow");

        // Create type layout
        typeLayout = new QHBoxLayout;
        typeLabel = new QLabel("Type:", this);
        typeComboBox = new QComboBox(this);
        typeComboBox->addItem("Article");
        typeComboBox->addItem("Audio");
        typeComboBox->addItem("Book");
        typeComboBox->addItem("Film");
        typeLayout->addWidget(typeLabel);
        typeLayout->addWidget(typeComboBox);

        // Create id layout
        idLayout = new QHBoxLayout;
        idLabel = new QLabel("ID:", this);
        idLineEdit = new QLineEdit(this);
        idLineEdit->setFixedSize(193, 26);
        idLayout->addWidget(idLabel);
        idLayout->addWidget(idLineEdit);

        // Create title layout
        nameLayout = new QHBoxLayout;
        nameLabel = new QLabel("Title:", this);
        nameLineEdit = new QLineEdit(this);
        nameLineEdit->setFixedSize(193, 26);
        nameLayout->addWidget(nameLabel);
        nameLayout->addWidget(nameLineEdit);

        // Create description layout
        descriptionLayout = new QHBoxLayout;
        descriptionLabel = new QLabel("Description:", this);
        descriptionLineEdit = new QLineEdit(this);
        descriptionLineEdit->setFixedSize(193, 26);
        descriptionLayout->addWidget(descriptionLabel);
        descriptionLayout->addWidget(descriptionLineEdit);

        // Create author layout
        brandLayout = new QHBoxLayout;
        brandLabel = new QLabel("Author:", this);
        brandLineEdit = new QLineEdit(this);
        brandLineEdit->setFixedSize(193, 26);
        brandLayout->addWidget(brandLabel);
        brandLayout->addWidget(brandLineEdit);

        // Initialize all specific media type fields
        
        // Article fields
        journalLayout = new QHBoxLayout;
        journalLabel = new QLabel("Journal:", this);
        journalLineEdit = new QLineEdit(this);
        journalLineEdit->setFixedSize(193, 26);
        journalLayout->addWidget(journalLabel);
        journalLayout->addWidget(journalLineEdit);

        volumeLayout = new QHBoxLayout;
        volumeLabel = new QLabel("Volume:", this);
        volumeLineEdit = new QLineEdit(this);
        volumeLineEdit->setFixedSize(193, 26);
        volumeLayout->addWidget(volumeLabel);
        volumeLayout->addWidget(volumeLineEdit);

        doiLayout = new QHBoxLayout;
        doiLabel = new QLabel("DOI:", this);
        doiLineEdit = new QLineEdit(this);
        doiLineEdit->setFixedSize(193, 26);
        doiLayout->addWidget(doiLabel);
        doiLayout->addWidget(doiLineEdit);

        pagesLayout = new QHBoxLayout;
        pagesLabel = new QLabel("Pages:", this);
        pagesLineEdit = new QLineEdit(this);
        pagesLineEdit->setFixedSize(193, 26);
        pagesLayout->addWidget(pagesLabel);
        pagesLayout->addWidget(pagesLineEdit);

        // Audio fields
        durationLayout = new QHBoxLayout;
        durationLabel = new QLabel("Duration:", this);
        durationLineEdit = new QLineEdit(this);
        durationLineEdit->setFixedSize(193, 26);
        durationLayout->addWidget(durationLabel);
        durationLayout->addWidget(durationLineEdit);

        formatLayout = new QHBoxLayout;
        formatLabel = new QLabel("Format:", this);
        formatLineEdit = new QLineEdit(this);
        formatLineEdit->setFixedSize(193, 26);
        formatLayout->addWidget(formatLabel);
        formatLayout->addWidget(formatLineEdit);

        artistLayout = new QHBoxLayout;
        artistLabel = new QLabel("Artist:", this);
        artistLineEdit = new QLineEdit(this);
        artistLineEdit->setFixedSize(193, 26);
        artistLayout->addWidget(artistLabel);
        artistLayout->addWidget(artistLineEdit);

        albumLayout = new QHBoxLayout;
        albumLabel = new QLabel("Album:", this);
        albumLineEdit = new QLineEdit(this);
        albumLineEdit->setFixedSize(193, 26);
        albumLayout->addWidget(albumLabel);
        albumLayout->addWidget(albumLineEdit);

        // Book fields
        isbnLayout = new QHBoxLayout;
        isbnLabel = new QLabel("ISBN:", this);
        isbnLineEdit = new QLineEdit(this);
        isbnLineEdit->setFixedSize(193, 26);
        isbnLayout->addWidget(isbnLabel);
        isbnLayout->addWidget(isbnLineEdit);

        publisherLayout = new QHBoxLayout;
        publisherLabel = new QLabel("Publisher:", this);
        publisherLineEdit = new QLineEdit(this);
        publisherLineEdit->setFixedSize(193, 26);
        publisherLayout->addWidget(publisherLabel);
        publisherLayout->addWidget(publisherLineEdit);

        genreLayout = new QHBoxLayout;
        genreLabel = new QLabel("Genre:", this);
        genreLineEdit = new QLineEdit(this);
        genreLineEdit->setFixedSize(193, 26);
        genreLayout->addWidget(genreLabel);
        genreLayout->addWidget(genreLineEdit);

        // Film fields
        budgetLayout = new QHBoxLayout;
        budgetLabel = new QLabel("Budget ($):", this);
        budgetLineEdit = new QLineEdit(this);
        budgetLineEdit->setFixedSize(193, 26);
        budgetLayout->addWidget(budgetLabel);
        budgetLayout->addWidget(budgetLineEdit);

        // Create cover image layout
        coverImageLayout = new QHBoxLayout;
        coverImageLabel = new QLabel("Cover Image:", this);
        coverImagePreview = new QLabel(this);
        coverImagePreview->setFixedSize(100, 100);
        coverImagePreview->setScaledContents(true);
        selectCoverButton = new QPushButton("Select Image", this);
        connect(selectCoverButton, &QPushButton::clicked, this, &AddMediaDialogueWindow::selectCoverImage);
        
        coverImageLayout->addWidget(coverImageLabel);
        coverImageLayout->addWidget(coverImagePreview);
        coverImageLayout->addWidget(selectCoverButton);

        // Create buttons layout
        buttonsLayout = new QHBoxLayout;

        // Create buttons
        createButton = new QPushButton("Add", this);
        createButton->setShortcut(Qt::Key_Enter);
        connect(createButton, &QPushButton::clicked, this, &AddMediaDialogueWindow::createAndAddSlot);

        discardButton = new QPushButton("Cancel", this);
        discardButton->setShortcut(Qt::Key_Escape);
        connect(discardButton, &QPushButton::clicked, this, &AddMediaDialogueWindow::discardChanges);

        // Add buttons to layout
        buttonsLayout->addWidget(discardButton);
        buttonsLayout->addWidget(createButton);

        // Add all layouts to main layout
        mainLayout->addLayout(typeLayout);
        mainLayout->addLayout(idLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(descriptionLayout);
        mainLayout->addLayout(brandLayout);
        mainLayout->addLayout(journalLayout);
        mainLayout->addLayout(volumeLayout);
        mainLayout->addLayout(doiLayout);
        mainLayout->addLayout(pagesLayout);
        mainLayout->addLayout(durationLayout);
        mainLayout->addLayout(formatLayout);
        mainLayout->addLayout(artistLayout);
        mainLayout->addLayout(albumLayout);
        mainLayout->addLayout(isbnLayout);
        mainLayout->addLayout(publisherLayout);
        mainLayout->addLayout(genreLayout);
        mainLayout->addLayout(budgetLayout);
        mainLayout->addLayout(coverImageLayout);
        mainLayout->addLayout(buttonsLayout);

        // Set main layout as window layout
        setLayout(mainLayout);

        // Initially hide all specific fields
        onTypeChanged(0);

        // Connect typeComboBox signal to onTypeChanged slot
        connect(typeComboBox, &QComboBox::currentIndexChanged, this, &AddMediaDialogueWindow::onTypeChanged);
    }

    // Check if the new media is different from the original
    bool AddMediaDialogueWindow::differentFromOriginal() {
        // If all fields are empty or the default option is selected, it's not different from the original, otherwise it is
        return !(typeComboBox->currentIndex() == 0 &&
                 idLineEdit->text().isEmpty() &&
                 nameLineEdit->text().isEmpty() &&
                 descriptionLineEdit->text().isEmpty() &&
                 brandLineEdit->text().isEmpty());
    }

    // Emit signal to start adding a new media
    void AddMediaDialogueWindow::createAndAddSlot()
    {
        // Emit signal to start adding a new media
        emit createAndAddSignal();
    }

    // Create and add a new media to the list of medias
    void AddMediaDialogueWindow::createAndAddMedia(const std::vector<Media::AbstractMedia *> &medias) {
        bool ok = true;
        unsigned int id = idLineEdit->text().toUInt(&ok);
        if (!ok) {
            QMessageBox::critical(this, "Error", "ID must be a non-negative integer!");
            return;
        }
        if (idLineEdit->text().length() != 6) {
            QMessageBox::critical(this, "Error", "The ID must consist of exactly 6 digits!");
            return;
        }
        std::string title = nameLineEdit->text().toStdString();
        std::string description = descriptionLineEdit->text().toStdString();
        std::string author = brandLineEdit->text().toStdString();

        if (title.empty() || description.empty() || author.empty()) {
            QMessageBox::critical(this, "Error", "Id, title, description and author values cannot be empty!");
            return;
        }
        for (Media::AbstractMedia *media : medias) {
            if (media->getId() == id) {
                QMessageBox::critical(this, "Error", "ID already in use");
                return;
            }
            if (media->getTitle() == title) {
                QMessageBox::critical(this, "Error", "Name already in use");
                return;
            }
        }
        std::string type = typeComboBox->currentText().toStdString();
        std::string currentDate = QDate::currentDate().toString("yyyy-MM-dd").toStdString();
        Media::AbstractMedia *media = nullptr;

        if (type == "Article") {
            bool pagesOk = true;
            unsigned int pages = pagesLineEdit->text().toUInt(&pagesOk);
            if (!pagesOk || pages == 0) {
                QMessageBox::critical(this, "Error", "Pages must be a positive number!");
                return;
            }
            std::string journal = journalLineEdit->text().toStdString();
            std::string volume = volumeLineEdit->text().toStdString();
            std::string doi = doiLineEdit->text().toStdString();
            
            if (journal.empty() || volume.empty()) {
                QMessageBox::critical(this, "Error", "Journal and volume cannot be empty!");
                return;
            }
            
            std::string title = nameLineEdit->text().toStdString();
            std::string author = brandLineEdit->text().toStdString();
            
            media = new Media::Article(id, title, currentDate, author, description, 
                                     journal, volume, pages, doi);
            if (!selectedCoverPath.isEmpty()) {
                media->setCoverImage(selectedCoverPath.toStdString());
            }
        } 
        else if (type == "Audio") {
            bool durationOk = true;
            unsigned int duration = durationLineEdit->text().toUInt(&durationOk);
            if (!durationOk || duration == 0) {
                QMessageBox::critical(this, "Error", "Duration must be a positive number!");
                return;
            }
            
            std::string format = formatLineEdit->text().toStdString();
            std::string artist = artistLineEdit->text().toStdString();
            std::string album = albumLineEdit->text().toStdString();
            
            if (format.empty() || artist.empty()) {
                QMessageBox::critical(this, "Error", "Format and artist cannot be empty!");
                return;
            }
            
            std::string title = nameLineEdit->text().toStdString();
            std::string author = brandLineEdit->text().toStdString();
            
            media = new Media::Audio(id, title, currentDate, author, description,
                                   duration, format, artist, album);
            if (!selectedCoverPath.isEmpty()) {
                media->setCoverImage(selectedCoverPath.toStdString());
            }
        } 
        else if (type == "Book") {
            bool pagesOk = true;
            unsigned int pages = pagesLineEdit->text().toUInt(&pagesOk);
            if (!pagesOk || pages == 0) {
                QMessageBox::critical(this, "Error", "Pages must be a positive number!");
                return;
            }
            
            std::string isbn = isbnLineEdit->text().toStdString();
            std::string publisher = publisherLineEdit->text().toStdString();
            std::string genre = genreLineEdit->text().toStdString();
            
            if (isbn.empty() || publisher.empty() || genre.empty()) {
                QMessageBox::critical(this, "Error", "ISBN, publisher and genre cannot be empty!");
                return;
            }
            
            std::string title = nameLineEdit->text().toStdString();
            std::string author = brandLineEdit->text().toStdString();
            
            media = new Media::Book(id, title, currentDate, author, description,
                                  isbn, pages, publisher, genre);
            if (!selectedCoverPath.isEmpty()) {
                media->setCoverImage(selectedCoverPath.toStdString());
            }
        } 
        else if (type == "Film") {
            bool durationOk = true;
            unsigned int duration = durationLineEdit->text().toUInt(&durationOk);
            if (!durationOk || duration == 0) {
                QMessageBox::critical(this, "Error", "Duration must be a positive number!");
                return;
            }
            
            std::string title = nameLineEdit->text().toStdString();
            std::string description = descriptionLineEdit->text().toStdString();
            std::string director = brandLineEdit->text().toStdString();
            std::string genre = genreLineEdit->text().toStdString();
            bool budgetOk = true;
            double budget = budgetLineEdit->text().toDouble(&budgetOk);
            
            if (!budgetOk || budget < 0) {
                QMessageBox::critical(this, "Error", "Budget must be a non-negative number!");
                return;
            }
            
            if (title.empty() || description.empty() || director.empty() || genre.empty()) {
                QMessageBox::critical(this, "Error", "Title, description, director and genre cannot be empty!");
                return;
            }
            
            media = new Media::Film(id, title, currentDate, director, description,
                                  director, duration, genre, budget);
            if (!selectedCoverPath.isEmpty()) {
                media->setCoverImage(selectedCoverPath.toStdString());
            }
        } else {
            QMessageBox::critical(this, "Error", "Invalid media type selected!");
            return;
        }
        
        if (!media) {
            QMessageBox::critical(this, "Error", "Failed to create media!");
            return;
        }
        
        emit mediaAdded(media);
    }

    // Discard changes and close the dialog if there are changes
    void AddMediaDialogueWindow::discardChanges()
    {
        if (differentFromOriginal()) {
            QMessageBox::StandardButton reply = QMessageBox::question(
                this, "Discard changes?",
                "Are you sure you want to discard the changes?",
                QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) reject();
        } else reject();
    }

    // Slot to handle typeComboBox index change
    void AddMediaDialogueWindow::onTypeChanged(int index) {
        QString type = typeComboBox->itemText(index);
        
        // Hide all specific fields first
        journalLabel->setVisible(false);
        journalLineEdit->setVisible(false);
        volumeLabel->setVisible(false);
        volumeLineEdit->setVisible(false);
        doiLabel->setVisible(false);
        doiLineEdit->setVisible(false);
        pagesLabel->setVisible(false);
        pagesLineEdit->setVisible(false);
        durationLabel->setVisible(false);
        durationLineEdit->setVisible(false);
        formatLabel->setVisible(false);
        formatLineEdit->setVisible(false);
        artistLabel->setVisible(false);
        artistLineEdit->setVisible(false);
        albumLabel->setVisible(false);
        albumLineEdit->setVisible(false);
        isbnLabel->setVisible(false);
        isbnLineEdit->setVisible(false);
        publisherLabel->setVisible(false);
        publisherLineEdit->setVisible(false);
        genreLabel->setVisible(false);
        genreLineEdit->setVisible(false);
        budgetLabel->setVisible(false);
        budgetLineEdit->setVisible(false);

        // Update Author/Director label based on type
        brandLabel->setText(type == "Film" ? "Director:" : "Author:");

        // Show fields based on selected type
        if (type == "Article") {
            journalLabel->setVisible(true);
            journalLineEdit->setVisible(true);
            volumeLabel->setVisible(true);
            volumeLineEdit->setVisible(true);
            doiLabel->setVisible(true);
            doiLineEdit->setVisible(true);
            pagesLabel->setVisible(true);
            pagesLineEdit->setVisible(true);
        }
        else if (type == "Audio") {
            durationLabel->setVisible(true);
            durationLineEdit->setVisible(true);
            formatLabel->setVisible(true);
            formatLineEdit->setVisible(true);
            artistLabel->setVisible(true);
            artistLineEdit->setVisible(true);
            albumLabel->setVisible(true);
            albumLineEdit->setVisible(true);
        }
        else if (type == "Book") {
            pagesLabel->setVisible(true);
            pagesLineEdit->setVisible(true);
            isbnLabel->setVisible(true);
            isbnLineEdit->setVisible(true);
            publisherLabel->setVisible(true);
            publisherLineEdit->setVisible(true);
            genreLabel->setVisible(true);
            genreLineEdit->setVisible(true);
        }
        else if (type == "Film") {
            durationLabel->setVisible(true);
            durationLineEdit->setVisible(true);
            genreLabel->setVisible(true);
            genreLineEdit->setVisible(true);
            budgetLabel->setVisible(true);
            budgetLineEdit->setVisible(true);
        }
    }

    // Slot to handle cover image selection
    void AddMediaDialogueWindow::selectCoverImage() {
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Select Cover Image"), "",
            tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
        
        if (!fileName.isEmpty()) {
            QImage image(fileName);
            if (!image.isNull()) {
                selectedCoverPath = fileName;
                coverImagePreview->setPixmap(QPixmap::fromImage(image).scaled(
                    coverImagePreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                QMessageBox::critical(this, "Error", "Failed to load the selected image!");
            }
        }
    }

    // Destructor of the AddMediaDialogueWindow class
    // Deletes all dynamically allocated UI elements
    AddMediaDialogueWindow::~AddMediaDialogueWindow() {
        delete typeLabel;
        delete idLabel;
        delete nameLabel;
        delete descriptionLabel;
        delete brandLabel;
        delete journalLabel;
        delete volumeLabel;
        delete doiLabel;
        delete artistLabel;
        delete albumLabel;
        delete isbnLabel;
        delete publisherLabel;
        delete budgetLabel;

        delete typeComboBox;
        delete idLineEdit;
        delete nameLineEdit;
        delete descriptionLineEdit;
        delete brandLineEdit;
        delete journalLineEdit;
        delete volumeLineEdit;
        delete doiLineEdit;
        delete artistLineEdit;
        delete albumLineEdit;
        delete isbnLineEdit;
        delete publisherLineEdit;
        delete budgetLineEdit;

        delete discardButton;
        delete createButton;

        delete typeLayout;
        delete idLayout;
        delete nameLayout;
        delete descriptionLayout;
        delete brandLayout;
        delete journalLayout;
        delete volumeLayout;
        delete doiLayout;
        delete artistLayout;
        delete albumLayout;
        delete isbnLayout;
        delete publisherLayout;
        delete budgetLayout;
        delete buttonsLayout;
        delete mainLayout;
    }

}

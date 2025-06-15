#include "AddMediaDialogueWindow.h"
#include <QDate>
#include <QWidget>
#include <QFileDialog>
#include <QImageReader>
#include <QDir>
#include <QDateTime>
#include <QCoreApplication>
#include <QMessageBox>

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
        setMinimumWidth(450);  // Set minimum width for the dialog

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

        // Create title layout
        nameLayout = new QHBoxLayout;
        nameLabel = new QLabel("Title:", this);
        nameLineEdit = new QLineEdit(this);
        nameLineEdit->setFixedSize(300, 26);
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
        authorLayout = new QHBoxLayout;
        authorLabel = new QLabel("Author:", this);
        authorLineEdit = new QLineEdit(this);
        authorLineEdit->setFixedSize(193, 26);
        authorLayout->addWidget(authorLabel);
        authorLayout->addWidget(authorLineEdit);

        // Create production company layout (for Film)
        productionCompanyLayout = new QHBoxLayout;
        productionCompanyLabel = new QLabel("Production Company:", this);
        productionCompanyLineEdit = new QLineEdit(this);
        productionCompanyLineEdit->setFixedSize(193, 26);
        productionCompanyLabel->hide();
        productionCompanyLineEdit->hide();
        productionCompanyLayout->addWidget(productionCompanyLabel);
        productionCompanyLayout->addWidget(productionCompanyLineEdit);

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
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(descriptionLayout);
        mainLayout->addLayout(authorLayout);
        mainLayout->addLayout(productionCompanyLayout);  // Add production company layout (will be shown/hidden as needed)

        // Add media type specific fields layouts
        mainLayout->addLayout(journalLayout);
        mainLayout->addLayout(volumeLayout);
        mainLayout->addLayout(doiLayout);
        mainLayout->addLayout(pagesLayout);
        mainLayout->addLayout(durationLayout);
        mainLayout->addLayout(formatLayout);
        mainLayout->addLayout(albumLayout);
        mainLayout->addLayout(isbnLayout);
        mainLayout->addLayout(publisherLayout);
        mainLayout->addLayout(genreLayout);
        mainLayout->addLayout(budgetLayout);
        mainLayout->addLayout(coverImageLayout);
        mainLayout->addLayout(buttonsLayout);

        // Set main layout as window layout
        setLayout(mainLayout);

        // Set up validators for numeric fields
        pagesLineEdit->setValidator(new QIntValidator(1, 999999, this));  // Minimo 1 pagina
        durationLineEdit->setValidator(new QIntValidator(1, 999999, this));  // Minimo 1 secondo
        budgetLineEdit->setValidator(new QDoubleValidator(0, 999999999.99, 2, this));  // Budget può essere 0

        // Initially hide all specific fields
        onTypeChanged(0);

        // Connect typeComboBox signal to onTypeChanged slot
        connect(typeComboBox, &QComboBox::currentIndexChanged, this, &AddMediaDialogueWindow::onTypeChanged);
    }

    // Check if the new media is different from the original
    bool AddMediaDialogueWindow::differentFromOriginal() {
        // If all fields are empty or the default option is selected, it's not different from the original, otherwise it is
        return !(typeComboBox->currentIndex() == 0 &&
                 nameLineEdit->text().isEmpty() &&
                 descriptionLineEdit->text().isEmpty() &&
                 authorLineEdit->text().isEmpty());
    }

    // Emit signal to start adding a new media
    void AddMediaDialogueWindow::createAndAddSlot()
    {
        // Emit signal to start adding a new media
        emit createAndAddSignal();
    }

    // Create and add a new media to the list of medias
    void AddMediaDialogueWindow::createAndAddMedia(const std::vector<Media::AbstractMedia *> &medias) {
        // Find the highest ID currently in use
        unsigned int maxId = 0;
        for (Media::AbstractMedia *existingMedia : medias) {
            if (existingMedia->getId() > maxId) {
                maxId = existingMedia->getId();
            }
        }
        // Generate the new ID by adding 1, starting from 000001 if list is empty
        unsigned int id = (medias.empty()) ? 1 : maxId + 1;
        
        std::string title = nameLineEdit->text().toStdString();
        std::string description = descriptionLineEdit->text().toStdString();
        std::string author = authorLineEdit->text().toStdString();

        if (title.empty() || description.empty() || author.empty()) {
            QMessageBox::critical(this, "Error", "Title, description and author values cannot be empty!");
            return;
        }

        // Check if title is already in use
        for (Media::AbstractMedia *media : medias) {
            if (media->getTitle() == title) {
                QMessageBox::critical(this, "Error", "Title already in use");
                return;
            }
        }

        std::string type = typeComboBox->currentText().toStdString();
        std::string currentDate = QDate::currentDate().toString("yyyy-MM-dd").toStdString();
        Media::AbstractMedia *media = nullptr;

        std::string coverImagePath = selectedCoverPath.toStdString();
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
            media = new Media::Article(id, title, author, description, journal, volume, pages, doi, coverImagePath);
        } else if (type == "Audio") {
            bool durationOk = true;
            unsigned int duration = durationLineEdit->text().toUInt(&durationOk);
            if (!durationOk || duration == 0) {
                QMessageBox::critical(this, "Error", "Duration must be a positive number!");
                return;
            }
            std::string format = formatLineEdit->text().toStdString();
            std::string album = albumLineEdit->text().toStdString();
            if (format.empty() || album.empty()) {
                QMessageBox::critical(this, "Error", "Format and album cannot be empty!");
                return;
            }
            media = new Media::Audio(id, title, author, description, duration, format, album, coverImagePath);
        } else if (type == "Book") {
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
            media = new Media::Book(id, title, author, description, isbn, pages, publisher, genre, coverImagePath);
        } else if (type == "Film") {
            bool durationOk = true;
            unsigned int duration = durationLineEdit->text().toUInt(&durationOk);
            if (!durationOk || duration == 0) {
                QMessageBox::critical(this, "Error", "Duration must be a positive number!");
                return;
            }
            std::string productionCompany = productionCompanyLineEdit->text().toStdString();
            std::string genre = genreLineEdit->text().toStdString();
            bool budgetOk = true;
            double budget = budgetLineEdit->text().toDouble(&budgetOk);
            if (!budgetOk || budget < 0) {
                QMessageBox::critical(this, "Error", "Budget must be a non-negative number!");
                return;
            }
            if (title.empty() || description.empty() || author.empty() || productionCompany.empty() || genre.empty()) {
                QMessageBox::critical(this, "Error", "Title, description, author, production company and genre cannot be empty!");
                return;
            }
            media = new Media::Film(id, title, author, description, productionCompany, duration, genre, budget, coverImagePath);
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

    // Save the selected image to the project's images directory
    QString AddMediaDialogueWindow::copyImageToProjectAndGetPath(const QString& originalImagePath) {
        if (originalImagePath.isEmpty())
            return QString();

        // Create a unique filename with timestamp
        QFileInfo originalFile(originalImagePath);
        QString newFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_") + 
                            originalFile.fileName();
        
        // Get the project src directory by going up from the executable location
        QDir projectDir(QCoreApplication::applicationDirPath());
        
        // Navigate to the src directory
        #ifdef Q_OS_MAC
            projectDir.cdUp(); // up from MacOS
            projectDir.cdUp(); // up from Contents
            projectDir.cdUp(); // up from .app
            projectDir.cd("src"); // enter src directory
        #else
            projectDir.cdUp(); // up from build directory
            projectDir.cd("src"); // enter src directory
        #endif
        
        // Create images directory if it doesn't exist
        QDir imagesDir(projectDir.absoluteFilePath("images"));
        imagesDir.mkpath(".");
        
        QString destinationPath = imagesDir.absoluteFilePath(newFileName);
        
        // If the destination file already exists, remove it
        if (QFile::exists(destinationPath)) {
            QFile::remove(destinationPath);
        }
        
        // Copy the file
        if (!QFile::copy(originalImagePath, destinationPath))
            return QString();
            
        return "../../../src/images/" + newFileName;
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

        // Show/hide Production Company field for Film
        productionCompanyLabel->setVisible(type == "Film");
        productionCompanyLineEdit->setVisible(type == "Film");

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
                QString newPath = copyImageToProjectAndGetPath(fileName);
                if (!newPath.isEmpty()) {
                    selectedCoverPath = newPath;
                    coverImagePreview->setPixmap(QPixmap::fromImage(image).scaled(
                        coverImagePreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                } else {
                    QMessageBox::critical(this, "Error", "Failed to save the image!");
                }
            } else {
                QMessageBox::critical(this, "Error", "Failed to load the selected image!");
            }
        }
    }

    // Destructor of the AddMediaDialogueWindow class
    // Deletes all dynamically allocated UI elements
    AddMediaDialogueWindow::~AddMediaDialogueWindow() {
        delete journalLabel;
        delete volumeLabel;
        delete doiLabel;
        delete albumLabel;
        delete isbnLabel;
        delete publisherLabel;
        delete budgetLabel;
        delete coverImageLabel;
        delete coverImagePreview;

        delete typeComboBox;
        delete nameLineEdit;
        delete descriptionLineEdit;
        delete authorLineEdit;
        delete productionCompanyLineEdit;
        delete journalLineEdit;
        delete volumeLineEdit;
        delete doiLineEdit;
        delete albumLineEdit;
        delete isbnLineEdit;
        delete publisherLineEdit;
        delete budgetLineEdit;

        delete discardButton;
        delete createButton;
        delete selectCoverButton;

        delete typeLayout;
        delete nameLayout;
        delete descriptionLayout;
        delete authorLayout;
        delete productionCompanyLayout;
        delete journalLayout;
        delete volumeLayout;
        delete doiLayout;
        delete albumLayout;
        delete isbnLayout;
        delete publisherLayout;
        delete budgetLayout;
        delete coverImageLayout;
        delete buttonsLayout;

        delete mainLayout;
    }

}

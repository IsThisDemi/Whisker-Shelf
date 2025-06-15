#include "ModifyMediaDialogueWindow.h"
#include <QFileDialog>
#include <QImageReader>
#include <QDir>
#include <QDateTime>
#include <QCoreApplication>
#include <QMessageBox>

namespace View
{

    // This is the constructor of the ModifyMediaDialogueWindow class
    ModifyMediaDialogueWindow::ModifyMediaDialogueWindow(const unsigned int &Id, const std::string &Type, const std::string &MediaName,
                                                           const std::string &MediaDescription,                                                           const std::string &MediaAuthor,
                                                           const std::map<std::string, std::variant<std::string, unsigned int, double>> &MediaFields,
                                                           const std::string &CoverImage, AbstractDialogueWindow *parent)
        : AbstractDialogueWindow(parent), id(Id), type(Type), originalMediaName(MediaName),
          originalMediaDescription(MediaDescription), originalMediaAuthor(MediaAuthor),
          originalCoverImage(CoverImage)
    {
        // Initialize media type specific fields
        if (type == "Article") {
            originalJournalName = std::get<std::string>(MediaFields.at("journalName"));
            originalVolume = std::get<std::string>(MediaFields.at("volumeNumber"));
            originalPageCount = std::get<unsigned int>(MediaFields.at("pageCount"));
            originalDoi = std::get<std::string>(MediaFields.at("doi"));
        }
        else if (type == "Audio") {
            originalDuration = std::get<unsigned int>(MediaFields.at("duration"));
            originalFormat = std::get<std::string>(MediaFields.at("format"));
            originalAlbum = std::get<std::string>(MediaFields.at("album"));
        }
        else if (type == "Book") {
            originalIsbn = std::get<std::string>(MediaFields.at("isbn"));
            originalBookPageCount = std::get<unsigned int>(MediaFields.at("pageCount"));
            originalPublisher = std::get<std::string>(MediaFields.at("publisher"));
            originalBookGenre = std::get<std::string>(MediaFields.at("genre"));
        }
        else if (type == "Film") {
            originalProductionCompany = std::get<std::string>(MediaFields.at("productionCompany"));
            originalFilmDuration = std::get<unsigned int>(MediaFields.at("duration"));
            originalFilmGenre = std::get<std::string>(MediaFields.at("genre"));
            originalBudget = std::get<double>(MediaFields.at("budget"));
        }

        setupUI();
    }

    void ModifyMediaDialogueWindow::setupUI() {
        // Set the title of the window
        setWindowTitle("Modify " + QString::fromStdString(type));
        setMinimumWidth(450);  // Set minimum width for the dialog

        // Create a vertical layout for the main window
        mainLayout = new QVBoxLayout(this);

        // Common fields section
        setupCommonFields();

        // Media type specific fields section
        setupMediaTypeSpecificFields();

        // Cover image section
        setupCoverImageSection();

        // Buttons section
        setupButtons();

        setLayout(mainLayout);

        // Connect signals
        connectSignals();
    }

    void ModifyMediaDialogueWindow::setupCommonFields() {
        // Name field
        nameLayout = new QHBoxLayout;
        nameLabel = new QLabel("Name:", this);
        nameLineEdit = new QLineEdit(QString::fromStdString(originalMediaName), this);
        nameLineEdit->setFixedSize(193, 26);
        nameLayout->addWidget(nameLabel);
        nameLayout->addWidget(nameLineEdit);
        mainLayout->addLayout(nameLayout);

        // Description field
        descriptionLayout = new QHBoxLayout;
        descriptionLabel = new QLabel("Description:", this);
        descriptionLineEdit = new QLineEdit(QString::fromStdString(originalMediaDescription), this);
        descriptionLineEdit->setFixedSize(193, 26);
        descriptionLayout->addWidget(descriptionLabel);
        descriptionLayout->addWidget(descriptionLineEdit);
        mainLayout->addLayout(descriptionLayout);

        // Author field
        authorLayout = new QHBoxLayout;
        authorLabel = new QLabel("Author:", this);
        authorLineEdit = new QLineEdit(QString::fromStdString(originalMediaAuthor), this);
        authorLineEdit->setFixedSize(193, 26);
        authorLayout->addWidget(authorLabel);
        authorLayout->addWidget(authorLineEdit);
        mainLayout->addLayout(authorLayout);

        // Production Company field (only for Film)
        if (type == "Film") {
            productionCompanyLayout = new QHBoxLayout;
            productionCompanyLabel = new QLabel("Production Company:", this);
            productionCompanyLineEdit = new QLineEdit(QString::fromStdString(originalProductionCompany), this);
            productionCompanyLineEdit->setFixedSize(193, 26);
            productionCompanyLayout->addWidget(productionCompanyLabel);
            productionCompanyLayout->addWidget(productionCompanyLineEdit);
            mainLayout->addLayout(productionCompanyLayout);
        }
    }

    void ModifyMediaDialogueWindow::setupMediaTypeSpecificFields() {
        field1Edit = new QLineEdit(this);
        field2Edit = new QLineEdit(this);
        field3Edit = new QLineEdit(this);
        field4Edit = new QLineEdit(this);
        field1Edit->setFixedSize(193, 26);
        field2Edit->setFixedSize(193, 26);
        field3Edit->setFixedSize(193, 26);
        field4Edit->setFixedSize(193, 26);

        QHBoxLayout *field1Layout = new QHBoxLayout;
        QHBoxLayout *field2Layout = new QHBoxLayout;
        QHBoxLayout *field3Layout = new QHBoxLayout;
        QHBoxLayout *field4Layout = new QHBoxLayout;

        field1Label = new QLabel(this);
        field2Label = new QLabel(this);
        field3Label = new QLabel(this);
        field4Label = new QLabel(this);

        if (type == "Article") {
            setupArticleFields();
        }
        else if (type == "Audio") {
            setupAudioFields();
        }
        else if (type == "Book") {
            setupBookFields();
        }
        else if (type == "Film") {
            setupFilmFields();
        }

        field1Layout->addWidget(field1Label);
        field1Layout->addWidget(field1Edit);
        field2Layout->addWidget(field2Label);
        field2Layout->addWidget(field2Edit);
        field3Layout->addWidget(field3Label);
        field3Layout->addWidget(field3Edit);
        field4Layout->addWidget(field4Label);
        field4Layout->addWidget(field4Edit);

        mainLayout->addLayout(field1Layout);
        mainLayout->addLayout(field2Layout);
        mainLayout->addLayout(field3Layout);
        mainLayout->addLayout(field4Layout);
    }

    void ModifyMediaDialogueWindow::setupArticleFields() {
        field1Label->setText("Journal Name:");
        field2Label->setText("Volume Number:");
        field3Label->setText("Page Count:");
        field4Label->setText("DOI:");

        field1Edit->setText(QString::fromStdString(originalJournalName));
        field2Edit->setText(QString::fromStdString(originalVolume));
        field3Edit->setText(QString::number(originalPageCount));
        field4Edit->setText(QString::fromStdString(originalDoi));

        // Set validator for page count
        field3Edit->setValidator(new QIntValidator(0, 999999, this));
    }

    void ModifyMediaDialogueWindow::setupAudioFields() {
        field1Label->setText("Duration (sec):");
        field2Label->setText("Format:");
        field3Label->setText("Album:");

        field1Edit->setText(QString::number(originalDuration));
        field2Edit->setText(QString::fromStdString(originalFormat));
        field3Edit->setText(QString::fromStdString(originalAlbum));

        // Nascondo il quarto campo che non viene usato
        field4Label->hide();
        field4Edit->hide();

        // Set validator for duration
        field1Edit->setValidator(new QIntValidator(0, 999999, this));
    }

    void ModifyMediaDialogueWindow::setupBookFields() {
        field1Label->setText("ISBN:");
        field2Label->setText("Page Count:");
        field3Label->setText("Publisher:");
        field4Label->setText("Genre:");

        field1Edit->setText(QString::fromStdString(originalIsbn));
        field2Edit->setText(QString::number(originalBookPageCount));
        field3Edit->setText(QString::fromStdString(originalPublisher));
        field4Edit->setText(QString::fromStdString(originalBookGenre));

        // Set validator for page count
        field2Edit->setValidator(new QIntValidator(0, 999999, this));
    }

    void ModifyMediaDialogueWindow::setupFilmFields() {
        field1Label->setText("Duration (min):");
        field2Label->setText("Budget ($):");
        field3Label->setText("Genre:");

        field1Edit->setText(QString::number(originalFilmDuration));
        field2Edit->setText(QString::number(originalBudget));
        field3Edit->setText(QString::fromStdString(originalFilmGenre));

        // Nascondo il quarto campo che non viene usato
        field4Label->hide();
        field4Edit->hide();

        // Set validators
        field1Edit->setValidator(new QIntValidator(1, 999999, this));  // Durata minima 1 minuto
        field2Edit->setValidator(new QDoubleValidator(0, 999999999.99, 2, this));
    }

    void ModifyMediaDialogueWindow::setupCoverImageSection() {
        coverImageLayout = new QHBoxLayout;
        coverImageLabel = new QLabel("Cover Image:", this);
        coverImagePreview = new QLabel(this);
        
        if (!originalCoverImage.empty()) {
            QImage image(QString::fromStdString(originalCoverImage));
            if (!image.isNull()) {
                coverImagePreview->setPixmap(QPixmap::fromImage(image).scaled(100, 100, Qt::KeepAspectRatio));
            }
        }
        
        coverImagePreview->setFixedSize(100, 100);
        coverImagePreview->setStyleSheet("border: 1px solid #ccc;");
        
        selectCoverButton = new QPushButton("Select Image", this);
        
        coverImageLayout->addWidget(coverImageLabel);
        coverImageLayout->addWidget(coverImagePreview);
        coverImageLayout->addWidget(selectCoverButton);
        mainLayout->addLayout(coverImageLayout);
    }

    void ModifyMediaDialogueWindow::setupButtons() {
        QHBoxLayout *buttonsLayout = new QHBoxLayout;
        discardButton = new QPushButton("Cancel", this);
        applyButton = new QPushButton("Apply", this);
        applyButton->setEnabled(false);

        buttonsLayout->addWidget(discardButton);
        buttonsLayout->addWidget(applyButton);
        mainLayout->addLayout(buttonsLayout);
    }

    void ModifyMediaDialogueWindow::connectSignals() {
        connect(nameLineEdit, &QLineEdit::textChanged, this, &ModifyMediaDialogueWindow::afterTextChanged);
        connect(descriptionLineEdit, &QLineEdit::textChanged, this, &ModifyMediaDialogueWindow::afterTextChanged);
        connect(authorLineEdit, &QLineEdit::textChanged, this, &ModifyMediaDialogueWindow::afterTextChanged);
        connect(field1Edit, &QLineEdit::textChanged, this, &ModifyMediaDialogueWindow::afterTextChanged);
        connect(field2Edit, &QLineEdit::textChanged, this, &ModifyMediaDialogueWindow::afterTextChanged);
        connect(field3Edit, &QLineEdit::textChanged, this, &ModifyMediaDialogueWindow::afterTextChanged);
        connect(field4Edit, &QLineEdit::textChanged, this, &ModifyMediaDialogueWindow::afterTextChanged);
        connect(selectCoverButton, &QPushButton::clicked, this, &ModifyMediaDialogueWindow::selectCoverImage);
        connect(discardButton, &QPushButton::clicked, this, &ModifyMediaDialogueWindow::discardChanges);
        connect(applyButton, &QPushButton::clicked, this, &ModifyMediaDialogueWindow::applySlot);
    }

    // Check if any fields have been modified
    bool ModifyMediaDialogueWindow::differentFromOriginal()
    {
        if (nameLineEdit->text().toStdString() != originalMediaName ||
            descriptionLineEdit->text().toStdString() != originalMediaDescription ||
            authorLineEdit->text().toStdString() != originalMediaAuthor ||
            (type == "Film" && productionCompanyLineEdit && 
             productionCompanyLineEdit->text().toStdString() != originalProductionCompany) ||
            (selectedCoverPath != QString::fromStdString(originalCoverImage) && !selectedCoverPath.isEmpty()))
        {
            return true;
        }

        // Check media type specific fields
        if (type == "Article") {
            if (field1Edit->text().toStdString() != originalJournalName ||
                field2Edit->text().toStdString() != originalVolume ||
                field3Edit->text().toUInt() != originalPageCount ||
                field4Edit->text().toStdString() != originalDoi)
            {
                return true;
            }
        }
        else if (type == "Audio") {
            if (field1Edit->text().toUInt() != originalDuration ||
                field2Edit->text().toStdString() != originalFormat ||
                field3Edit->text().toStdString() != originalAlbum)
            {
                return true;
            }
        }
        else if (type == "Book") {
            if (field1Edit->text().toStdString() != originalIsbn ||
                field2Edit->text().toUInt() != originalBookPageCount ||
                field3Edit->text().toStdString() != originalPublisher ||
                field4Edit->text().toStdString() != originalBookGenre)
            {
                return true;
            }
        }
        else if (type == "Film") {
            if (field1Edit->text().toUInt() != originalFilmDuration ||
                field2Edit->text().toDouble() != originalBudget ||
                field3Edit->text().toStdString() != originalFilmGenre)
            {
                return true;
            }
        }

        return false;
    }

    void ModifyMediaDialogueWindow::selectCoverImage()
    {
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Select Cover Image"), "",
            tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
        
        if (!fileName.isEmpty()) {
            QImage image(fileName);
            if (!image.isNull()) {
                QString relativePath = copyImageToProjectAndGetPath(fileName);
                if (!relativePath.isEmpty()) {
                    selectedCoverPath = relativePath;
                    coverImagePreview->setPixmap(QPixmap::fromImage(image).scaled(
                        coverImagePreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    afterTextChanged();
                } else {
                    QMessageBox::critical(this, "Error", "Failed to save the image!");
                }
            } else {
                QMessageBox::critical(this, "Error", "Failed to load the selected image!");
            }
        }
    }

    QString ModifyMediaDialogueWindow::copyImageToProjectAndGetPath(const QString& originalImagePath) {
        if (originalImagePath.isEmpty())
            return QString();

        // Create a unique filename with timestamp
        QFileInfo originalFile(originalImagePath);
        QString newFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_") + 
                            originalFile.fileName();
        
        // Get the project root directory (where src folder is)
        QDir projectDir(QCoreApplication::applicationDirPath());
        projectDir.cdUp(); // up from MacOS
        projectDir.cdUp(); // up from Contents
        projectDir.cdUp(); // up from WhiskerShelf.app
        
        // Create images directory if it doesn't exist
        QString imagesDir = projectDir.absolutePath() + "/images";
        QDir().mkpath(imagesDir);
        
        QString destinationPath = imagesDir + "/" + newFileName;
        
        // If the destination file already exists, remove it
        if (QFile::exists(destinationPath)) {
            QFile::remove(destinationPath);
        }
        
        // Copy the file
        if (!QFile::copy(originalImagePath, destinationPath))
            return QString();
            
        return "../../../images/" + newFileName;
    }

    // Enables the apply button if there are any changes to apply.
    void ModifyMediaDialogueWindow::afterTextChanged()
    {
        // Check if there are any changes
        if (differentFromOriginal()) {
            applyButton->setEnabled(true);
        } else {
            applyButton->setEnabled(false);
        }
    }

    // Emits the saveModify signal to apply the changes and closes the dialog.
    void ModifyMediaDialogueWindow::applySlot()
    {
        // Check if all common text fields are filled
        if (nameLineEdit->text().isEmpty() || descriptionLineEdit->text().isEmpty() || authorLineEdit->text().isEmpty() ||
            (type == "Film" && productionCompanyLineEdit && productionCompanyLineEdit->text().isEmpty()))
        {
            QMessageBox::critical(this, "Error", type == "Film" ? 
                "Name, description, author and production company are required!" :
                "Name, description and author are required!");
            return;
        }

        // Check if media type specific fields are filled and valid
        if (!validateMediaTypeSpecificFields())
        {
            return;
        }

        // Store all values before closing the dialog
        std::string name = nameLineEdit->text().toStdString();
        std::string description = descriptionLineEdit->text().toStdString();
        std::string author = authorLineEdit->text().toStdString();
        std::string coverImage = selectedCoverPath.toStdString();
        if (coverImage.empty()) {
            coverImage = originalCoverImage;
        }

        // Create a map of media-specific fields
        std::map<std::string, std::variant<std::string, unsigned int, double>> mediaFields;
        if (type == "Article") {
            mediaFields["journalName"] = field1Edit->text().toStdString();
            mediaFields["volumeNumber"] = field2Edit->text().toStdString();
            mediaFields["pageCount"] = static_cast<unsigned int>(field3Edit->text().toUInt());
            mediaFields["doi"] = field4Edit->text().toStdString();
        } 
        else if (type == "Audio") {
            mediaFields["duration"] = static_cast<unsigned int>(field1Edit->text().toUInt());
            mediaFields["format"] = field2Edit->text().toStdString();
            mediaFields["album"] = field3Edit->text().toStdString();
        }
        else if (type == "Book") {
            mediaFields["isbn"] = field1Edit->text().toStdString();
            mediaFields["pageCount"] = static_cast<unsigned int>(field2Edit->text().toUInt());
            mediaFields["publisher"] = field3Edit->text().toStdString();
            mediaFields["genre"] = field4Edit->text().toStdString();
        }
        else if (type == "Film") {
            mediaFields["productionCompany"] = productionCompanyLineEdit->text().toStdString();
            mediaFields["duration"] = static_cast<unsigned int>(field1Edit->text().toUInt());
            mediaFields["budget"] = field2Edit->text().toDouble();
            mediaFields["genre"] = field3Edit->text().toStdString();
        }

        // First accept the dialog (this will close it)
        QDialog::accept();
        
        // Then emit the signal with the stored values
        emit saveModify(name, description, author, mediaFields, coverImage);
    }

    // Apply changes to the media - used for name validation
    void ModifyMediaDialogueWindow::applyChanges([[maybe_unused]] const std::vector<Media::AbstractMedia *> medias)
    {
        // When we receive the validation result, emit applySignal
        emit applySignal();
    }

    bool ModifyMediaDialogueWindow::validateMediaTypeSpecificFields()
    {
        // Controlliamo i campi in base al tipo di media
        if (type == "Article") {
            if (field1Edit->text().isEmpty() || field2Edit->text().isEmpty() ||
                field3Edit->text().isEmpty() || field4Edit->text().isEmpty())
            {
                QMessageBox::critical(this, "Error", "Journal name, volume number, page count and DOI are required!");
                return false;
            }
        }
        else if (type == "Audio") {
            if (field1Edit->text().isEmpty() || field2Edit->text().isEmpty() ||
                field3Edit->text().isEmpty())
            {
                QMessageBox::critical(this, "Error", "Duration, format and album are required!");
                return false;
            }
        }
        else if (type == "Book") {
            if (field1Edit->text().isEmpty() || field2Edit->text().isEmpty() ||
                field3Edit->text().isEmpty() || field4Edit->text().isEmpty())
            {
                QMessageBox::critical(this, "Error", "ISBN, page count, publisher and genre are required!");
                return false;
            }
        }
        else if (type == "Film") {
            if (field1Edit->text().isEmpty() || field2Edit->text().isEmpty() ||
                field3Edit->text().isEmpty())
            {
                QMessageBox::critical(this, "Error", "Duration, budget and genre are required!");
                return false;
            }
        }

        return true;
    }

    // If there are modified fields, show a confirmation dialog
    // If confirmed, reject the dialog to close it
    // If not confirmed or there are no modified fields, reject the dialog to close it
    void ModifyMediaDialogueWindow::discardChanges()
    {
        if (differentFromOriginal()) {
            QMessageBox::StandardButton reply = QMessageBox::question(
                this, "Discard changes?", "Are you sure you want to discard the changes?",
                QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                reject();
            }
        } else {
            reject();
        }
    }

    // Free up memory when the dialog is destroyed
    ModifyMediaDialogueWindow::~ModifyMediaDialogueWindow()
    {
        // Delete labels
        delete nameLabel;
        delete descriptionLabel;
        delete authorLabel;
        delete field1Label;
        delete field2Label;
        if (type != "Audio") {
            delete field3Label;
            delete field3Edit;
        }
        delete field4Label;
        delete coverImageLabel;
        delete coverImagePreview;

        // Delete input fields
        delete nameLineEdit;
        delete descriptionLineEdit;
        delete authorLineEdit;
        delete field1Edit;
        delete field2Edit;
        delete field4Edit;

        // Delete buttons
        delete discardButton;
        delete applyButton;
        delete selectCoverButton;

        // Delete layouts
        delete nameLayout;
        delete descriptionLayout;
        delete authorLayout;
        delete value1Layout;
        delete value2Layout;
        delete value3Layout;
        delete value4Layout;
        delete coverImageLayout;

        // Delete main layout
        delete mainLayout;
    }

}

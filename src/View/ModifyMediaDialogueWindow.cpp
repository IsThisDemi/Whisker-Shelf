#include "ModifyMediaDialogueWindow.h"

namespace View
{

    // This is the constructor of the ModifyMediaDialogueWindow class
    ModifyMediaDialogueWindow::ModifyMediaDialogueWindow(const unsigned int &Id, const std::string &Type, const std::string &OriginalMediaName, const std::string &OriginalMediaDescription,
                                                           const std::string &OriginalMediaBrand, const double &OriginalValue1, const double &OriginalValue2,
                                                           const std::string &OriginalValue3, const double &OriginalValue4, AbstractDialogueWindow *parent)
        : AbstractDialogueWindow(parent), id(Id), type(Type), originalMediaName(OriginalMediaName), originalMediaDescription(OriginalMediaDescription),
          originalMediaBrand(OriginalMediaBrand), originalValue1(OriginalValue1), originalValue2(OriginalValue2), originalValue3(OriginalValue3), originalValue4(OriginalValue4)
    {
        // Set the title of the window
        setWindowTitle("Modify media");

        // Create a vertical layout for the main window
        mainLayout = new QVBoxLayout(this);

        // Create a horizontal layout for the name field
        nameLayout = new QHBoxLayout;
        nameLabel = new QLabel("Name:", this);
        nameLineEdit = new QLineEdit(QString::fromStdString(originalMediaName), this);
        nameLineEdit->setFixedSize(193, 26);
        nameLayout->addWidget(nameLabel);
        nameLayout->addWidget(nameLineEdit);

        // Create a horizontal layout for the description field
        descriptionLayout = new QHBoxLayout;
        descriptionLabel = new QLabel("Description:", this);
        descriptionLineEdit = new QLineEdit(QString::fromStdString(originalMediaDescription), this);
        descriptionLineEdit->setFixedSize(193, 26);
        descriptionLayout->addWidget(descriptionLabel);
        descriptionLayout->addWidget(descriptionLineEdit);

        // Create a horizontal layout for the brand field
        brandLayout = new QHBoxLayout;
        brandLabel = new QLabel("Brand:", this);
        brandLineEdit = new QLineEdit(QString::fromStdString(originalMediaBrand), this);
        brandLineEdit->setFixedSize(193, 26);
        brandLayout->addWidget(brandLabel);
        brandLayout->addWidget(brandLineEdit);

        // Create a horizontal layout for the value1 field
        value1LineEdit = new QLineEdit(QString::number(originalValue1), this);
        value1Layout = new QHBoxLayout;
        if (type == "Article" || type == "Book") {
            value1Label = new QLabel("Page Count:", this);
        } else if (type == "Audio" || type == "Film") {
            value1Label = new QLabel("Duration:", this);
        }
        value1LineEdit->setFixedSize(193, 26);
        value1Layout->addWidget(value1Label);
        value1Layout->addWidget(value1LineEdit);

        // Create a horizontal layout for the value2 field
        value2LineEdit = new QLineEdit(QString::number(originalValue2), this);
        value2Layout = new QHBoxLayout;
        if (type == "Article" || type == "Book") {
            value2Label = new QLabel("Page Count:", this);
            value2LineEdit->setEnabled(false);
            value2LineEdit->setObjectName("valueLineEditDisabled");
        } else if (type == "Audio" || type == "Film") {
            value2Label = new QLabel("Duration:", this);
            value2LineEdit->setEnabled(false);
            value2LineEdit->setObjectName("valueLineEditDisabled");
        }
        value2LineEdit->setFixedSize(193, 26);
        value2Layout->addWidget(value2Label);
        value2Layout->addWidget(value2LineEdit);

        // Create a horizontal layout for the value3 field
        value3LineEdit = new QLineEdit(QString::fromStdString(originalValue3), this);
        value3LineEdit->hide();
        value3Layout = new QHBoxLayout;
        if (type == "Article" || type == "Book") {
            value3Label = new QLabel("", this);
        } else if (type == "Audio") {
            value3Label = new QLabel("Format:", this);
            value3Layout->addWidget(value3Label);
            value3Layout->addWidget(value3LineEdit);
            value3LineEdit->show();
        } else if (type == "Film") {
            value3Label = new QLabel("Genre:", this);
            value3Layout->addWidget(value3Label);
            value3Layout->addWidget(value3LineEdit);
            value3LineEdit->show();
        }
        value3LineEdit->setFixedSize(193, 26);

        // Create a horizontal layout for the value4 field
        value4LineEdit = new QLineEdit(QString::number(originalValue4), this);
        value4LineEdit->hide();
        value4Layout = new QHBoxLayout;
        if (type == "Film") {
            value4Label = new QLabel("Rating:", this);
            value4LineEdit->setEnabled(false);
            value4LineEdit->setObjectName("valueLineEditDisabled");
            value4LineEdit->show();
            value4Layout->addWidget(value4Label);
            value4Layout->addWidget(value4LineEdit);
        }
        value4LineEdit->setFixedSize(193, 26);

        // Create a horizontal layout for the buttons
        buttonsLayout = new QHBoxLayout;

        applyButton = new QPushButton("Done", this);
        applyButton->setShortcut(Qt::Key_Enter);
        connect(applyButton, &QPushButton::clicked, this, &ModifyMediaDialogueWindow::applySlot);

        discardButton = new QPushButton("Cancel", this);
        discardButton->setShortcut(Qt::Key_Escape);
        connect(discardButton, &QPushButton::clicked, this, &ModifyMediaDialogueWindow::discardChanges);

        buttonsLayout->addWidget(discardButton);
        buttonsLayout->addWidget(applyButton);

        // Add all the layouts to the main layout
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(descriptionLayout);
        mainLayout->addLayout(brandLayout);
        mainLayout->addLayout(value1Layout);
        mainLayout->addLayout(value2Layout);
        mainLayout->addLayout(value3Layout);
        mainLayout->addLayout(value4Layout);
        mainLayout->addLayout(buttonsLayout);

        // Set the layout of the main window
        setLayout(mainLayout);
    }

    // Check if any fields have been modified
    bool ModifyMediaDialogueWindow::differentFromOriginal()
    {
        // Get the text from the input fields
        std::string name = nameLineEdit->text().toStdString();
        std::string description = descriptionLineEdit->text().toStdString();
        std::string brand = brandLineEdit->text().toStdString();

        // Get the numerical values from the input fields
        double value1 = value1LineEdit->text().toDouble();
        double value2 = value2LineEdit->text().toDouble();
        std::string value3 = value3LineEdit->text().toStdString();
        double value4 = value4LineEdit->text().toDouble();

        // Check if any fields have been modified
        return (name != originalMediaName) ||
               (description != originalMediaDescription) ||
               (brand != originalMediaBrand) ||
               (value1 != originalValue1) ||
               (value2 != originalValue2) ||
               (value3 != originalValue3) ||
               (value4 != originalValue4);
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

     // Emits the applySignal to apply the changes.
    void ModifyMediaDialogueWindow::applySlot()
    {
        emit applySignal();
    }

    // Apply changes to the media
    void ModifyMediaDialogueWindow::applyChanges(const std::vector<Media::AbstractMedia *> medias)
    {
        // Check if all text fields are filled
        if (nameLineEdit->text().isEmpty() || descriptionLineEdit->text().isEmpty() || brandLineEdit->text().isEmpty() ||
            value1LineEdit->text().isEmpty() || value2LineEdit->text().isEmpty() /*|| value3LineEdit->text().isEmpty() || value4LineEdit->text().isEmpty()*/)
        {
            QMessageBox::critical(this, "Error", "Not all text fields are filled!");
            return;
        }

        // Convert text fields to appropriate data types
        std::string name = nameLineEdit->text().toStdString();
        std::string description = descriptionLineEdit->text().toStdString();
        std::string brand = brandLineEdit->text().toStdString();
        double value1 = value1LineEdit->text().toDouble();
        double value2 = value2LineEdit->text().toDouble();
        std::string value3 = value3LineEdit->text().toStdString();
        double value4 = value4LineEdit->text().toDouble();

        // Check if the values are numeric
        if (!(value1LineEdit->hasAcceptableInput() && value2LineEdit->hasAcceptableInput() && value4LineEdit->hasAcceptableInput()))
        {
            QMessageBox::critical(this, "Error", "Values must be numeric!");
            return;
        }

        // Check if the name is modified
        bool isNameModified = (name != originalMediaName);

        // Check if the name is unique
        if (isNameModified)
        {
            for (Media::AbstractMedia *media : medias)
            {
                if (media->getId() != id && media->getTitle() == name)
                {
                    QMessageBox::critical(this, "Error", "A media with that name already exists!");
                    return;
                }
            }
        }

        // Validate values based on media type
        if (type == "Article" || type == "Book")
        {
            // Validate page count
            if (value1 < 1)
            {
                QMessageBox::critical(this, "Error", "Page count must be at least 1");
                return;
            }
        }
        else if (type == "Audio" || type == "Film")
        {
            // Validate duration
            if (value1 < 0)
            {
                QMessageBox::critical(this, "Error", "Duration cannot be negative");
                return;
            }

            if (type == "Film")
            {
                // Validate rating for films
                if (value4 != originalValue4 && (value4 < 0.0 || value4 > 10.0))
                {
                    QMessageBox::critical(this, "Error", "Rating must be between 0.0 and 10.0");
                    return;
                }
            }
        }

        // Emit signal with modified media details
        emit mediaModified(name, description, brand, value1, value2, value3, value4);

        // Emit signal if the name is modified
        if (isNameModified)
            emit mediaNameModified(originalMediaName, name);

        // Close the dialog
        accept();
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
        delete nameLabel;
        delete descriptionLabel;
        delete brandLabel;
        delete value1Label;
        delete value2Label;
        delete value3Label;
        delete value4Label;

        delete nameLineEdit;
        delete descriptionLineEdit;
        delete brandLineEdit;
        delete value1LineEdit;
        delete value2LineEdit;
        delete value3LineEdit;
        delete value4LineEdit;

        delete discardButton;
        delete applyButton;

        delete nameLayout;
        delete descriptionLayout;
        delete brandLayout;
        delete value1Layout;
        delete value2Layout;
        delete value3Layout;
        delete value4Layout;

        delete buttonsLayout;
        delete mainLayout;
    }

}

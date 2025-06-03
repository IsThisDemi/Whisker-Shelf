#include "ModifySensorDialogueWindow.h"

namespace View
{

    // This is the constructor of the ModifySensorDialogueWindow class
    ModifySensorDialogueWindow::ModifySensorDialogueWindow(const unsigned int &Id, const std::string &Type, const std::string &OriginalSensorName, const std::string &OriginalSensorDescription,
                                                           const std::string &OriginalSensorBrand, const double &OriginalValue1, const double &OriginalValue2,
                                                           const std::string &OriginalValue3, const double &OriginalValue4, AbstractDialogueWindow *parent)
        : AbstractDialogueWindow(parent), id(Id), type(Type), originalSensorName(OriginalSensorName), originalSensorDescription(OriginalSensorDescription),
          originalSensorBrand(OriginalSensorBrand), originalValue1(OriginalValue1), originalValue2(OriginalValue2), originalValue3(OriginalValue3), originalValue4(OriginalValue4)
    {
        // Set the title of the window
        setWindowTitle("Modifica sensore");

        // Create a vertical layout for the main window
        mainLayout = new QVBoxLayout(this);

        // Create a horizontal layout for the name field
        nameLayout = new QHBoxLayout;
        nameLabel = new QLabel("Name:", this);
        nameLineEdit = new QLineEdit(QString::fromStdString(originalSensorName), this);
        nameLineEdit->setFixedSize(193, 26);
        nameLayout->addWidget(nameLabel);
        nameLayout->addWidget(nameLineEdit);

        // Create a horizontal layout for the description field
        descriptionLayout = new QHBoxLayout;
        descriptionLabel = new QLabel("Description:", this);
        descriptionLineEdit = new QLineEdit(QString::fromStdString(originalSensorDescription), this);
        descriptionLineEdit->setFixedSize(193, 26);
        descriptionLayout->addWidget(descriptionLabel);
        descriptionLayout->addWidget(descriptionLineEdit);

        // Create a horizontal layout for the brand field
        brandLayout = new QHBoxLayout;
        brandLabel = new QLabel("Brand:", this);
        brandLineEdit = new QLineEdit(QString::fromStdString(originalSensorBrand), this);
        brandLineEdit->setFixedSize(193, 26);
        brandLayout->addWidget(brandLabel);
        brandLayout->addWidget(brandLineEdit);

        // Create a horizontal layout for the value1 field
        value1LineEdit = new QLineEdit(QString::number(originalValue1), this);
        value1Layout = new QHBoxLayout;
        if (type == "Humidity" || type == "Temperature" || type == "Wind") {
            value1Label = new QLabel("Accuracy:", this);
            value1LineEdit->setEnabled(false);
            value1LineEdit->setObjectName("valueLineEditDisabled");
        } else if (type == "Light") {
            value1Label = new QLabel("Intensity:", this);
        }
        value1LineEdit->setFixedSize(193, 26);
        value1Layout->addWidget(value1Label);
        value1Layout->addWidget(value1LineEdit);

        // Create a horizontal layout for the value2 field
        value2LineEdit = new QLineEdit(QString::number(originalValue2), this);
        value2Layout = new QHBoxLayout;
        if (type == "Humidity") {
            value2Label = new QLabel("Humidity:", this);
            value2LineEdit->setEnabled(false);
            value2LineEdit->setObjectName("valueLineEditDisabled");
        } else if (type == "Light") {
            value2Label = new QLabel("Signal Strength:", this);
            value2LineEdit->setEnabled(false);
            value2LineEdit->setObjectName("valueLineEditDisabled");
        } else if (type == "Temperature") {
            value2Label = new QLabel("Temperature:", this);
            value2LineEdit->setEnabled(false);
            value2LineEdit->setObjectName("valueLineEditDisabled");
        } else if (type == "Wind") {
            value2Label = new QLabel("Direction:", this);
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
        if (type == "Humidity") {
            value3Label = new QLabel("", this);
        } else if (type == "Light") {
            value3Label = new QLabel("Color:", this);
            value3Layout->addWidget(value3Label);
            value3Layout->addWidget(value3LineEdit);
            value3LineEdit->show();
        } else if (type == "Temperature") {
            value3Label = new QLabel("Unit:", this);
            value3Layout->addWidget(value3Label);
            value3Layout->addWidget(value3LineEdit);
            value3LineEdit->show();
        } else if (type == "Wind") {
            value3Label = new QLabel("Unit:", this);
            value3Layout->addWidget(value3Label);
            value3Layout->addWidget(value3LineEdit);
            value3LineEdit->show();
        }
        value3LineEdit->setFixedSize(193, 26);

        // Create a horizontal layout for the value4 field
        value4LineEdit = new QLineEdit(QString::number(originalValue4), this);
        value4LineEdit->hide();
        value4Layout = new QHBoxLayout;
        if (type == "Humidity") {
            value4Label = new QLabel("", this);
            value4Layout->addWidget(value4Label);
        } else if (type == "Light") {
            value4Label = new QLabel("", this);
            value4Layout->addWidget(value4Label);
        } else if (type == "Temperature") {
            value4Label = new QLabel("", this);
            value4Layout->addWidget(value4Label);
        } else if (type == "Wind") {
            value4Label = new QLabel("Speed:", this);
            value4LineEdit->setEnabled(false);
            value4LineEdit->setObjectName("valueLineEditDisabled");
            value4LineEdit->show();
            value4Layout->addWidget(value4Label);
            value4Layout->addWidget(value4LineEdit);
        }
        value4LineEdit->setFixedSize(193, 26);

        // Create a horizontal layout for the buttons
        buttonsLayout = new QHBoxLayout;

        applyButton = new QPushButton("Fatto", this);
        applyButton->setShortcut(Qt::Key_Enter);
        connect(applyButton, &QPushButton::clicked, this, &ModifySensorDialogueWindow::applySlot);

        discardButton = new QPushButton("Annulla", this);
        discardButton->setShortcut(Qt::Key_Escape);
        connect(discardButton, &QPushButton::clicked, this, &ModifySensorDialogueWindow::discardChanges);

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
    bool ModifySensorDialogueWindow::differentFromOriginal()
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
        return (name != originalSensorName) ||
               (description != originalSensorDescription) ||
               (brand != originalSensorBrand) ||
               (value1 != originalValue1) ||
               (value2 != originalValue2) ||
               (value3 != originalValue3) ||
               (value4 != originalValue4);
    }

    // Enables the apply button if there are any changes to apply.
    void ModifySensorDialogueWindow::afterTextChanged()
    {
        // Check if there are any changes
        if (differentFromOriginal()) {
            applyButton->setEnabled(true);
        } else {
            applyButton->setEnabled(false);
        }
    }

     // Emits the applySignal to apply the changes.
    void ModifySensorDialogueWindow::applySlot()
    {
        emit applySignal();
    }

    // Apply changes to the sensor
    void ModifySensorDialogueWindow::applyChanges(const std::vector<Sensor::AbstractSensor *> sensors)
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
        bool isNameModified = (name != originalSensorName);

        // Check if the name is unique
        if (isNameModified)
        {
            for (Sensor::AbstractSensor *sensor : sensors)
            {
                if (sensor->getId() != id && sensor->getName() == name)
                {
                    QMessageBox::critical(this, "Error", "A sensor with that name already exists!");
                    return;
                }
            }
        }

        // Validate Value1
        if (value1 != originalValue1 && (value1 < 1.0 || value1 > 100.0))
        {
            QMessageBox::critical(this, "Error", "Value1 must be between 1.0 and 100.0");
            return;
        }

        // Validate Value2
        if (value2 != originalValue2 && (value2 < 1.0 || value2 > 100.0))
        {
            QMessageBox::critical(this, "Error", "Value2 must be between 1.0 and 100.0");
            return;
        }

        // Validate Value3
        if (value3 != originalValue3 && (!std::regex_match(value3, std::regex("^#[0-9a-fA-F]{6}$"))) &&
            (value3 != "km/h" && value3 != "m/s" && value3 != "mph" && value3 != "C" && value3 != "F" && value3 != "K"))
        {
            QMessageBox::critical(this, "Error", "Please for Light sensor use a hexadecimal color code or one of the following units for Wind and Temperature sensors: km/h, m/s, mph, C, F, K");
            return;
        }

        // Validate Value4
        if (value4 != originalValue4 && (value4 < 1.0 || value4 > 10.0))
        {
            QMessageBox::critical(this, "Error", "Variance must be between 1.0 and 10.0");
            return;
        }

        // Emit signal with modified sensor details
        emit sensorModified(name, description, brand, value1, value2, value3, value4);

        // Emit signal if the name is modified
        if (isNameModified)
            emit sensorNameModified(originalSensorName, name);

        // Close the dialog
        accept();
    }

    // If there are modified fields, show a confirmation dialog
    // If confirmed, reject the dialog to close it
    // If not confirmed or there are no modified fields, reject the dialog to close it
    void ModifySensorDialogueWindow::discardChanges()
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
    ModifySensorDialogueWindow::~ModifySensorDialogueWindow()
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

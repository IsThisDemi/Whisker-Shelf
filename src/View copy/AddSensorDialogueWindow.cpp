#include "AddSensorDialogueWindow.h"

namespace View
{
    // AddSensorDialogueWindow constructor
    // Set window title, create layouts, add widgets and connect signals
    AddSensorDialogueWindow::AddSensorDialogueWindow(AbstractDialogueWindow* parent)
        : AbstractDialogueWindow(parent)
    {
        setWindowTitle("Add a new sensor");

        // Create main layout
        mainLayout = new QVBoxLayout(this);
        mainLayout->setObjectName("AddSensorDialogueWindow");

        // Create type layout
        typeLayout = new QHBoxLayout;
        typeLabel = new QLabel("Type:", this);
        typeComboBox = new QComboBox(this);
        typeComboBox->addItem("Humidity");
        typeComboBox->addItem("Light");
        typeComboBox->addItem("Temperature");
        typeComboBox->addItem("Wind");
        typeLayout->addWidget(typeLabel);
        typeLayout->addWidget(typeComboBox);

        // Create id layout
        idLayout = new QHBoxLayout;
        idLabel = new QLabel("ID:", this);
        idLineEdit = new QLineEdit(this);
        idLineEdit->setFixedSize(193, 26);
        idLayout->addWidget(idLabel);
        idLayout->addWidget(idLineEdit);

        // Create name layout
        nameLayout = new QHBoxLayout;
        nameLabel = new QLabel("Name:", this);
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

        // Create brand layout
        brandLayout = new QHBoxLayout;
        brandLabel = new QLabel("Brand:", this);
        brandLineEdit = new QLineEdit(this);
        brandLineEdit->setFixedSize(193, 26);
        brandLayout->addWidget(brandLabel);
        brandLayout->addWidget(brandLineEdit);

        // Create buttons layout
        buttonsLayout = new QHBoxLayout;

        // Create create button
        createButton = new QPushButton("Add", this);
        createButton->setShortcut(Qt::Key_Enter);
        connect(createButton, &QPushButton::clicked, this, &AddSensorDialogueWindow::createAndAddSlot);

        // Create discard button
        discardButton = new QPushButton("Cancel", this);
        discardButton->setShortcut(Qt::Key_Escape);
        connect(discardButton, &QPushButton::clicked, this, &AddSensorDialogueWindow::discardChanges);

        // Add buttons to layout
        buttonsLayout->addWidget(discardButton);
        buttonsLayout->addWidget(createButton);

        // Add layouts to main layout
        mainLayout->addLayout(typeLayout);
        mainLayout->addLayout(idLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(descriptionLayout);
        mainLayout->addLayout(brandLayout);
        mainLayout->addLayout(buttonsLayout);

        // Set main layout as window layout
        setLayout(mainLayout);
    }

    // Check if the new sensor is different from the original
    bool AddSensorDialogueWindow::differentFromOriginal() {
        // If all fields are empty or the default option is selected, it's not different from the original, otherwise it is
        return !(typeComboBox->currentIndex() == 0 &&
                 idLineEdit->text().isEmpty() &&
                 nameLineEdit->text().isEmpty() &&
                 descriptionLineEdit->text().isEmpty() &&
                 brandLineEdit->text().isEmpty());
    }

    // Emit signal to start adding a new sensor
    void AddSensorDialogueWindow::createAndAddSlot()
    {
        // Emit signal to start adding a new sensor
        emit createAndAddSignal();
    }

    // Create and add a new sensor to the list of sensors
    void AddSensorDialogueWindow::createAndAddSensor(const std::vector<Sensor::AbstractSensor *> &sensors) {
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
        std::string name = nameLineEdit->text().toStdString();
        std::string description = descriptionLineEdit->text().toStdString();
        std::string brand = brandLineEdit->text().toStdString();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> hundred_dis(0.0, 100.0);
        std::uniform_real_distribution<> direction_dis(0.0, 360.0);

        if (name.empty() || description.empty() || brand.empty()) {
            QMessageBox::critical(this, "Error", "Id, name, description and brand values cannot be empty!");
            return;
        }
        for (Sensor::AbstractSensor *sensor : sensors) {
            if (sensor->getId() == id) {
                QMessageBox::critical(this, "Error", "ID already in use");
                return;
            }
            if (sensor->getName() == name) {
                QMessageBox::critical(this, "Error", "Name already in use");
                return;
            }
        }
        std::string type = typeComboBox->currentText().toStdString();
        Sensor::AbstractSensor *sensor;
        if (type == "Humidity") {
            sensor = new Sensor::Humidity(id, name, description, brand, std::floor(hundred_dis(gen) * 100 + 0.5) / 100.0, std::floor(hundred_dis(gen) * 100 + 0.5) / 100.0);
        } else if (type == "Light") {
            sensor = new Sensor::Light(id, name, description, brand, std::floor(hundred_dis(gen) * 100 + 0.5) / 100.0, "#000000", std::floor(hundred_dis(gen) * 100 + 0.5) / 100.0);
        } else if (type == "Temperature") {
            sensor = new Sensor::Temperature(id, name, description, brand, std::floor(hundred_dis(gen) * 100 + 0.5) / 100.0, "C", std::floor(hundred_dis(gen) * 100 + 0.5) / 100.0);
        } else {
            sensor = new Sensor::Wind(id, name, description, brand, std::floor(hundred_dis(gen) * 100 + 0.5) / 100.0, "Km/h", std::floor(direction_dis(gen) * 100 + 0.5) / 100.0, std::floor(hundred_dis(gen) * 100 + 0.5) / 100.0);
        }
        emit sensorAdded(sensor);
    }

    // Discard changes and close the dialog if there are changes
    void AddSensorDialogueWindow::discardChanges()
    {
        if (differentFromOriginal()) {
            QMessageBox::StandardButton reply = QMessageBox::question(
                this, "Discard changes?",
                "Are you sure you want to discard the changes?",
                QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) reject();
        } else reject();
    }

    // Destructor of the AddSensorDialogueWindow class
    // Deletes all dynamically allocated UI elements
    AddSensorDialogueWindow::~AddSensorDialogueWindow() {
        delete typeLabel;
        delete idLabel;
        delete nameLabel;
        delete descriptionLabel;
        delete brandLabel;

        delete typeComboBox;
        delete idLineEdit;
        delete nameLineEdit;
        delete descriptionLineEdit;
        delete brandLineEdit;

        delete discardButton;
        delete createButton;

        delete typeLayout;
        delete idLayout;
        delete nameLayout;
        delete descriptionLayout;
        delete brandLayout;
        delete buttonsLayout;
        delete mainLayout;
    }

}

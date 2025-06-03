// The AboveChartWidget class is a widget that displays above a chart all the
// necessary information about the sensor.

#include "AboveChartWidget.h"
#include "AboveChartLabelsCreatorVisitor.h"
#include <stdexcept>

namespace View
{

    // Constructor that initializes the widget and creates the grey panel.
    AboveChartWidget::AboveChartWidget(QWidget *parent) : QWidget(parent),
                                                          greyPanel(nullptr),
                                                          layout(nullptr),
                                                          sensorNameLabel(nullptr),
                                                          sensorIDLabel(nullptr),
                                                          sensorDescriptionLabel(nullptr),
                                                          sensorBrandLabel(nullptr),
                                                          sensorValue1Label(nullptr),
                                                          sensorValue2Label(nullptr),
                                                          sensorValue3Label(nullptr),
                                                          sensorValue4Label(nullptr),
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
        delete sensorNameLabel;
        delete sensorIDLabel;
        delete sensorDescriptionLabel;
        delete sensorBrandLabel;
        delete sensorValue1Label;
        delete sensorValue2Label;
        delete sensorValue3Label;
        delete sensorValue4Label;
        delete simulateButton;
        delete modifyButton;
        delete deleteButton;
        delete modifyWindow;
        delete layout;

        // Set all pointers to nullptr.
        greyPanel = nullptr;
        sensorNameLabel = nullptr;
        sensorIDLabel = nullptr;
        sensorDescriptionLabel = nullptr;
        sensorBrandLabel = nullptr;
        sensorValue1Label = nullptr;
        sensorValue2Label = nullptr;
        sensorValue3Label = nullptr;
        sensorValue4Label = nullptr;
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

    void AboveChartWidget::createAboveChartForSensor(Sensor::AbstractSensor *sensor)
    {
        // Remove dynamically allocated objects from before.
        delete greyPanel;
        delete sensorNameLabel;
        delete sensorIDLabel;
        delete sensorDescriptionLabel;
        delete sensorBrandLabel;
        delete sensorValue1Label;
        delete sensorValue2Label;
        delete sensorValue3Label;
        delete sensorValue4Label;
        delete simulateButton;
        delete modifyButton;
        delete deleteButton;
        delete modifyWindow;
        delete layout;

        // Set pointers to nullptr.
        greyPanel = nullptr;
        sensorNameLabel = nullptr;
        sensorIDLabel = nullptr;
        sensorDescriptionLabel = nullptr;
        sensorBrandLabel = nullptr;
        sensorValue1Label = nullptr;
        sensorValue2Label = nullptr;
        sensorValue3Label = nullptr;
        sensorValue4Label = nullptr;
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

        // Create labels for sensor data.
        sensorNameLabel = new QLabel(QString::fromStdString(sensor->getName()), this);
        QFont fontLabel = QFont();
        fontLabel.setPointSize(20);

        sensorIDLabel = new QLabel(QString("ID: %1").arg(sensor->getId()), this);
        sensorIDLabel->setFont(fontLabel);

        sensorDescriptionLabel = new QLabel(QString("Description: %1").arg(QString::fromStdString(sensor->getDescription())), this);
        sensorDescriptionLabel->setFont(fontLabel);
        sensorDescriptionLabel->setWordWrap(true);

        sensorBrandLabel = new QLabel(QString("Brand: %1").arg(QString::fromStdString(sensor->getBrand())), this);
        sensorBrandLabel->setFont(fontLabel);
        sensorDescriptionLabel->setWordWrap(true);

        AboveChartLabelsCreatorVisitor aboveChartLabelsCreatorVisitor(this);
        sensor->accept(aboveChartLabelsCreatorVisitor);

        // Set font size for sensor name label.
        QFont fontTitle = sensorNameLabel->font();
        fontTitle.setPointSize(36);
        sensorNameLabel->setFont(fontTitle);
        sensorNameLabel->setObjectName("sensorNameLabel");

        // Create layouts to organize widgets.
        layout = new QGridLayout(this);

        // Add widgets to the data layout.
        layout->addWidget(sensorNameLabel, 0, 0);
        layout->addWidget(modifyButton, 0, 1);
        layout->addWidget(deleteButton, 0, 2);
        layout->addWidget(simulateButton, 0, 3);
        layout->addWidget(sensorIDLabel, 1, 0);
        layout->addWidget(sensorBrandLabel, 1, 1);
        layout->addWidget(sensorDescriptionLabel, 1, 2, 3, 2, Qt::AlignTop);
        layout->addWidget(sensorValue1Label, 2, 0);
        layout->addWidget(sensorValue2Label, 3, 0);
        layout->addWidget(sensorValue3Label, 2, 1);
        layout->addWidget(sensorValue4Label, 3, 1);

        // Set the main layout for the widget.
        setLayout(layout);

        // Connect button signals to slots.
        connect(simulateButton, &QPushButton::clicked, this, &AboveChartWidget::simulateSlot);
        connect(modifyButton, &QPushButton::clicked, this, &AboveChartWidget::modifySlot);
        connect(deleteButton, &QPushButton::clicked, this, &AboveChartWidget::deleteSlot);
    }

    // Create the rest of labels for Humidity
    void AboveChartWidget::createTheRestOfLabelsHumidity(const double &accuracy, const double &humidity)
    {
        QFont font;
        font.setPointSize(20);

        sensorValue1Label = new QLabel(QString("Accuracy: %1").arg(QString::number(accuracy)) + " %", this);
        sensorValue1Label->setFont(font);
        sensorValue2Label = new QLabel(QString("Humidity: %1").arg(QString::number(humidity)) + " %", this);
        sensorValue2Label->setFont(font);
    }

    // Create the rest of labels for Light
    void AboveChartWidget::createTheRestOfLabelsLight(const std::string &color, const double &intensity, const double &signalStrength)
    {
        QFont font;
        font.setPointSize(20);

        sensorValue1Label = new QLabel(QString("Intensity: %1").arg(QString::number(intensity)) + " %", this);
        sensorValue1Label->setFont(font);
        sensorValue2Label = new QLabel(QString("Signal Strength: %1").arg(QString::number(signalStrength)) + " %", this);
        sensorValue2Label->setFont(font);
        sensorValue3Label = new QLabel(QString("Color: %1").arg(QString::fromStdString(color)), this);
        sensorValue3Label->setFont(font);
    }

    // Create the rest of labels for Temperature
    void AboveChartWidget::createTheRestOfLabelsTemperature(const double &accuracy, const double &temperature, const std::string &unit)
    {
        QFont font;
        font.setPointSize(20);

        sensorValue1Label = new QLabel(QString("Accuracy: %1").arg(QString::number(accuracy)) + " %", this);
        sensorValue1Label->setFont(font);
        sensorValue2Label = new QLabel(QString("Temperature: %1").arg(QString::number(temperature)) + " °", this);
        sensorValue2Label->setFont(font);
        sensorValue3Label = new QLabel(QString("Unit: %1").arg(QString::fromStdString(unit)), this);
        sensorValue3Label->setFont(font);
    }

    // Create the rest of labels for Wind
    void AboveChartWidget::createTheRestOfLabelsWind(const double &accuracy, const double &direction, const double &speed, const std::string &unit)
    {
        QFont font;
        font.setPointSize(20);

        sensorValue1Label = new QLabel(QString("Accuracy: %1").arg(QString::number(accuracy)) + " %", this);
        sensorValue1Label->setFont(font);
        sensorValue2Label = new QLabel(QString("Direction: %1").arg(QString::number(direction)) + " °", this);
        sensorValue2Label->setFont(font);
        sensorValue3Label = new QLabel(QString("Unit: %1").arg(QString::fromStdString(unit)), this);
        sensorValue3Label->setFont(font);
        sensorValue4Label = new QLabel(QString("Speed: %1").arg(QString::number(speed)), this);
        sensorValue4Label->setFont(font);
    }

    // Get the ID of the selected sensor
    unsigned int AboveChartWidget::getId() const
    {
        if (sensorIDLabel != nullptr)
        {
            bool ok = true;
            QString idText = sensorIDLabel->text();
            QString idSubstring = idText.mid(4);
            unsigned int id = idSubstring.toUInt(&ok);
            if (ok)
            {
                return id;
            }
            else
            {
                qWarning() << "Invalid sensor ID!";
                throw std::exception();
            }
        }
        else
        {
            qWarning() << "No sensor selected in AboveChartWidget!";
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
    void AboveChartWidget::modify(Sensor::AbstractSensor *sensor)
    {
        // Handle humidity sensor
        if (dynamic_cast<Sensor::Humidity *>(sensor))
        {
            Sensor::Humidity *humidity = static_cast<Sensor::Humidity *>(sensor);

            modifyWindow = new ModifySensorDialogueWindow(humidity->getId(), "Humidity", humidity->getName(), humidity->getDescription(), humidity->getBrand(),
                                                          humidity->getAccuracy(), humidity->getHumidity(), "", 0);

            connect(modifyWindow, &ModifySensorDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
            connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifySensorDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifySensorDialogueWindow::sensorModified, this, &AboveChartWidget::saveModifySlot);
            connect(modifyWindow, &ModifySensorDialogueWindow::sensorNameModified, this, &AboveChartWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
        // Handle light sensor
        else if (dynamic_cast<Sensor::Light *>(sensor))
        {
            Sensor::Light *light = static_cast<Sensor::Light *>(sensor);

            modifyWindow = new ModifySensorDialogueWindow(light->getId(), "Light", light->getName(), light->getDescription(), light->getBrand(),
                                                          light->getIntensity(), light->getSignalStrength(), light->getColor(), 0);

            connect(modifyWindow, &ModifySensorDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
            connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifySensorDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifySensorDialogueWindow::sensorModified, this, &AboveChartWidget::saveModifySlot);
            connect(modifyWindow, &ModifySensorDialogueWindow::sensorNameModified, this, &AboveChartWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
        // Handle temperature sensor
        else if (dynamic_cast<Sensor::Temperature *>(sensor))
        {
            Sensor::Temperature *temperature = static_cast<Sensor::Temperature *>(sensor);

            modifyWindow = new ModifySensorDialogueWindow(temperature->getId(), "Temperature", temperature->getName(), temperature->getDescription(), temperature->getBrand(),
                                                          temperature->getAccuracy(), temperature->getTemperature(), temperature->getUnit(), 0);

            connect(modifyWindow, &ModifySensorDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
            connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifySensorDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifySensorDialogueWindow::sensorModified, this, &AboveChartWidget::saveModifySlot);
            connect(modifyWindow, &ModifySensorDialogueWindow::sensorNameModified, this, &AboveChartWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
        // Handle wind sensor
        else if (dynamic_cast<Sensor::Wind *>(sensor))
        {
            Sensor::Wind *wind = static_cast<Sensor::Wind *>(sensor);

            modifyWindow = new ModifySensorDialogueWindow(wind->getId(), "Wind", wind->getName(), wind->getDescription(), wind->getBrand(),
                                                          wind->getAccuracy(), wind->getDirection(), wind->getUnit(), wind->getSpeed());

            connect(modifyWindow, &ModifySensorDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
            connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifySensorDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifySensorDialogueWindow::sensorModified, this, &AboveChartWidget::saveModifySlot);
            connect(modifyWindow, &ModifySensorDialogueWindow::sensorNameModified, this, &AboveChartWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
    }

    // Signal when apply changes button is pressed
    void AboveChartWidget::applyChangesSlot()
    {
        emit applyChangesSignal();
    }

    // Signal to check if name is unique
    void AboveChartWidget::youCanCheckIfNameIsUnique(const std::vector<Sensor::AbstractSensor *> &sensors)
    {
        emit finallyYouCanApplyChanges(sensors);
    }

    // Signal to save modifications
    void AboveChartWidget::saveModifySlot(const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, const double &value4)
    {
        emit saveModifySignal(name, description, brand, value1, value2, value3, value4);
    }

    // Update sensor data and widget
    void AboveChartWidget::saveModify(Sensor::AbstractSensor *sensor, const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, const double &value4)
    {
        if (dynamic_cast<Sensor::Humidity *>(sensor))
        {
            Sensor::Humidity *humidity = static_cast<Sensor::Humidity *>(sensor);

            humidity->setName(name);
            humidity->setDescription(description);
            humidity->setBrand(brand);
            humidity->setAccuracy(value1);
            humidity->setHumidity(value2);
        }
        else if (dynamic_cast<Sensor::Light *>(sensor))
        {
            Sensor::Light *light = static_cast<Sensor::Light *>(sensor);

            light->setName(name);
            light->setDescription(description);
            light->setBrand(brand);
            light->setIntensity(value1);
            light->setSignalStrength(value2);
            light->setColor(value3);
        }
        else if (dynamic_cast<Sensor::Temperature *>(sensor))
        {
            Sensor::Temperature *temperature = static_cast<Sensor::Temperature *>(sensor);

            temperature->setName(name);
            temperature->setDescription(description);
            temperature->setBrand(brand);
            temperature->setAccuracy(value1);
            temperature->setTemperature(value2);
            temperature->setUnit(value3);
        }
        else if (dynamic_cast<Sensor::Wind *>(sensor))
        {
            Sensor::Wind *wind = static_cast<Sensor::Wind *>(sensor);

            wind->setName(name);
            wind->setDescription(description);
            wind->setBrand(brand);
            wind->setAccuracy(value1);
            wind->setDirection(value2);
            wind->setUnit(value3);
            wind->setSpeed(value4);
        }

        // Update widget
        setSensorNameLabel(name);
        setDescriptionLabel(description);
        setSensorBrandLabel(brand);
        if (dynamic_cast<Sensor::Humidity *>(sensor))
        {
            setSensorValue1Label("Humidity", value1);
            setSensorValue2Label("Humidity", value2);
        }
        if (dynamic_cast<Sensor::Light *>(sensor))
        {
            setSensorValue1Label("Light", value1);
            setSensorValue2Label("Light", value2);
            setSensorValue3Label("Light", value3);
        }
        if (dynamic_cast<Sensor::Temperature *>(sensor))
        {
            setSensorValue1Label("Temperature", value1);
            setSensorValue2Label("Temperature", value2);
            setSensorValue3Label("Temperature", value3);
        }
        if (dynamic_cast<Sensor::Wind *>(sensor))
        {
            setSensorValue1Label("Wind", value1);
            setSensorValue2Label("Wind", value2);
            setSensorValue3Label("Wind", value3);
            setSensorValue4Label("Wind", value4);
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
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Elimina sensore", "Vuoi eliminare definitivamente questo sensore?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            emit sensorDeleted();
        }
    }

    // Slot for handling simulate button
    void AboveChartWidget::simulateSlot()
    {
        emit simulate();
    }

    // Set sensor name label
    void AboveChartWidget::setSensorNameLabel(const std::string &name)
    {
        sensorNameLabel->setText(QString::fromStdString(name));
    }

    // Set sensor description label
    void AboveChartWidget::setDescriptionLabel(const std::string &description)
    {
        sensorDescriptionLabel->setText("Description: " + QString::fromStdString(description));
    }

    // Set sensor brand label
    void AboveChartWidget::setSensorBrandLabel(const std::string &brand)
    {
        sensorBrandLabel->setText("Brand: " + QString::fromStdString(brand));
    }

    // Set sensor value 1 label
    void AboveChartWidget::setSensorValue1Label(const std::string &type, const double &value)
    {
        if (type == "Humidity" || type == "Temperature" || type == "Wind")
            sensorValue1Label->setText("Accuracy: " + QString::number(value) + " %");
        if (type == "Light")
            sensorValue1Label->setText("Intensity: " + QString::number(value) + " %");
    }

    // Set sensor value 2 label
    void AboveChartWidget::setSensorValue2Label(const std::string &type, const double &value)
    {
        if (type == "Humidity")
            sensorValue2Label->setText("Humidity: " + QString::number(value) + " %");
        if (type == "Light")
            sensorValue2Label->setText("Signal strength: " + QString::number(value) + " %");
        if (type == "Temperature")
            sensorValue2Label->setText("Temperature: " + QString::number(value) + " °");
        if (type == "Wind")
            sensorValue2Label->setText("Direction: " + QString::number(value) + " °");
    }

    // Set sensor value 3 label
    void AboveChartWidget::setSensorValue3Label(const std::string &type, const std::string &value)
    {
        if (type == "Light")
            sensorValue3Label->setText("Color: " + QString::fromStdString(value));
        if (type == "Wind")
            sensorValue3Label->setText("Unit: " + QString::fromStdString(value));
    }

    // Set sensor value 4 label
    void AboveChartWidget::setSensorValue4Label(const std::string &type, const double &value)
    {
        if (type == "Wind")
            sensorValue4Label->setText("Speed: " + QString::number(value));
    }

    // Destructor
    AboveChartWidget::~AboveChartWidget()
    {
        delete greyPanel;

        delete sensorNameLabel;
        delete sensorIDLabel;
        delete sensorDescriptionLabel;
        delete sensorBrandLabel;
        delete sensorValue1Label;
        delete sensorValue2Label;
        delete sensorValue3Label;
        delete sensorValue4Label;

        delete simulateButton;
        delete modifyButton;
        delete deleteButton;

        delete modifyWindow;

        delete layout;
    }

}
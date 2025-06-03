#include "MainWindow.h"

#include <stdexcept>
namespace View
{

    // Constructor for MainWindow
    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), repository(nullptr), isSaved(true), centralWidget(nullptr), mainLayout(nullptr), centralLayout(nullptr), toolbarLayout(nullptr), chartLayout(nullptr),
          statusBar(nullptr), sensorPanel(nullptr), aboveChartWidget(nullptr), chartWidget(nullptr), toolBar(nullptr)
    {
        setWindowTitle("WhiskerWatcher");

        // Create layouts
        mainLayout = new QVBoxLayout;
        centralLayout = new QHBoxLayout;
        chartLayout = new QVBoxLayout;
        toolbarLayout = new QHBoxLayout;

        // Create widgets
        sensorPanel = new SensorPanel(sensors, this);
        sensorPanel->setFixedWidth(500);

        aboveChartWidget = new AboveChartWidget(this);
        aboveChartWidget->setMinimumWidth(714);
        aboveChartWidget->setMinimumHeight(85);
        aboveChartWidget->setObjectName("AboveChartWidget");

        chartWidget = new ChartWidget(this);
        chartWidget->setMinimumWidth(714);
        chartWidget->setMinimumHeight(300);
        chartWidget->setObjectName("ChartWidget");

        toolBar = new ToolBar();
        toolBar->setObjectName("Toolbar");

        // Add toolbar to toolbar layout
        toolbarLayout->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
        toolbarLayout->addWidget(toolBar);

        statusBar = new StatusBar();
        statusBar->setFixedHeight(20);

        // Add widgets to layouts
        chartLayout->addWidget(aboveChartWidget);
        chartLayout->addWidget(chartWidget);
        chartLayout->setAlignment(Qt::AlignTop);

        centralLayout->addWidget(sensorPanel);
        centralLayout->addLayout(chartLayout);

        mainLayout->addLayout(centralLayout);
        mainLayout->addLayout(toolbarLayout);
        mainLayout->addWidget(statusBar);

        // Set main panel
        centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        centralWidget->setLayout(mainLayout);
        this->setMinimumSize(1200, 800);

        // Connect signals
        connect(toolBar, &ToolBar::openSignal, this, &MainWindow::openHandler);
        connect(toolBar, &ToolBar::saveSignal, this, &MainWindow::saveHandler);
        connect(toolBar, &ToolBar::saveAsSignal, this, &MainWindow::saveAsHandler);
        connect(toolBar, &ToolBar::fileOpenedSignal, this, &MainWindow::fileOpenedHandler);
        connect(toolBar, &ToolBar::setIsSavedSignal, this, &MainWindow::setIsSaved);

        connect(sensorPanel, &SensorPanel::areThereAnySensors, this, &MainWindow::checkIfAreThereAnySensors);
        connect(sensorPanel, &SensorPanel::searchSignal, this, &MainWindow::searchHandler);
        connect(sensorPanel, &SensorPanel::searchResults, this, &MainWindow::searchResultsHandler);
        connect(sensorPanel, &SensorPanel::returnBackSignal, this, &MainWindow::returnBackHandler);
        connect(sensorPanel, &SensorPanel::sensorSelected, this, &MainWindow::sensorSelectedHandler);
        connect(sensorPanel, &SensorPanel::sensorAdded, this, &MainWindow::sensorAddedHandler);
        connect(sensorPanel, &SensorPanel::createAndAddSensorSignal, this, &MainWindow::createAndAddSensorHandler);
        connect(this, &MainWindow::youCanCheckIfNameAndIDAreUnique, sensorPanel, &SensorPanel::youCanCheckIfNameAndIDAreUnique);

        connect(aboveChartWidget, &AboveChartWidget::modifySignal, this, &MainWindow::modifyHandler); //TODO: Fix this
        connect(aboveChartWidget, &AboveChartWidget::applyChangesSignal, this, &MainWindow::applyChangesHandler);
        connect(this, &MainWindow::youCanCheckIfNameIsUnique, aboveChartWidget, &AboveChartWidget::youCanCheckIfNameIsUnique);
        connect(aboveChartWidget, &AboveChartWidget::saveModifySignal, this, &MainWindow::saveModifyHandler);
        connect(aboveChartWidget, &AboveChartWidget::setIsSaved, this, &MainWindow::setIsSaved);
        connect(aboveChartWidget, &AboveChartWidget::nameHasBeenModified, this, &MainWindow::nameModifiedHandler);
        connect(aboveChartWidget, &AboveChartWidget::sensorDeleted, this, &MainWindow::sensorDeletedHandler);
        connect(aboveChartWidget, &AboveChartWidget::simulate, this, &MainWindow::simulationHandler);
    }

    // Check if there are any unsaved changes and ask the user if they want to save them
    bool MainWindow::maybeSave()
    {
        // If no sensors and no repository, it doesn't make sense to ask to save
        if (sensors.empty() && repository == nullptr)
            return true;

        // If there are unsaved changes
        if (!isSaved)
        {
            QMessageBox::StandardButton ret = QMessageBox::warning(this, "Application", "Save unsaved changes?",
                                                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

            // If the user cancels, return false
            if (ret == QMessageBox::Cancel)
                return false;

            // If the user decides to save
            if (ret == QMessageBox::Save)
                toolBar->saveJsonFile(sensors, repository);

            // Clear sensors and repository
            sensors.clear();
            delete repository;
            repository = nullptr;

            // Recreate the interface
            sensorPanel->createPanel(sensors);
            aboveChartWidget->createGreyPanel();
            chartWidget->initialChartWidget();

            // Mark as saved and disable save as action
            setIsSaved(true);
            toolBar->disableSaveAsAction();
        }

        return true;
    }

    // Get the currently selected sensor
    Sensor::AbstractSensor *MainWindow::getCurrentlySelectedSensor()
    {
        try
        {
            unsigned int id = aboveChartWidget->getId();

            for (Sensor::AbstractSensor *sensor : sensors)
            {
                if (sensor->getId() == id)
                    return sensor;
            }

            return nullptr;
        }
        catch (const std::exception &e)
        {
            return nullptr;
        }
    }

    // This function is called to replace the sensors in the MainWindow with those read from the repository.
    // If there are already sensors, they are deleted before adding the new ones.
    // This allows the sensors to be updated when a new file is opened.
    void MainWindow::setSensors()
    {
        if (!sensors.empty())
        {
            // Delete all sensors and clear the vector
            for (Sensor::AbstractSensor *sensor : sensors)
            {
                delete sensor;
            }
            sensors.clear();
        }

        // Read the sensors from the repository and add them to the vector
        std::vector<Sensor::AbstractSensor *> new_sensors(repository->readAll());
        for (Sensor::AbstractSensor *sensor : new_sensors)
        {
            sensors.push_back(sensor->clone());
        }
    }

    // This function is called when the user attempts to close the window.
    // If there are unsaved changes, the user is asked if they want to save them.
    // If the user cancels the save operation, the window is not closed.
    void MainWindow::closeEvent(QCloseEvent *event)
    {
        // Maybe save the changes and then accept the event to close the window.
        if (maybeSave())
        {
            event->accept();
        }
        else
        {
            // If the user has clicked on "Cancel", do not close the window.
            event->ignore();
        }
    }

    // This function is called when the user attempts to open a new file.
    // If there are unsaved changes, the user is asked if they want to save them.
    // If the user cancels the save operation, the file is not opened.
    void MainWindow::openHandler()
    {
        // Maybe save the changes and then attempt to open the new file.
        if (maybeSave())
        {
            toolBar->openJsonFile(repository);
        }
    }

    // This function is called when the user attempts to save the current file.
    // The sensors are saved to the repository and the status bar is updated.
    void MainWindow::saveHandler()
    {
        toolBar->saveJsonFile(sensors, repository);
    }

    // This function is called when the user attempts to save the current file with a new name.
    // The sensors are saved to a new file and the status bar is updated.
    void MainWindow::saveAsHandler()
    {
        toolBar->saveAsJsonFile(sensors, repository);
    }

    // Update sensors
    // Create (or recreate) the SensorPanel
    // Select the first sensor
    // Update the StatusBar
    // Activate "Save with name" button
    void MainWindow::fileOpenedHandler()
    {
        setSensors();
        sensorPanel->createPanel(sensors);
        sensorSelectedHandler(sensors[0]->getId());
        statusBar->updateBecauseSensorPanelIsNotEmpty();
        toolBar->enableSaveAsAction();
    }

    // Update the "Save" button state
    void MainWindow::setIsSaved(const bool &value)
    {
        isSaved = value;
        if (isSaved)
            toolBar->disableSaveAction();
        else
            toolBar->enableSaveAction();
    }

    // Check if there are any sensors
    void MainWindow::checkIfAreThereAnySensors()
    {
        sensorPanel->afterTextChanged(!sensors.empty());
    }

    // Update the search results
    void MainWindow::searchHandler()
    {
        sensorPanel->updateSearchResults(sensors);
    }

    // Update the UI after a search
    void MainWindow::searchResultsHandler(const std::vector<SensorWidget *> &sensorWidgets)
    {
        if (sensorWidgets.empty())
        {
            aboveChartWidget->createGreyPanel();
            chartWidget->initialChartWidget();
            statusBar->updateAfterResearch(0);
        }
        else
        {
            sensorPanel->handleSensorWidgetSelected(sensorWidgets[0]);
            statusBar->updateAfterResearch(sensorWidgets.size());
        }
    }

    // Return back to the main UI
    void MainWindow::returnBackHandler()
    {
        sensorPanel->createPanel(sensors);
        if (!sensors.empty())
            sensorSelectedHandler(sensors[0]->getId());
    }

    // If no sensor is selected, show the selected one
    // If a different sensor is selected, change the right panels
    // If the same sensor is selected, only update the color
    void MainWindow::sensorSelectedHandler(const unsigned int &id) 
    {
        Sensor::AbstractSensor *currentSensor = getCurrentlySelectedSensor();

        if (currentSensor == nullptr) 
        {
            for (Sensor::AbstractSensor *sensor : sensors)
            {
                if (sensor->getId() == id)
                {
                    sensorPanel->setColors(nullptr, sensor);
                    aboveChartWidget->createAboveChartForSensor(sensor);
                    chartWidget->chartWidgetOnSelection(sensor);
                    statusBar->updateAfterSensorSelected();
                    return;
                }
            }
        }
        else if (id != currentSensor->getId())
        {
            for (Sensor::AbstractSensor *sensor : sensors)
            {
                if (sensor->getId() == id)
                {
                    sensorPanel->setColors(currentSensor, sensor);
                    aboveChartWidget->createAboveChartForSensor(sensor);
                    chartWidget->chartWidgetOnSelection(sensor);
                    statusBar->updateAfterSensorSelected();
                    return;
                }
            }
        }
        else
        {
            for (Sensor::AbstractSensor *sensor : sensors)
            {
                if (sensor->getId() == id)
                {
                    sensorPanel->setColors(currentSensor, sensor);
                    statusBar->updateAfterSensorSelected();
                    return;
                }
            }
        }
    }

    // Add the new sensor to the sensors queue
    // Refresh the SensorPanel. If it was showing search results, they disappear and it switches back to the panel that shows all sensors
    // Select the newly created sensor
    // Activate the "Save" button
    // If this is the first sensor added, activate the "Save as" button
    void MainWindow::sensorAddedHandler(Sensor::AbstractSensor *sensor)
    {
        sensors.push_back(sensor);
        sensorPanel->createPanel(sensors);
        sensorSelectedHandler(sensor->getId());
        setIsSaved(false);
        if (sensors.size() == 1)
            toolBar->enableSaveAsAction();
    }

    // Emits a signal to check if the name and ID are unique
    void MainWindow::createAndAddSensorHandler()
    {
        emit youCanCheckIfNameAndIDAreUnique(sensors);
    }

    // Activates the "Modify" button
    void MainWindow::modifyHandler()
    {
        aboveChartWidget->modify(getCurrentlySelectedSensor());
    }

    // Emits a signal to check if the name is unique
    void MainWindow::applyChangesHandler()
    {
        emit youCanCheckIfNameIsUnique(sensors);
    }

    // Saves the modified values of the currently selected sensor
    void MainWindow::saveModifyHandler(const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, const double &value4)
    {
        aboveChartWidget->saveModify(getCurrentlySelectedSensor(), name, description, brand, value1, value2, value3, value4);
    }

    // Modifies the name of the currently selected sensor in the SensorPanel
    void MainWindow::nameModifiedHandler(const std::string &previousName, const std::string &newName)
    {
        sensorPanel->modifyOneName(previousName, newName);
    }

    // Handle the deletion of the currently selected sensor
    void MainWindow::sensorDeletedHandler()
    {
        // Delete the currently selected sensor
        Sensor::AbstractSensor *sensor = getCurrentlySelectedSensor();
        auto it = sensors.begin();
        for (; it != sensors.end(); ++it)
        {
            if (sensor->getId() == (*it)->getId())
            {
                delete *it;
                it = sensors.erase(it);
                break;
            }
        }

        // Refresh the SensorPanel
        sensorPanel->createPanel(sensors); // The check if "sensors" is empty is already executed inside the "createPanel" function

        if (!sensors.empty())
        {
            // If the deleted sensor was not the last one, select the next one, otherwise select the previous one
            if (it != sensors.end())
                sensorSelectedHandler((*it)->getId());
            else
            {
                it--;
                sensorSelectedHandler((*it)->getId());
            }
        }
        else
        { // If "sensors" is empty, recreate the initial screen
            aboveChartWidget->createGreyPanel();
            chartWidget->initialChartWidget();
            statusBar->updateBecauseSensorPanelIsEmpty();

            // Since the user has deleted all the sensors, the "Save with name" button is disabled

            // If no repository has been created, the "Save" button is also disabled
            if (repository == nullptr)
            {
                toolBar->disableSaveAction();
                return; // Finish here, otherwise the last line of this method would undo the previous disactivation
            }
        }

        // Enable the "Save" button
        setIsSaved(false);
    }

    // Handle the simulation of the currently selected sensor
    void MainWindow::simulationHandler()
    {
        // Use dynamic_cast to check the type of the sensor and call the appropriate chart insertion method
        if (dynamic_cast<Sensor::Humidity *>(getCurrentlySelectedSensor()))
        {
            chartWidget->insertHumidityChart(static_cast<Sensor::Humidity *>(getCurrentlySelectedSensor()));
            statusBar->updateAfterSimulation();
        }
        else if (dynamic_cast<Sensor::Light *>(getCurrentlySelectedSensor()))
        {
            chartWidget->insertLightChart(static_cast<Sensor::Light *>(getCurrentlySelectedSensor()));
            statusBar->updateAfterSimulation();
        }
        else if (dynamic_cast<Sensor::Temperature *>(getCurrentlySelectedSensor()))
        {
            chartWidget->insertTemperatureChart(static_cast<Sensor::Temperature *>(getCurrentlySelectedSensor()));
            statusBar->updateAfterSimulation();
        }
        else if (dynamic_cast<Sensor::Wind *>(getCurrentlySelectedSensor()))
        {
            chartWidget->insertWindChart(static_cast<Sensor::Wind *>(getCurrentlySelectedSensor()));
            statusBar->updateAfterSimulation();
        }
    }

    // Destructor that cleans up dynamically allocated objects
    MainWindow::~MainWindow()
    {
        // Delete each sensor object and clear the vector
        for (Sensor::AbstractSensor *sensor : sensors)
        {
            delete sensor;
        }
        sensors.clear();

        // Delete the widgets and layouts
        delete toolBar;
        delete sensorPanel;
        delete aboveChartWidget;
        delete chartWidget;
        delete statusBar;

        delete chartLayout;
        delete centralLayout;
        delete mainLayout;
        delete centralWidget;
    }

}
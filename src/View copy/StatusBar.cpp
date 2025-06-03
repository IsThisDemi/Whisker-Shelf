#include "StatusBar.h"

namespace View
{
    // StatusBar constructor
    StatusBar::StatusBar(QStatusBar *parent) : QStatusBar(parent)
    {
        updateBecauseSensorPanelIsEmpty();
    }

    // Get status message
    QString StatusBar::getStatusMessage() const { return statusMessage; }

    // Set status message
    void StatusBar::setStatusMessage(const std::string &newStatusMessage)
    {
        statusMessage = QString::fromStdString(newStatusMessage);
    }

    // Update status bar
    void StatusBar::updateStatus() { showMessage(statusMessage); }

    // Update status bar when sensor panel is empty
    void StatusBar::updateBecauseSensorPanelIsEmpty()
    {
        statusMessage = "Load or add a sensor.";
        updateStatus();
    }

    // Update status bar when sensor panel is not empty
    void StatusBar::updateBecauseSensorPanelIsNotEmpty()
    {
        statusMessage = "Ready to test.";
        updateStatus();
    }

    // Update status bar after sensor is selected
    void StatusBar::updateAfterSensorSelected()
    {
        statusMessage = "You can start a simulation.";
        updateStatus();
    }

    // Update status bar after research is performed
    void StatusBar::updateAfterResearch(const unsigned int &resultsNumber)
    {
        if (resultsNumber > 1)
            statusMessage = "The search has produced " + QString::number(resultsNumber) + " results";
        else if (resultsNumber == 1)
            statusMessage = "The search has produced 1 result";
        else
            statusMessage = "No sensor found";

        updateStatus();
    }

    // Update status bar after simulation is performed
    void StatusBar::updateAfterSimulation()
    {
        statusMessage = "Interesting results!";
        updateStatus();
    }
}


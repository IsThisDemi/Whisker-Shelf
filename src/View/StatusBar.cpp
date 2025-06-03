#include "StatusBar.h"

namespace View
{
    // StatusBar constructor
    StatusBar::StatusBar(QStatusBar *parent) : QStatusBar(parent)
    {
        updateBecauseMediaPanelIsEmpty();
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

    // Update status bar when media panel is empty
    void StatusBar::updateBecauseMediaPanelIsEmpty()
    {
        statusMessage = "Load or add a media.";
        updateStatus();
    }

    // Update status bar when media panel is not empty
    void StatusBar::updateBecauseMediaPanelIsNotEmpty()
    {
        statusMessage = "Ready to explore.";
        updateStatus();
    }

    // Update status bar after media is selected
    void StatusBar::updateAfterMediaSelected()
    {
        statusMessage = "You can start exploring.";
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
            statusMessage = "No media found";

        updateStatus();
    }

    // Update status bar after simulation is performed
    void StatusBar::updateAfterSimulation()
    {
        statusMessage = "Interesting results!";
        updateStatus();
    }
}


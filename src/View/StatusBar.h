#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>

namespace View
{

    class StatusBar : public QStatusBar
    {
        Q_OBJECT

    private:
        QString statusMessage;

    public:
        StatusBar(QStatusBar *parent = nullptr);

        QString getStatusMessage() const;
        void setStatusMessage(const std::string &newStatusMessage);

        void updateStatus();

        void updateBecauseMediaPanelIsEmpty();
        void updateBecauseMediaPanelIsNotEmpty();
        void updateAfterMediaSelected();
        void updateAfterResearch(const unsigned int &resultsNumber);
        void updateAfterSimulation();

        ~StatusBar() = default;
    };

}

#endif

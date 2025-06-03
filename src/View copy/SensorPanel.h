#ifndef VIEW_SENSORPANEL_H
#define VIEW_SENSORPANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QScrollArea>
#include <QLabel>
#include <algorithm>
#include <QMultiMap>

#include "../Sensor/Humidity.h"
#include "../Sensor/Light.h"
#include "../Sensor/Temperature.h"
#include "../Sensor/Wind.h"
#include "AddSensorDialogueWindow.h"
#include "SensorWidget.h"

namespace View
{

    class SensorPanel : public QWidget
    {
        Q_OBJECT

    private:
        QVBoxLayout *mainLayout;

        QHBoxLayout *searchLayout;
        QLineEdit *searchBar;
        QPushButton *returnBackButton;

        QGridLayout *sensorLayout;
        QScrollArea *scrollArea;
        std::vector<SensorWidget *> sensorWidgets;
        QWidget *sensorWidgetContainer;

        QPushButton *addSensorButton;

        AddSensorDialogueWindow *addWindow;

        SensorWidget *sensorWidget; // Temporary pointer, creates objects to be inserted into the sensorWidgets vector, and then it automatically disassociates the memory on the Heap from it via shallow copy,
                                    // So that memory on the Heap is cleaned up at the time of cleanup of the vector itself.
    protected:
        void mousePressEvent(QMouseEvent *event) override;

    signals:
        void areThereAnySensors();
        void searchSignal();
        void oneCharacterSearch();
        void searchResults(const std::vector<SensorWidget *> &sensorWidgets);
        void returnBackSignal();
        void sensorSelected(const unsigned int &id);
        void createAndAddSensorSignal();
        void finallyYouCanCreateAndAddSensor(const std::vector<Sensor::AbstractSensor *> &sensors);
        void sensorAdded(Sensor::AbstractSensor *sensor);

    public slots:
        void afterTextChangedSlot();
        void search();
        void returnBackFromSearch();
        void addSensorSlot();
        void createAndAddSensorSlot();
        void youCanCheckIfNameAndIDAreUnique(const std::vector<Sensor::AbstractSensor *> &sensors);
        void handleSensorWidgetSelected(SensorWidget *sender);
        void handleSensorAdded(Sensor::AbstractSensor *sensor);

    public:
        explicit SensorPanel(const std::vector<Sensor::AbstractSensor *> &sensors, QWidget *parent);
        void createPanel(const std::vector<Sensor::AbstractSensor *> &sensors);
        void updateSearchResults(const std::vector<Sensor::AbstractSensor *> &sensors);
        int findLengthOfLongestCommonSubstring(const QString &str1, const QString &str2);
        std::vector<Sensor::AbstractSensor *> getSensorsForKey(const QMultiMap<int, Sensor::AbstractSensor *> &sensorMap, int key);

        void setIconOfSensorWidget(const QIcon &icon);

        void afterTextChanged(const bool &thereAreSensors);
        void modifyOneName(const std::string &previousName, const std::string &newName);
        void setColors(Sensor::AbstractSensor *previousCurrentSensor, Sensor::AbstractSensor *newCurrentSensor);

        ~SensorPanel();
    };

}

#endif

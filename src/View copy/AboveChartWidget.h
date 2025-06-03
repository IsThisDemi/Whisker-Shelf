#ifndef ABOVE_CHART_WIDGET_H
#define ABOVE_CHART_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

#include "../Sensor/Humidity.h"
#include "../Sensor/Light.h"
#include "../Sensor/Temperature.h"
#include "../Sensor/Wind.h"
#include "ModifySensorDialogueWindow.h"

namespace View
{

    class AboveChartWidget : public QWidget
    {
        Q_OBJECT

    private:
        QFrame *greyPanel;

        QGridLayout *layout;

        // Common labels
        QLabel *sensorNameLabel;
        QLabel *sensorIDLabel;
        QLabel *sensorDescriptionLabel;
        QLabel *sensorBrandLabel;

        // Label for specific sensor values
        QLabel *sensorValue1Label;
        QLabel *sensorValue2Label;
        QLabel *sensorValue3Label;
        QLabel *sensorValue4Label;

        QPushButton *simulateButton;
        QPushButton *modifyButton;
        QPushButton *deleteButton;

        ModifySensorDialogueWindow *modifyWindow;

    signals:
        void setIsSaved(const bool &value);
        void modifySignal();
        void applyChangesSignal();
        void finallyYouCanApplyChanges(const std::vector<Sensor::AbstractSensor *> &sensors);
        void saveModifySignal(const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, const double &value4);
        void nameHasBeenModified(const std::string &previousName, const std::string &newName);
        void sensorDeleted();
        void simulate();

    public slots:
        void modifySlot();
        void applyChangesSlot();
        void youCanCheckIfNameIsUnique(const std::vector<Sensor::AbstractSensor *> &sensors);
        void saveModifySlot(const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, const double &value4);
        void nameModifiedSlot(const std::string &previousName, const std::string &newName);
        void deleteSlot();
        void simulateSlot();

    public:
        AboveChartWidget(QWidget *parent = nullptr);
        void createGreyPanel();
        void createAboveChartForSensor(Sensor::AbstractSensor *sensor);

        void createTheRestOfLabelsHumidity(const double &accuracy, const double &humidity);
        void createTheRestOfLabelsLight(const std::string &color, const double &intensity, const double &signalStrength);
        void createTheRestOfLabelsTemperature(const double &accuracy, const double &temperature, const std::string &unit);
        void createTheRestOfLabelsWind(const double &accuracy, const double &direction, const double &speed, const std::string &unit);

        unsigned int getId() const;
        void modify(Sensor::AbstractSensor *sensor);
        void saveModify(Sensor::AbstractSensor *sensor, const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, const double &value4);

        void setSensorNameLabel(const std::string &name);
        void setDescriptionLabel(const std::string &description);
        void setSensorBrandLabel(const std::string &brand);
        void setSensorValue1Label(const std::string &type, const double &value);
        void setSensorValue2Label(const std::string &type, const double &value);
        void setSensorValue3Label(const std::string &type, const std::string &value);
        void setSensorValue4Label(const std::string &type, const double &value);

        ~AboveChartWidget();
    };

}

#endif

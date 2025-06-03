#include "SetTypeAndIconOfSensorWidgetVisitor.h"

namespace View
{

    SetTypeAndIconOfSensorWidgetVisitor::SetTypeAndIconOfSensorWidgetVisitor(SensorPanel *sensorPanel)
        : sensorPanel(sensorPanel) {}

    // Set the icon of the sensor widget according to the type of the sensor
    void SetTypeAndIconOfSensorWidgetVisitor::visit(const Sensor::Humidity &)
    {
        sensorPanel->setIconOfSensorWidget(QIcon(":/Assets/Icons/Sensors/humidity.png"));
    }

    void SetTypeAndIconOfSensorWidgetVisitor::visit(const Sensor::Light &)
    {
        sensorPanel->setIconOfSensorWidget(QIcon(":/Assets/Icons/Sensors/light.png"));
    }

    void SetTypeAndIconOfSensorWidgetVisitor::visit(const Sensor::Temperature &)
    {
        sensorPanel->setIconOfSensorWidget(QIcon(":/Assets/Icons/Sensors/temperature.png"));
    }

    void SetTypeAndIconOfSensorWidgetVisitor::visit(const Sensor::Wind &)
    {
        sensorPanel->setIconOfSensorWidget(QIcon(":/Assets/Icons/Sensors/wind.png"));
    }

}

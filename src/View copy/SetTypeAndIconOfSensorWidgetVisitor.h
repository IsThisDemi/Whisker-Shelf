#ifndef SET_TYPE_AND_ICON_OF_SENSOR_WIDGET_VISITOR_H
#define SET_TYPE_AND_ICON_OF_SENSOR_WIDGET_VISITOR_H

#include "SensorPanel.h"
#include "../Sensor/Humidity.h"

namespace View
{

    class SetTypeAndIconOfSensorWidgetVisitor : public Sensor::IConstVisitor
    {
    private:
        SensorPanel *sensorPanel;

    public:
        SetTypeAndIconOfSensorWidgetVisitor(SensorPanel *sensorPanel);

        void visit(const Sensor::Humidity &humidity) override;
        void visit(const Sensor::Light &light) override;
        void visit(const Sensor::Temperature &temperature) override;
        void visit(const Sensor::Wind &wind) override;
    };

}

#endif
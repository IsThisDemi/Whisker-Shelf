#ifndef SENSOR_OBSERVER_H
#define SENSOR_OBSERVER_H

namespace Sensor {

class AbstractSensor;

class SensorObserver{
public:
    virtual void notify(const AbstractSensor& sensor) = 0;

    virtual ~SensorObserver() = default;
};

}

#endif
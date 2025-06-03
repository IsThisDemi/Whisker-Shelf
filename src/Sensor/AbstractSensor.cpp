#include "AbstractSensor.h"

namespace Sensor {
    // Constructor
    // Initialize fields with parameters
    AbstractSensor::AbstractSensor(
        const unsigned int id, 
        const std::string name, 
        const std::string description, 
        const std::string brand
    ) : id(id), name(name), description(description), brand(brand) {}

    // Destructor
    // Default destructor
    AbstractSensor::~AbstractSensor() {}

    // Get the id of the sensor
    unsigned int AbstractSensor::getId() const {
        return id;
    }

    // Get the name of the sensor
    const std::string AbstractSensor::getName() const {
        return name;
    }

    // Set the name of the sensor
    // Return a reference to the sensor
    AbstractSensor& AbstractSensor::setName(const std::string name) {
        this->name = name;
        return *this;
    }

    // Get the description of the sensor
    const std::string AbstractSensor::getDescription() const {
        return description;
    }

    // Set the description of the sensor
    // Return a reference to the sensor
    AbstractSensor& AbstractSensor::setDescription(const std::string description) {
        this->description = description;
        return *this;
    }

    // Get the brand of the sensor
    const std::string AbstractSensor::getBrand() const {
        return brand;
    }

    // Set the brand of the sensor
    // Return a reference to the sensor
    AbstractSensor& AbstractSensor::setBrand(const std::string brand) {
        this->brand = brand;
        return *this;
    }
    
    // Get the observer of the sensor
    SensorObserver* AbstractSensor::getObserver() const {
        return observer;
    }

    // Set the observer of the sensor
    void AbstractSensor::setObserver(SensorObserver* newObserver) {
        observer = newObserver;
    }
}
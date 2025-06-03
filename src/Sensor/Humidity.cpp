#include "Humidity.h"
#include <random>
#include <iostream>
#include <typeinfo>
#include <stdexcept>

namespace Sensor {
    // Constructor
    // Initialize Humidity object with provided parameters
    Humidity::Humidity(
        const unsigned int id, // ID of the sensor
        const std::string name, // Name of the sensor
        const std::string description, // Description of the sensor
        const std::string brand, // Brand of the sensor
        const double humidity, // Current humidity value
        const double accuracy, // Accuracy of the sensor
        const std::vector<double> data // Historical data
    ) 
        : AbstractSensor(id, name, description, brand),
          humidity(humidity),
          accuracy(accuracy),
          data(data)
    {}

    // Get current humidity
    double Humidity::getHumidity() const {
        return humidity;
    }

    // Set current humidity
    Humidity& Humidity::setHumidity(const double humidity) {
        this->humidity = humidity;
        return *this;
    }

    // Get accuracy of the sensor
    double Humidity::getAccuracy() const {
        return accuracy;
    }

    // Set accuracy of the sensor
    Humidity& Humidity::setAccuracy(const double accuracy) {
        this->accuracy = accuracy;
        return *this;
    }

    // Get historical data
    std::vector<double> Humidity::getData() const {
        return data;
    }

    // Generate random data
    void Humidity::setRandomData() {
        // Initialize random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 100.0);

        // Generate random data
        for (auto &value : data)
        {
            value = dis(gen);
        }

        // Notify observer
        getObserver()->notify(*this);
    }

    // Create a copy of the object
    Humidity* Humidity::clone() const {
        return new Humidity(*this);
    }

    // Accept visitor
    void Humidity::accept(IConstVisitor& visitor) const {
        visitor.visit(*this);
    }

    // Accept visitor
    void Humidity::accept(IVisitor& visitor) {
        visitor.visit(*this);
    }
}
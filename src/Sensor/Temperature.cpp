#include "Temperature.h"

namespace Sensor{
    // Constructor
    // Initialize temperature, unit, accuracy and data
    Temperature::Temperature(
        const unsigned int id,
        const std::string name,
        const std::string description,
        const std::string brand,
        const double temperature,
        const std::string unit,
        const double accuracy,
        const std::vector<double> data
        ) : AbstractSensor(id, name, description, brand),
            temperature(temperature),
            unit(unit),
            accuracy(accuracy),
            data(data) {}

    // Getter for temperature
    // Returns the temperature
    double Temperature::getTemperature() const {
        return temperature;
    }

    // Setter for temperature
    // Updates the temperature and returns reference to object
    Temperature& Temperature::setTemperature(const double temperature) {
        this->temperature = temperature;
        return *this;
    }

    // Getter for unit
    // Returns the unit
    std::string Temperature::getUnit() const {
        return unit;
    }

    // Setter for unit
    // Updates the unit and returns reference to object
    Temperature& Temperature::setUnit(const std::string unit) {
        this->unit = unit;
        return *this;
    }

    // Getter for accuracy
    // Returns the accuracy
    double Temperature::getAccuracy() const {
        return accuracy;
    }

    // Setter for accuracy
    // Updates the accuracy and returns reference to object
    Temperature& Temperature::setAccuracy(const double accuracy) {
        this->accuracy = accuracy;
        return *this;
    }

    // Getter for data
    // Returns the data
    std::vector<double> Temperature::getData() const {
        return data;
    }

    // Setter for data
    // Updates the data with random values between 0 and 100
    void Temperature::setRandomData()
    {
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

    // Creates a clone of the object
    Temperature* Temperature::clone() const {
        return new Temperature(*this);
    }

    // Accepts a constant visitor
    void Temperature::accept(IConstVisitor& visitor) const {
        visitor.visit(*this);
    }

    // Accepts a visitor
    void Temperature::accept(IVisitor& visitor) {
        visitor.visit(*this);
    }
}
#include "Wind.h"

namespace Sensor {
    // Constructor
    // Initialize Wind sensor with given parameters
    Wind::Wind(
        const unsigned int id,
        const std::string name,
        const std::string description,
        const std::string brand,
        const double speed,
        const std::string unit,
        const double direction,
        const double accuracy,
        const std::vector<double> data
        ) : AbstractSensor(id, name, description, brand), speed(speed), unit(unit), direction(direction), accuracy(accuracy), data(data) {}

    // Get speed
    // Return wind speed of the sensor
    double Wind::getSpeed() const {
        return speed;
    }

    // Set speed
    // Set wind speed of the sensor
    Wind& Wind::setSpeed(const double speed) {
        this->speed = speed;
        return *this;
    }

    // Get unit
    // Return unit of the wind sensor
    std::string Wind::getUnit() const {
        return unit;
    }

    // Set unit
    // Set unit of the wind sensor
    Wind& Wind::setUnit(const std::string unit) {
        this->unit = unit;
        return *this;
    }

    // Get direction
    // Return wind direction of the sensor
    double Wind::getDirection() const {
        return direction;
    }

    // Set direction
    // Set wind direction of the sensor
    Wind& Wind::setDirection(const double direction) {
        this->direction = direction;
        return *this;
    }

    // Get accuracy
    // Return wind accuracy of the sensor
    double Wind::getAccuracy() const {
        return accuracy;
    }

    // Set accuracy
    // Set wind accuracy of the sensor
    Wind& Wind::setAccuracy(const double accuracy) {
        this->accuracy = accuracy;
        return *this;
    }

    // Get data
    // Return wind data of the sensor
    std::vector<double> Wind::getData() const
    {
        return data;
    }

    // Set random data
    // Generate random wind data for the sensor
    void Wind::setRandomData()
    {
        // Initialize random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 360.0);

        // Generate random data
        for (auto &value : data)
        {
            value = dis(gen);
        }

        getObserver()->notify(*this);
    }

    // Clone
    // Create a copy of the wind sensor
    Wind* Wind::clone() const {
        return new Wind(*this);
    }

    // Accept
    // Accept visitor for const wind sensor
    void Wind::accept(IConstVisitor& visitor) const {
        visitor.visit(*this);
    }

    // Accept
    // Accept visitor for wind sensor
    void Wind::accept(IVisitor& visitor) {
        visitor.visit(*this);
    }
}

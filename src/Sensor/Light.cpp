#include "Light.h"

namespace Sensor {
    // Constructor
    // Sets all the attributes of the light
    Light::Light(
        const unsigned int id,
        const std::string name,
        const std::string description,
        const std::string brand,
        const double intensity,
        const std::string color,
        const double signalStrength,
        const std::vector<double> data
        ) : AbstractSensor(id, name, description, brand),
            intensity(intensity),
            color(color),
            signalStrength(signalStrength),
            data(data) {}

    // Getter for intensity
    double Light::getIntensity() const {
        return intensity;
    }

    // Setter for intensity
    Light& Light::setIntensity(const double intensity) {
        this->intensity = intensity;
        return *this;
    }

    // Getter for color
    std::string Light::getColor() const {
        return color;
    }

    // Setter for color
    Light& Light::setColor(const std::string color) {
        this->color = color;
        return *this;
    }

    // Getter for signal strength
    double Light::getSignalStrength() const {
        return signalStrength;
    }

    // Setter for signal strength
    Light& Light::setSignalStrength(const double signalStrength) {
        this->signalStrength = signalStrength;
        return *this;
    }

    // Getter for data
    std::vector<double> Light::getData() const
    {
        return data;
    }

    // Setter for data, generates random data
    void Light::setRandomData()
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

        getObserver()->notify(*this);
    }

    // Clones the light
    Light* Light::clone() const {
        return new Light(*this);
    }

    // Accept function for IConstVisitor
    void Light::accept(IConstVisitor& visitor) const {
        visitor.visit(*this);
    }

    // Accept function for IVisitor
    void Light::accept(IVisitor& visitor) {
        visitor.visit(*this);
    }
}
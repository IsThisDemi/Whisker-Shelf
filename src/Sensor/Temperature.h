#ifndef SENSOR_TEMPERATURE_H
#define SENSOR_TEMPERATURE_H

#include "AbstractSensor.h"

namespace Sensor {
    class Temperature : public AbstractSensor {
        private:
            double temperature;
            std::string unit; 
            double accuracy;
            std::vector<double> data;

        public:
            Temperature(
                const unsigned int id,
                const std::string name,
                const std::string description,
                const std::string brand,
                const double temperature,
                const std::string unit,
                const double accuracy,
                const std::vector<double> data = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
            );

            double getTemperature() const;
            Temperature& setTemperature(const double temperature);

            std::string getUnit() const;
            Temperature& setUnit(const std::string unit);

            double getAccuracy() const;
            Temperature& setAccuracy(const double accuracy);

            std::vector<double> getData() const;
            void setRandomData();

            Temperature* clone() const;

            virtual void accept(IConstVisitor& visitor) const;
            virtual void accept(IVisitor& visitor);
    };
}

#endif
#ifndef SENSOR_WIND_H
#define SENSOR_WIND_H

#include "AbstractSensor.h"

namespace Sensor {
    class Wind : public AbstractSensor {
        private:
            double speed;
            std::string unit;
            double direction;
            double accuracy;
            std::vector<double> data;

        public:
            Wind(
                const unsigned int id,
                const std::string name,
                const std::string description,
                const std::string brand,
                const double speed,
                const std::string unit,
                const double direction,
                const double accuracy,
                const std::vector<double> data = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
            );

            double getSpeed() const;
            Wind& setSpeed(const double speed);

            std::string getUnit() const;
            Wind& setUnit(const std::string unit);

            double getDirection() const;
            Wind& setDirection(const double direction);

            double getAccuracy() const;
            Wind& setAccuracy(const double accuracy);

            std::vector<double> getData() const;
            void setRandomData();

            Wind* clone() const;

            virtual void accept(IConstVisitor& visitor) const;
            virtual void accept(IVisitor& visitor);
    };
}

#endif
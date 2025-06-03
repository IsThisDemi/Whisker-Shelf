#ifndef SENSOR_HUMIDITY_H
#define SENSOR_HUMIDITY_H

#include "AbstractSensor.h"

namespace Sensor {
    class Humidity : public AbstractSensor {
        private:
            double humidity;
            double accuracy;
            std::vector<double> data;

        public:
            Humidity(
                const unsigned int id,
                const std::string name,
                const std::string description,
                const std::string brand,
                const double humidity,
                const double accuracy,
                const std::vector<double> data = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
                );

            double getHumidity() const;
            Humidity& setHumidity(const double humidity);

            double getAccuracy() const;
            Humidity& setAccuracy(const double accuracy);

            std::vector<double> getData() const;
            void setRandomData();

            Humidity* clone() const;

            virtual void accept(IConstVisitor& visitor) const;
            virtual void accept(IVisitor& visitor);
    };
}

#endif
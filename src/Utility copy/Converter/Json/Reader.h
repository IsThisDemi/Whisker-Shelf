#ifndef UTILITY_CONVERTER_JSON_READER_H
#define UTILITY_CONVERTER_JSON_READER_H

#include <map>
#include <QJsonObject>

#include "IReader.h"
#include "Json.h"

namespace Utility {
    namespace Converter {
        namespace Json {
            class Reader : public IReader {
                private:
                    std::map<unsigned int, Sensor::AbstractSensor*> cache;

                    Sensor::AbstractSensor *readHumidity(const QJsonObject &object) const;
                    Sensor::AbstractSensor *readLight(const QJsonObject &object) const;
                    Sensor::AbstractSensor *readTemperature(const QJsonObject &object) const;
                    Sensor::AbstractSensor *readWind(const QJsonObject &object) const;
                public:
                    const std::map<unsigned int, Sensor::AbstractSensor*> &getCache() const;
                    Reader& clear();
                    Sensor::AbstractSensor* read(const QJsonObject& object); 
            };
        }
    }
}

#endif
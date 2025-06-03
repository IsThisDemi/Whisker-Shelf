#include "Reader.h"

// Utility includes
#include <stdexcept>
#include <QJsonArray>
#include <iostream>

// Sensor includes
#include "Sensor/Humidity.h"
#include "Sensor/Light.h"
#include "Sensor/Temperature.h"
#include "Sensor/Wind.h"

namespace Utility {
    namespace Converter {
        namespace Json {
            const std::map<unsigned int, Sensor::AbstractSensor*>& Reader::getCache() const {
                // Returns the cache of sensors
                return cache;
            }

            Reader& Reader::clear() {
                // Clears the cache of sensors
                cache.clear();
                return *this;
            }

            Sensor::AbstractSensor* Reader::read(const QJsonObject& object) {
                // Reads a sensor from a JSON object
                QJsonValue type = object.value("type");
                if (type.isUndefined()) {
                    throw std::invalid_argument("Missing sensor type.");
                }

                const unsigned int identifier = object.value("id").toInt();
                if (cache.count(identifier) > 0) {
                    return cache[identifier];
                }

                if (type.toString() == "Humidity") {
                    return readHumidity(object);
                } else if (type.toString() == "Light") {
                    return readLight(object);
                } else if (type.toString() == "Temperature") {
                    return readTemperature(object);
                } else if (type.toString() == "Wind") {
                    return readWind(object);
                } else {
                    throw std::invalid_argument("Unknown sensor type.");
                }
            }

            Sensor::AbstractSensor* Reader::readHumidity(const QJsonObject& object) const {
                // Reads a Humidity sensor from a JSON object
                return new Sensor::Humidity(
                    object.value("id").toInt(),
                    object.value("name").toString().toStdString(),
                    object.value("description").toString().toStdString(),
                    object.value("brand").toString().toStdString(),
                    object.value("humidity").toDouble(),
                    object.value("accuracy").toDouble()
                );
            }

            Sensor::AbstractSensor* Reader::readLight(const QJsonObject& object) const {
                // Reads a Light sensor from a JSON object
                return new Sensor::Light(
                    object.value("id").toInt(),
                    object.value("name").toString().toStdString(),
                    object.value("description").toString().toStdString(),
                    object.value("brand").toString().toStdString(),
                    object.value("intensity").toDouble(),
                    object.value("color").toString().toStdString(),
                    object.value("signalStrength").toDouble()
                );
            }

            Sensor::AbstractSensor* Reader::readTemperature(const QJsonObject& object) const {
                // Reads a Temperature sensor from a JSON object
                return new Sensor::Temperature(
                    object.value("id").toInt(),
                    object.value("name").toString().toStdString(),
                    object.value("description").toString().toStdString(),
                    object.value("brand").toString().toStdString(),
                    object.value("temperature").toDouble(),
                    object.value("unit").toString().toStdString(),
                    object.value("accuracy").toDouble()
                );
            }

            Sensor::AbstractSensor* Reader::readWind(const QJsonObject& object) const {
                // Reads a Wind sensor from a JSON object
                return new Sensor::Wind(
                    object.value("id").toInt(),
                    object.value("name").toString().toStdString(),
                    object.value("description").toString().toStdString(),
                    object.value("brand").toString().toStdString(),
                    object.value("speed").toDouble(),
                    object.value("unit").toString().toStdString(),
                    object.value("direction").toDouble(),
                    object.value("accuracy").toDouble()
                );
            }
        }
    }
}

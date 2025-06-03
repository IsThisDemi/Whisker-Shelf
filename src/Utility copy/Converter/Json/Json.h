#ifndef UTILITY_CONVERTER_JSON_JSON_H
#define UTILITY_CONVERTER_JSON_JSON_H

#include "Reader.h"
#include "../../../Sensor/AbstractSensor.h"
#include "JsonVisitor.h"

namespace Utility {
    namespace Converter {
        namespace Json {
            class Json {
                public:
                    static QJsonObject fromObject(const Sensor::AbstractSensor& sensor);
                    static Sensor::AbstractSensor& toObject(const QJsonObject& json);
            };
        }
    }
}

#endif
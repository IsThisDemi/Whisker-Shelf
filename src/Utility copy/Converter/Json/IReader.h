#ifndef UTILITY_CONVERTER_JSON_IREADER_H
#define UTILITY_CONVERTER_JSON_IREADER_H

#include <QJsonObject>
#include "../../../Sensor/AbstractSensor.h"

namespace Utility {
    namespace Converter {
        namespace Json {
            class IReader {
                public:
                    virtual ~IReader(){};
                    virtual Sensor::AbstractSensor* read(const QJsonObject& object) = 0;
            };
        }
    }
}
#endif
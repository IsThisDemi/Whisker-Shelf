#ifndef UTILITY_CONVERTER_JSON_JSON_VISITOR_H
#define UTILITY_CONVERTER_JSON_JSON_VISITOR_H

#include <QJsonObject>
#include "../../../Sensor/IConstVisitor.h"
#include "../../../Sensor/Humidity.h"
#include "../../../Sensor/Light.h"
#include "../../../Sensor/Temperature.h"
#include "../../../Sensor/Wind.h"

#include "Json.h"

namespace Utility
{
    namespace Converter
    {
        namespace Json
        {

            class JsonVisitor : public Sensor::IConstVisitor
            {
            private:
                QJsonObject object;

            public:
                QJsonObject getObject() const;
                
                void visit(const Sensor::Humidity &humidity);
                void visit(const Sensor::Light &light);
                void visit(const Sensor::Temperature &temperature);
                void visit(const Sensor::Wind &wind);
            };
        }
    }
}

#endif
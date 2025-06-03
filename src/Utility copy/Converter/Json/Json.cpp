#include "Json.h"
#include <QJsonArray>

namespace Utility
{
    namespace Converter
    {
        namespace Json
        {
            // Convert a sensor object to a JSON object
            QJsonObject Json::fromObject(const Sensor::AbstractSensor &sensor)
            {
                JsonVisitor json_visitor;        // Create a JsonVisitor instance
                sensor.accept(json_visitor);     // Accept the visitor to populate the JSON object
                return json_visitor.getObject(); // Return the JSON object created by the visitor
            }

            // Convert a JSON object to a sensor object
            Sensor::AbstractSensor &Json::toObject(const QJsonObject &json)
            {
                Reader reader;               // Create a Reader instance
                return *(reader.read(json)); // Read the JSON object and return the corresponding sensor object
            }

        }
    }
}

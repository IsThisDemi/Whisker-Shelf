#ifndef SENSOR_I_CONST_VISITOR_H
#define SENSOR_I_CONST_VISITOR_H

namespace Sensor {
    class Humidity;
    class Light;
    class Temperature;
    class Wind;

    class IConstVisitor {
        public:
            virtual ~IConstVisitor() = default;
            virtual void visit(const Humidity& humidity) = 0;
            virtual void visit(const Light& light) = 0;
            virtual void visit(const Temperature& temperature) = 0;
            virtual void visit(const Wind& wind) = 0;
    };
}
#endif
#ifndef SENSOR_I_VISITOR_H
#define SENSOR_I_VISITOR_H

namespace Sensor
{
    class Humidity;
    class Light;
    class Temperature;
    class Wind;

    class IVisitor
    {
    public:
        virtual ~IVisitor(){};
        virtual void visit(Humidity &humidity) = 0;
        virtual void visit(Light &light) = 0;
        virtual void visit(Temperature &temperature) = 0;
        virtual void visit(Wind &wind) = 0;
    };
}
#endif
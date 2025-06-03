#include "AboveChartLabelsCreatorVisitor.h"

namespace View
{

    // Constructor initializing the AboveChartWidget pointer
    AboveChartLabelsCreatorVisitor::AboveChartLabelsCreatorVisitor(AboveChartWidget *aboveChartWidget)
        : aboveChartWidget(aboveChartWidget) {}

    // Visit method for Humidity sensor
    void AboveChartLabelsCreatorVisitor::visit(const Sensor::Humidity &humidity)
    {
        // Create labels for Humidity sensor with its accuracy and humidity level
        aboveChartWidget->createTheRestOfLabelsHumidity(humidity.getAccuracy(), humidity.getHumidity());
    }

    // Visit method for Light sensor
    void AboveChartLabelsCreatorVisitor::visit(const Sensor::Light &light)
    {
        // Create labels for Light sensor with its color, intensity, and signal strength
        aboveChartWidget->createTheRestOfLabelsLight(light.getColor(), light.getIntensity(), light.getSignalStrength());
    }

    // Visit method for Temperature sensor
    void AboveChartLabelsCreatorVisitor::visit(const Sensor::Temperature &temperature)
    {
        // Create labels for Temperature sensor with its accuracy, temperature, and unit
        aboveChartWidget->createTheRestOfLabelsTemperature(temperature.getAccuracy(), temperature.getTemperature(), temperature.getUnit());
    }

    // Visit method for Wind sensor
    void AboveChartLabelsCreatorVisitor::visit(const Sensor::Wind &wind)
    {
        // Create labels for Wind sensor with its accuracy, direction, speed, and unit
        aboveChartWidget->createTheRestOfLabelsWind(wind.getAccuracy(), wind.getDirection(), wind.getSpeed(), wind.getUnit());
    }

}

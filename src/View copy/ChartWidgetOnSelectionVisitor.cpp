#include "ChartWidgetOnSelectionVisitor.h"


namespace View {

// Constructor
ChartWidgetOnSelectionVisitor::ChartWidgetOnSelectionVisitor(ChartWidget* chartWidget)
    : chartWidget(chartWidget)
{}

// Visit Humidity sensor
void ChartWidgetOnSelectionVisitor::visit(const Sensor::Humidity& humidity) {
    chartWidget->chartWidgetOnHumiditySelected(humidity);
}

// Visit Light sensor
void ChartWidgetOnSelectionVisitor::visit(const Sensor::Light& light) {
    chartWidget->chartWidgetOnLightSelected(light);
}

// Visit Temperature sensor
void ChartWidgetOnSelectionVisitor::visit(const Sensor::Temperature& temperature) {
    chartWidget->chartWidgetOnTemperatureSelected(temperature);
}

// Visit Wind sensor
void ChartWidgetOnSelectionVisitor::visit(const Sensor::Wind& wind) {
    chartWidget->chartWidgetOnWindSelected(wind);
}

}

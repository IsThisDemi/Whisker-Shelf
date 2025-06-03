#include "ChartWidgetOnSelectionVisitor.h"


namespace View {

// Constructor
ChartWidgetOnSelectionVisitor::ChartWidgetOnSelectionVisitor(ChartWidget* chartWidget)
    : chartWidget(chartWidget)
{}

// Visit methods commented out since they're not used with media
/*
void ChartWidgetOnSelectionVisitor::visit(const Sensor::Humidity& humidity) {
    chartWidget->chartWidgetOnHumiditySelected(humidity);
}

void ChartWidgetOnSelectionVisitor::visit(const Sensor::Light& light) {
    chartWidget->chartWidgetOnLightSelected(light);
}

void ChartWidgetOnSelectionVisitor::visit(const Sensor::Temperature& temperature) {
    chartWidget->chartWidgetOnTemperatureSelected(temperature);
}

void ChartWidgetOnSelectionVisitor::visit(const Sensor::Wind& wind) {
    chartWidget->chartWidgetOnWindSelected(wind);
}
*/

}

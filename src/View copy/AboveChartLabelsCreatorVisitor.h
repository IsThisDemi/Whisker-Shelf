#ifndef ABOVE_CHART_LABELS_CREATOR_VISITOR_H
#define ABOVE_CHART_LABELS_CREATOR_VISITOR_H

#include "AboveChartWidget.h"
#include "../Sensor/Humidity.h"

namespace View {

class AboveChartLabelsCreatorVisitor : public Sensor::IConstVisitor {
private:
    AboveChartWidget* aboveChartWidget;

public:
    AboveChartLabelsCreatorVisitor(AboveChartWidget* aboveChartWidget);

    void visit(const Sensor::Humidity& humidity) override;
    void visit(const Sensor::Light& light) override;
    void visit(const Sensor::Temperature& temperature) override;
    void visit(const Sensor::Wind& wind) override;
};

}

#endif

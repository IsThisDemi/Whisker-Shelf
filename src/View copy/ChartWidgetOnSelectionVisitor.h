#ifndef CHARTWIDGETONSELECTIONVISITOR_H
#define CHARTWIDGETONSELECTIONVISITOR_H

#include "ChartWidget.h"
#include "../Sensor/Humidity.h"

namespace View {

class ChartWidgetOnSelectionVisitor : public Sensor::IConstVisitor {
private:
    ChartWidget* chartWidget;

public:
    ChartWidgetOnSelectionVisitor(ChartWidget* chartWidget);

    void visit(const Sensor::Humidity& humidity) override;
    void visit(const Sensor::Light& light) override;
    void visit(const Sensor::Temperature& temperature) override;
    void visit(const Sensor::Wind& wind) override;
};

}

#endif

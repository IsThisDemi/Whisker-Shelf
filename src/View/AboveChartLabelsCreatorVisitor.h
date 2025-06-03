#ifndef ABOVE_CHART_LABELS_CREATOR_VISITOR_H
#define ABOVE_CHART_LABELS_CREATOR_VISITOR_H

#include "AboveChartWidget.h"
#include "../Media/Book.h"

namespace View {

class AboveChartLabelsCreatorVisitor : public Media::IConstVisitor {
private:
    AboveChartWidget* aboveChartWidget;

public:
    AboveChartLabelsCreatorVisitor(AboveChartWidget* aboveChartWidget);

    void visit(const Media::Article& article) override;
    void visit(const Media::Audio& audio) override;
    void visit(const Media::Book& book) override;
    void visit(const Media::Film& film) override;
};

}

#endif

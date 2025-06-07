#ifndef ABOVE_IMAGE_LABELS_CREATOR_VISITOR_H
#define ABOVE_IMAGE_LABELS_CREATOR_VISITOR_H

#include "AboveImageWidget.h"
#include "../Media/Book.h"

namespace View {

class AboveImageLabelsCreatorVisitor : public Media::IConstVisitor {
private:
    AboveImageWidget* aboveImageWidget;

public:
    AboveImageLabelsCreatorVisitor(AboveImageWidget* aboveImageWidget);

    void visit(const Media::Article& article) override;
    void visit(const Media::Audio& audio) override;
    void visit(const Media::Book& book) override;
    void visit(const Media::Film& film) override;
};

}

#endif

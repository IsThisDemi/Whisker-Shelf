#ifndef SET_TYPE_AND_ICON_OF_MEDIA_WIDGET_VISITOR_H
#define SET_TYPE_AND_ICON_OF_MEDIA_WIDGET_VISITOR_H

#include "MediaPanel.h"
#include "../Media/Article.h"

namespace View
{

    class SetTypeAndIconOfMediaWidgetVisitor : public Media::IConstVisitor
    {
    private:
        MediaPanel *mediaPanel;
        MediaWidget *targetWidget;

    public:
        SetTypeAndIconOfMediaWidgetVisitor(MediaPanel *mediaPanel, MediaWidget* widget);

        void visit(const Media::Article &article) override;
        void visit(const Media::Audio &audio) override;
        void visit(const Media::Book &book) override;
        void visit(const Media::Film &film) override;
    };

}

#endif
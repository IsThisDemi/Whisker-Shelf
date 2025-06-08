#include "SetTypeAndIconOfMediaWidgetVisitor.h"

namespace View
{

    SetTypeAndIconOfMediaWidgetVisitor::SetTypeAndIconOfMediaWidgetVisitor(MediaPanel *mediaPanel, MediaWidget* widget)
        : mediaPanel(mediaPanel), targetWidget(widget) {}

    // Set the icon of the media widget according to the type of the media
    void SetTypeAndIconOfMediaWidgetVisitor::visit(const Media::Article &)
    {
        mediaPanel->setIconOfMediaWidget(QIcon(":/Assets/Icons/Medias/article.png"), targetWidget);
    }

    void SetTypeAndIconOfMediaWidgetVisitor::visit(const Media::Audio &)
    {
        mediaPanel->setIconOfMediaWidget(QIcon(":/Assets/Icons/Medias/audio.png"), targetWidget);
    }

    void SetTypeAndIconOfMediaWidgetVisitor::visit(const Media::Book &)
    {
        mediaPanel->setIconOfMediaWidget(QIcon(":/Assets/Icons/Medias/book.png"), targetWidget);
    }

    void SetTypeAndIconOfMediaWidgetVisitor::visit(const Media::Film &)
    {
        mediaPanel->setIconOfMediaWidget(QIcon(":/Assets/Icons/Medias/movie.png"), targetWidget);
    }

}

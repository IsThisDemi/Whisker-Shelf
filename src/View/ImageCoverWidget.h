#ifndef IMAGE_COVER_WIDGET_H
#define IMAGE_COVER_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

namespace View
{
    class ImageCoverWidget : public QWidget
    {
        Q_OBJECT

    private:
        QVBoxLayout *layout;
        QLabel *imageLabel;

    public:
        ImageCoverWidget(QWidget *parent = nullptr);
        void setImage(const QString &imagePath);
        ~ImageCoverWidget();
    };
}

#endif

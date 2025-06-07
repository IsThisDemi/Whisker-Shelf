#include "ImageCoverWidget.h"

namespace View
{
    ImageCoverWidget::ImageCoverWidget(QWidget *parent) : QWidget(parent),
                                                         layout(nullptr),
                                                         imageLabel(nullptr)
    {
        layout = new QVBoxLayout(this);
        imageLabel = new QLabel(this);
        imageLabel->setScaledContents(true);
        imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(imageLabel);
        setLayout(layout);
    }

    void ImageCoverWidget::setImage(const QString &imagePath)
    {
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            imageLabel->setPixmap(pixmap);
        } else {
            // Se non c'è immagine, mostra un'immagine placeholder
            QPixmap defaultPixmap(":/Assets/Icons/media.png");
            imageLabel->setPixmap(defaultPixmap);
        }
    }

    ImageCoverWidget::~ImageCoverWidget()
    {
        delete imageLabel;
        delete layout;
    }
}

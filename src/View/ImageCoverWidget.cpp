#include "ImageCoverWidget.h"

namespace View
{
    ImageCoverWidget::ImageCoverWidget(QWidget *parent) : QWidget(parent),
                                                         layout(nullptr),
                                                         imageLabel(nullptr)
    {
        layout = new QVBoxLayout(this);
        imageLabel = new QLabel(this);
        imageLabel->setScaledContents(false);
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(imageLabel);
        layout->setAlignment(Qt::AlignCenter);
        setLayout(layout);
    }

    void ImageCoverWidget::resizeEvent(QResizeEvent *event)
    {
        QWidget::resizeEvent(event);
        if (!currentImagePath.isEmpty()) {
            setImage(currentImagePath);
        }
    }

    void ImageCoverWidget::setImage(const QString &imagePath)
    {
        currentImagePath = imagePath;
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            // Scala l'immagine mantenendo l'aspect ratio per adattarla al widget
            QSize widgetSize = size();
            QPixmap scaledPixmap = pixmap.scaled(widgetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);
        } else {
            // Se non c'è immagine, mostra un'immagine placeholder
            QPixmap defaultPixmap(":/Assets/Icons/media.png");
            QSize widgetSize = size();
            QPixmap scaledPixmap = defaultPixmap.scaled(widgetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);
        }
    }

    ImageCoverWidget::~ImageCoverWidget()
    {
        delete imageLabel;
        delete layout;
    }
}

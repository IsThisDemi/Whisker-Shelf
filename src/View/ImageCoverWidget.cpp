#include "ImageCoverWidget.h"
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>

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

        QString absolutePath;
        if (imagePath.startsWith(":/")) {
            absolutePath = imagePath;
        } else {
            // Get the directory of the running binary
            QDir binDir(QCoreApplication::applicationDirPath());
            binDir.cdUp(); // MacOS
            binDir.cdUp(); // Contents
            binDir.cdUp(); // WhiskerShelf.app

            // Se il percorso inizia con "../../../", rimuovi il prefisso
            QString adjustedPath = imagePath;
            if (adjustedPath.startsWith("../../../")) {
                adjustedPath.remove(0, 9); // rimuovi "../../../"
            }
            
            // Costruisci il percorso assoluto
            absolutePath = binDir.absoluteFilePath(adjustedPath);
        }

        QPixmap pixmap(absolutePath);

        if (!pixmap.isNull()) {
            QSize widgetSize = size();
            QPixmap scaledPixmap = pixmap.scaled(widgetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);
        } else {
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

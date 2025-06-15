#include "ImageCoverWidget.h"
#include <QDir>
#include <QCoreApplication>
#include <QFileInfo>
#include <QStandardPaths>

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
            QString filename = QFileInfo(imagePath).fileName();
#ifdef Q_OS_MAC
            QString appPath = QCoreApplication::applicationDirPath();
            QDir binDir(appPath);
            if (binDir.absolutePath().contains("WhiskerShelf.app")) {
                binDir.cdUp();
                binDir.cdUp();
                binDir.cdUp();
            }
            absolutePath = binDir.absoluteFilePath("images/" + filename);
#else
            // Su Linux, se esegui da src, cerca direttamente in images/
            QDir currentDir(QDir::currentPath());
            absolutePath = currentDir.absoluteFilePath("images/" + filename);
#endif
        }

        QPixmap pixmap;
        if (!absolutePath.isEmpty() && QFile::exists(absolutePath)) {
            pixmap.load(absolutePath);
        }

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

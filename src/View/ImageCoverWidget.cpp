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
            // Get the application directory path and create base directory
            QString appPath = QCoreApplication::applicationDirPath();
            QDir binDir(appPath);
            
            #ifdef Q_OS_MAC
                if (binDir.absolutePath().contains("WhiskerShelf.app")) {
                    binDir.cdUp(); // up from MacOS
                    binDir.cdUp(); // up from Contents
                    binDir.cdUp(); // up from .app
                }
            #else
                binDir.cdUp(); // just up from build directory
            #endif

            // Try to load the image using the exact path provided
            if (!imagePath.isEmpty()) {
                QString directPath = binDir.absoluteFilePath(imagePath);
                if (QFile::exists(directPath)) {
                    absolutePath = directPath;
                }
            }
            
            // If direct path failed, try the default location
            if (absolutePath.isEmpty() || !QFile::exists(absolutePath)) {
                QString filename = QFileInfo(imagePath).fileName();
                #ifdef Q_OS_MAC
                    absolutePath = binDir.absoluteFilePath("images/" + filename);
                #else
                    absolutePath = binDir.absoluteFilePath("src/images/" + filename);
                #endif
            }
        }

        // Try to load the image
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

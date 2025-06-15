#include "ImageCoverWidget.h"
#include <QDir>
#include <QCoreApplication>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDebug>

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
        qDebug() << "[setImage] received path:" << imagePath;
        if (!imageLabel) {
            qDebug() << "[setImage] imageLabel is null!";
            return;
        }
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
            QDir currentDir(QDir::currentPath());
            absolutePath = currentDir.absoluteFilePath("images/" + filename);
#endif
        }
        qDebug() << "[setImage] absolutePath:" << absolutePath;
        qDebug() << "[setImage] file exists:" << QFile::exists(absolutePath);

        QPixmap pixmap;
        if (!absolutePath.isEmpty() && QFile::exists(absolutePath)) {
            pixmap.load(absolutePath);
        }

        if (!pixmap.isNull()) {
            QSize widgetSize = size();
            QPixmap scaledPixmap = pixmap.scaled(widgetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);
            qDebug() << "[setImage] pixmap loaded and set.";
        } else {
            QPixmap defaultPixmap(":/Assets/Icons/media.png");
            QSize widgetSize = size();
            QPixmap scaledPixmap = defaultPixmap.scaled(widgetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);
            qDebug() << "[setImage] default pixmap set.";
        }
    }

    ImageCoverWidget::~ImageCoverWidget()
    {
        if (imageLabel) {
            delete imageLabel;
            imageLabel = nullptr;
        }
        if (layout) {
            delete layout;
            layout = nullptr;
        }
    }
}

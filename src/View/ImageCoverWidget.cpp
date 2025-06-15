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
        qDebug() << "ImageCoverWidget::setImage - Received path:" << imagePath;
        currentImagePath = imagePath;

        QString absolutePath;
        if (imagePath.startsWith(":/")) {
            absolutePath = imagePath;
            qDebug() << "Resource path detected:" << absolutePath;
        } else {
            // Get the application directory path
            QString appPath = QCoreApplication::applicationDirPath();
            
            // Create a QDir object for the current binary location
            QDir binDir(appPath);

            #ifdef Q_OS_MAC
                // On macOS, we need to go up three levels from the .app bundle
                if (binDir.absolutePath().contains("WhiskerShelf.app")) {
                    binDir.cdUp(); // up from MacOS
                    binDir.cdUp(); // up from Contents
                    binDir.cdUp(); // up from .app
                }
            #else
                // On Linux, just go up one level from the build directory
                binDir.cdUp();
            #endif

            // Get just the filename, stripping any path
            QString filename = QFileInfo(imagePath).fileName();
            
            #ifdef Q_OS_MAC
                absolutePath = binDir.absoluteFilePath("images/" + filename);
                qDebug() << "Mac path:" << absolutePath;
            #else
                QString srcPath = binDir.absoluteFilePath("src/images/" + filename);
                if (QFile::exists(srcPath)) {
                    absolutePath = srcPath;
                    qDebug() << "Linux - Found at:" << absolutePath;
                } else {
                    // Se non esiste, usa il percorso base src/images
                    absolutePath = srcPath;
                    qDebug() << "Linux - Using default path:" << absolutePath;
                }
            #endif
            
            // Verifica se il file esiste
            QFileInfo check_file(absolutePath);
        }

        qDebug() << "Final absolute path:" << absolutePath;
        qDebug() << "File exists:" << QFile::exists(absolutePath);
        
        QPixmap pixmap(absolutePath);
        qDebug() << "Pixmap is null:" << pixmap.isNull();

        if (!pixmap.isNull()) {
            QSize widgetSize = size();
            QPixmap scaledPixmap = pixmap.scaled(widgetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);
            qDebug() << "Successfully set pixmap";
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

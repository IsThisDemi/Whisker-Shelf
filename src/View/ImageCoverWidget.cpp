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

            // Handle the image path
            QString adjustedPath = imagePath;
            
            // Rimuovi il prefisso relativo "../../../src/" se presente
            if (adjustedPath.startsWith("../../../src/")) {
                adjustedPath = adjustedPath.mid(13); // rimuovi "../../../src/"
            }
            
            // Costruisci il percorso assoluto
            absolutePath = binDir.absoluteFilePath("images/" + QFileInfo(adjustedPath).fileName());
            
            // Verifica se il file esiste
            QFileInfo check_file(absolutePath);
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

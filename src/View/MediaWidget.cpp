#include "MediaWidget.h"
#include <stdexcept>

namespace View
{

    // Constructor for MediaWidget
    MediaWidget::MediaWidget(QWidget *parent) : QWidget(parent)
    {
        // Create main layout for this widget
        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        // Create custom background widget
        backgroundWidget = new QWidget(this);
        backgroundWidget->setObjectName("backgroundWidget");
        backgroundWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

        // Set layout for background widget
        layout = new QHBoxLayout(backgroundWidget);
        layout->setContentsMargins(16, 12, 16, 12);
        layout->setSpacing(16);

        // Create icon and set its size
        iconLabel = new QLabel(this);
        iconLabel->setObjectName("iconLabel");
        iconLabel->setFixedSize(64, 64);
        iconLabel->setAlignment(Qt::AlignCenter);

        // Create container for data section
        QWidget* dataContainer = new QWidget(backgroundWidget);
        dataContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        
        dataLayout = new QVBoxLayout(dataContainer);
        dataLayout->setContentsMargins(0, 0, 0, 0);
        dataLayout->setSpacing(2);

        // Create labels for media data
        nameLabel = new QLabel(dataContainer);
        nameLabel->setObjectName("nameLabel");
        nameLabel->setWordWrap(true);
        nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        
        idLabel = new QLabel(dataContainer);
        idLabel->setObjectName("idLabel");
        idLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        
        dataLabel = new QLabel(dataContainer);
        dataLabel->setObjectName("dataLabel");
        dataLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        
        descriptionLabel = new QLabel(dataContainer);
        descriptionLabel->setObjectName("descriptionLabel");
        descriptionLabel->setWordWrap(true);

        // Set fonts and styles
        QFont titleFont = nameLabel->font();
        titleFont.setPointSize(13);
        titleFont.setWeight(QFont::DemiBold);
        nameLabel->setFont(titleFont);

        QFont dataFont = dataLabel->font();
        dataFont.setPointSize(12);
        dataLabel->setFont(dataFont);
        
        QFont descFont = descriptionLabel->font();
        descFont.setPointSize(11);
        descriptionLabel->setFont(descFont);

        // Add widgets to layouts
        layout->addWidget(iconLabel);
        
        dataLayout->addWidget(nameLabel);
        dataLayout->addWidget(dataLabel);
        dataLayout->addWidget(descriptionLabel);
        dataLayout->addStretch();
        dataLayout->addWidget(idLabel);
        idLabel->hide();
        
        layout->addWidget(dataContainer, 1);  // Give data section more stretch
        
        mainLayout->addWidget(backgroundWidget);

        // Set name for CSS styling
        setObjectName("MediaWidget");

        // Set layout as main layout of widget
        setLayout(layout);
    }

    // Handle mouse press event, emit selected signal if left button is pressed
    void MediaWidget::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            emit selected(this);
        }
        QWidget::mousePressEvent(event);
    }

    // Set the background color of the widget
    void MediaWidget::setBackGroundColor(const QColor &color)
    {
        if (backgroundWidget != nullptr) {
            QPalette pal = backgroundWidget->palette();
            pal.setColor(QPalette::Window, color);
            backgroundWidget->setPalette(pal);
            backgroundWidget->setAutoFillBackground(true);
            // Remove previous style set in QSS
            backgroundWidget->setStyleSheet("QWidget#backgroundWidget { background-color: white; border: 7px solid " + color.name() + "; }");
            backgroundWidget->update();
        }
    }

    // Get the name of the media
    std::string MediaWidget::getName() const
    {
        return nameLabel->text().toStdString();
    }

    // Get the ID of the media
    unsigned int MediaWidget::getId() const
    {
        bool ok;
        QString idText = idLabel->text();
        QString idSubstring = idText.mid(4);
        unsigned int id = idSubstring.toUInt(&ok);
        if (ok) {
            return id;
        } else {
            // Handle error if ID is not a valid integer
            qWarning() << "ID not valid!";
            throw std::exception();
        }
    }

    // Set the icon of the media
    void MediaWidget::setIcon(const QIcon &icon)
    {
        iconLabel->setPixmap(icon.pixmap(32, 32)); // Set icon with fixed dimensions
    }

    // Set the name of the media
    void MediaWidget::setName(const QString &name)
    {
        nameLabel->setText(name);
    }

    // Set the ID of the media
    void MediaWidget::setId(const int &id)
    {
        idLabel->setText(QString("ID: %1").arg(id));
    }

    // Set the data of the media
    void MediaWidget::setData(const double &data, const QString &unit)
    {
        dataLabel->setText(QString("%L1%2").arg(data, 0, 'f', 0).arg(unit));
    }

    // Destructor, delete all widgets
    MediaWidget::~MediaWidget()
    {
        // Delete owned widgets in reverse order of creation
        delete dataLabel;
        delete idLabel;
        delete nameLabel;
        delete iconLabel;
        delete dataLayout;
        delete layout;
        delete backgroundWidget;
        
        // Set pointers to nullptr to prevent use-after-free
        dataLabel = nullptr;
        idLabel = nullptr;
        nameLabel = nullptr;
        iconLabel = nullptr;
        dataLayout = nullptr;
        layout = nullptr;
        backgroundWidget = nullptr;
    }

}
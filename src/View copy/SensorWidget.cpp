#include "SensorWidget.h"
#include <stdexcept>

namespace View
{

    // Constructor for SensorWidget
    SensorWidget::SensorWidget(QWidget *parent) : QWidget(parent)
    {
        // Create custom background widget
        backgroundWidget = new QWidget(this);
        backgroundWidget->setObjectName("backgroundWidget");
        backgroundWidget->setFixedSize(124, 124);

        // Set layout for background widget
        layout = new QVBoxLayout(backgroundWidget);
        layout->setAlignment(Qt::AlignHCenter);

        // Create icon and set its size
        iconLabel = new QLabel(this);
        iconLabel->setObjectName("iconLabel");
        iconLabel->setFixedSize(50, 50);
        iconLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        // Add icon to background widget layout
        layout->addWidget(iconLabel, 0, Qt::AlignHCenter);

        // Create layout for data labels
        dataLayout = new QVBoxLayout;
        dataLayout->setAlignment(Qt::AlignHCenter);

        // Create labels for sensor data
        nameLabel = new QLabel(backgroundWidget);
        nameLabel->setObjectName("nameLabel");
        idLabel = new QLabel(backgroundWidget);
        idLabel->setObjectName("idLabel");
        dataLabel = new QLabel(backgroundWidget);
        dataLabel->setObjectName("dataLabel");

        // Set font size for sensor name label
        QFont font = nameLabel->font();
        font.setPointSize(16);
        nameLabel->setFont(font);
        nameLabel->setContentsMargins(0,0,0,0);

        // Set font size for sensor data label
        font = dataLabel->font();
        font.setPointSize(24);
        dataLabel->setFont(font);
        dataLabel->setContentsMargins(0,0,0,0);

        // Add labels to data layout
        dataLayout->addWidget(nameLabel, 0, Qt::AlignHCenter);
        dataLayout->addWidget(idLabel, 0, Qt::AlignHCenter);
        idLabel->hide();
        dataLayout->addWidget(dataLabel, 0, Qt::AlignHCenter);

        // Add data layout to background widget layout
        layout->addLayout(dataLayout);

        // Set size of SensorWidget
        setFixedSize(124, 124);

        // Set name for CSS styling
        setObjectName("SensorWidget");

        // Set layout as main layout of widget
        setLayout(layout);
    }

    // Handle mouse press event, emit selected signal if left button is pressed
    void SensorWidget::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            emit selected(this);
        }
        QWidget::mousePressEvent(event);
    }

    // Set the background color of the widget
    void SensorWidget::setBackGroundColor(const QColor &color)
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

    // Get the name of the sensor
    std::string SensorWidget::getName() const
    {
        return nameLabel->text().toStdString();
    }

    // Get the ID of the sensor
    unsigned int SensorWidget::getId() const
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

    // Set the icon of the sensor
    void SensorWidget::setIcon(const QIcon &icon)
    {
        iconLabel->setPixmap(icon.pixmap(32, 32)); // Set icon with fixed dimensions
    }

    // Set the name of the sensor
    void SensorWidget::setName(const QString &name)
    {
        nameLabel->setText(name);
    }

    // Set the ID of the sensor
    void SensorWidget::setId(const int &id)
    {
        idLabel->setText(QString("ID: %1").arg(id));
    }

    // Set the data of the sensor
    void SensorWidget::setData(const double &data, const QString &unit)
    {
        dataLabel->setText(QString("%L1%2").arg(data, 0, 'f', 0).arg(unit));
    }

    // Destructor, delete all widgets
    SensorWidget::~SensorWidget()
    {
        delete iconLabel;

        delete nameLabel;
        delete idLabel;
        delete dataLabel;

        delete dataLayout;
        delete backgroundWidget;
        delete layout;
    }

}
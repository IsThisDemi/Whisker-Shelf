#ifndef VIEW_MEDIA_WIDGET_H
#define VIEW_MEDIA_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QMouseEvent>

namespace View
{
    class MediaWidget : public QWidget
    {
        Q_OBJECT
    private:
        QWidget *backgroundWidget;
        QHBoxLayout *layout;

        // Left section with icon
        QLabel *iconLabel;

        // Right section with data
        QVBoxLayout *dataLayout;
        QLabel *nameLabel;
        QLabel *idLabel;
        QLabel *dataLabel;
        QLabel *descriptionLabel;  // New label for extra info
    
    signals:
        void selected(MediaWidget *sender);

    public:
        explicit MediaWidget(QWidget *parent = nullptr);

        void mousePressEvent(QMouseEvent *event) override;
        void setBackGroundColor(const QColor &color);

        std::string getName() const;
        unsigned int getId() const;

        void setIcon(const QIcon &icon);
        void setName(const QString &name);
        void setId(const int &id);
        void setType(const QString &type);
        void setData(const double &data, const QString &unit);

        ~MediaWidget();
    };
}
#endif
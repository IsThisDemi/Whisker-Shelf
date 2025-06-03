#ifndef VIEW_ADD_SENSOR_DIALOGUE_WIDGET_H
#define VIEW_ADD_SENSOR_DIALOGUE_WIDGET_H

#include "AbstractDialogueWindow.h"

namespace View
{

    class AddSensorDialogueWindow : public AbstractDialogueWindow
    {
        Q_OBJECT

    private:
        QLabel *typeLabel;
        QLabel *idLabel;
        QLabel *nameLabel;
        QLabel *descriptionLabel;
        QLabel *brandLabel;

        QComboBox *typeComboBox;
        QLineEdit *idLineEdit;
        QLineEdit *nameLineEdit;
        QLineEdit *descriptionLineEdit;
        QLineEdit *brandLineEdit;

        QPushButton *discardButton;
        QPushButton *createButton;

        QVBoxLayout *mainLayout;
        QHBoxLayout *typeLayout;
        QHBoxLayout *idLayout;
        QHBoxLayout *nameLayout;
        QHBoxLayout *descriptionLayout;
        QHBoxLayout *brandLayout;
        QHBoxLayout *buttonsLayout;

    signals:
        void createAndAddSignal();
        void sensorAdded(Sensor::AbstractSensor *sensor);

    public slots:
        void createAndAddSlot();
        void discardChanges();

    public:
        explicit AddSensorDialogueWindow(AbstractDialogueWindow *parent = nullptr);

        bool differentFromOriginal();
        void createAndAddSensor(const std::vector<Sensor::AbstractSensor *> &sensors);

        ~AddSensorDialogueWindow();
    };

}

#endif

#ifndef MODIFYSENSORDIALOGUEWINDOW_H
#define MODIFYSENSORDIALOGUEWINDOW_H

#include "AbstractDialogueWindow.h"

namespace View
{

    class ModifySensorDialogueWindow : public AbstractDialogueWindow
    {
        Q_OBJECT

    private:
        unsigned int id;
        std::string type;
        std::string originalSensorName;
        std::string originalSensorDescription;
        std::string originalSensorBrand;
        double originalValue1;
        double originalValue2;
        std::string originalValue3;
        double originalValue4;

        QLabel *nameLabel;
        QLabel *descriptionLabel;
        QLabel *brandLabel;
        QLabel *value1Label;
        QLabel *value2Label;
        QLabel *value3Label;
        QLabel *value4Label;

        QLineEdit *nameLineEdit;
        QLineEdit *descriptionLineEdit;
        QLineEdit *brandLineEdit;
        QLineEdit *value1LineEdit;
        QLineEdit *value2LineEdit;
        QLineEdit *value3LineEdit;
        QLineEdit *value4LineEdit;

        QPushButton *discardButton;
        QPushButton *applyButton;

        QVBoxLayout *mainLayout;
        QHBoxLayout *nameLayout;
        QHBoxLayout *descriptionLayout;
        QHBoxLayout *brandLayout;
        QHBoxLayout *value1Layout;
        QHBoxLayout *value2Layout;
        QHBoxLayout *value3Layout;
        QHBoxLayout *value4Layout;
        QHBoxLayout *buttonsLayout;

    signals:
        void applySignal();
        void sensorModified(const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2,
                            const std::string &value3, const double &value4);
        void sensorNameModified(const std::string &previousName, const std::string &newName);

    public slots:
        void afterTextChanged();
        void discardChanges();
        void applySlot();

    public:
        explicit ModifySensorDialogueWindow(const unsigned int &Id, const std::string &Type, const std::string &OriginalSensorName, const std::string &OriginalSensorDescription,
                                            const std::string &OriginalSensorBrand, const double &OriginalValue1, const double &OriginalValue2,
                                            const std::string &OriginalValue3, const double &OriginalValue4, AbstractDialogueWindow *parent = nullptr);

        bool differentFromOriginal();
        void applyChanges(const std::vector<Sensor::AbstractSensor *> sensors);

        ~ModifySensorDialogueWindow();
    };

}

#endif

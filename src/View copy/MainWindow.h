#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QtCharts>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <vector>

#include "Utility/Repository/JsonRepository.h"
#include "AboveChartWidget.h"
#include "ChartWidget.h"
#include "SensorPanel.h"
#include "StatusBar.h"
#include "ToolBar.h"
namespace View
{

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    private:
        std::vector<Sensor::AbstractSensor *> sensors;
        Utility::Repository::JsonRepository *repository;

        bool isSaved;

        QWidget *centralWidget;
        QVBoxLayout *mainLayout;
        QHBoxLayout *centralLayout;
        QHBoxLayout *toolbarLayout;
        QVBoxLayout *chartLayout;

        StatusBar *statusBar;
        SensorPanel *sensorPanel;
        AboveChartWidget *aboveChartWidget;
        ChartWidget *chartWidget;
        ToolBar *toolBar;

    signals:
        void youCanCheckIfNameAndIDAreUnique(const std::vector<Sensor::AbstractSensor *> &sensors);
        void youCanCheckIfNameIsUnique(const std::vector<Sensor::AbstractSensor *> &sensors);

    public slots:
        void closeEvent(QCloseEvent *event);
        void openHandler();
        void saveHandler();
        void saveAsHandler();
        void fileOpenedHandler();
        void setIsSaved(const bool &value);
        void checkIfAreThereAnySensors();
        void searchHandler();
        void searchResultsHandler(const std::vector<SensorWidget *> &sensorWidgets);
        void returnBackHandler();
        void sensorSelectedHandler(const unsigned int &id);
        void sensorAddedHandler(Sensor::AbstractSensor *sensor);
        void createAndAddSensorHandler();
        void modifyHandler();
        void applyChangesHandler();
        void saveModifyHandler(const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2,
                               const std::string &value3, const double &value4);
        void nameModifiedHandler(const std::string &previousName, const std::string &newName);
        void sensorDeletedHandler();
        void simulationHandler();

    public:
        MainWindow(QWidget *parent = nullptr);

        bool maybeSave();
        Sensor::AbstractSensor *getCurrentlySelectedSensor();
        void setSensors();

        ~MainWindow();
    };
}
#endif // MAINWINDOW_H

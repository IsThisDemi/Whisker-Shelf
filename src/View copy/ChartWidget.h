#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <vector>

#include "../Chart/LineChart.h"
#include "../Sensor/AbstractSensor.h"

namespace View {

class ChartWidget : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout* verticalLayout;
    QGridLayout* gridLayout;

    QFrame* greyPanel1;

    Chart::LineChart* dataLineChart;

public:
    explicit ChartWidget(QWidget *parent = nullptr);

    void initialChartWidget();
    void chartWidgetOnSelection(Sensor::AbstractSensor* sensor);

    void chartWidgetOnHumiditySelected(const Sensor::Humidity& humidity);
    void chartWidgetOnLightSelected(const Sensor::Light& light);
    void chartWidgetOnTemperatureSelected(const Sensor::Temperature& temperature);
    void chartWidgetOnWindSelected(const Sensor::Wind& wind);

    void insertHumidityChart(Sensor::Humidity* humidity);
    void insertLightChart(Sensor::Light* light);
    void insertTemperatureChart(Sensor::Temperature* temperature);
    void insertWindChart(Sensor::Wind* wind);

    ~ChartWidget();
};

}

#endif 

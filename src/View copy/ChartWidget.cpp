#include "ChartWidget.h"
#include "ChartWidgetOnSelectionVisitor.h"

namespace View
{

    ChartWidget::ChartWidget(QWidget *parent)
        : QWidget(parent), verticalLayout(nullptr), gridLayout(nullptr), greyPanel1(nullptr), dataLineChart(nullptr)
    {
        // Initialize the chart widget
        initialChartWidget();
    }

    // Initialize the chart widget
    void ChartWidget::initialChartWidget()
    {
        // Deallocate previously allocated objects
        delete greyPanel1;
        delete dataLineChart;
        delete gridLayout;
        delete verticalLayout;

        // Set the pointers to nullptr
        greyPanel1 = nullptr;
        dataLineChart = nullptr;
        gridLayout = nullptr;
        verticalLayout = nullptr;

        greyPanel1 = new QFrame(this);
        greyPanel1->setObjectName("initialChartWidget");
        greyPanel1->setGeometry(0, 0, 714, 200);
        greyPanel1->show();
    }

    // Display the chart widget based on the selected sensor
    void ChartWidget::chartWidgetOnSelection(Sensor::AbstractSensor *sensor)
    {
        // Deallocate previously allocated objects
        delete greyPanel1;
        delete dataLineChart;
        delete gridLayout;
        delete verticalLayout;

        // Set the pointers to nullptr
        greyPanel1 = nullptr;
        dataLineChart = nullptr;
        gridLayout = nullptr;
        verticalLayout = nullptr;

        ChartWidgetOnSelectionVisitor visitor(this);
        sensor->accept(visitor);
    }

    // Display chart widget for humidity sensor
    void ChartWidget::chartWidgetOnHumiditySelected(const Sensor::Humidity &humidity)
    {
        // Prevent warning about unused parameter
        std::string name = humidity.getName();

        // Create layout and chart widget
        verticalLayout = new QVBoxLayout(this);
        greyPanel1 = new QFrame(this);
        greyPanel1->setObjectName("chartWidget");
        greyPanel1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        verticalLayout->addWidget(greyPanel1);
    }

    // Display chart widget for light sensor
    void ChartWidget::chartWidgetOnLightSelected(const Sensor::Light &light)
    {
        // Prevent warning about unused parameter
        std::string name = light.getName();

        // Create layout and chart widget
        verticalLayout = new QVBoxLayout(this);
        greyPanel1 = new QFrame(this);
        greyPanel1->setObjectName("chartWidget");
        greyPanel1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        verticalLayout->addWidget(greyPanel1);
    }

    // Display chart widget for temperature sensor
    void ChartWidget::chartWidgetOnTemperatureSelected(const Sensor::Temperature &temperature)
    {
        // Prevent warning about unused parameter
        std::string name = temperature.getName();

        // Create layout and chart widget
        verticalLayout = new QVBoxLayout(this);
        greyPanel1 = new QFrame(this);
        greyPanel1->setObjectName("chartWidget");
        greyPanel1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        verticalLayout->addWidget(greyPanel1);
    }

    // Display chart widget for wind sensor
    void ChartWidget::chartWidgetOnWindSelected(const Sensor::Wind &wind)
    {
        // Prevent warning about unused parameter
        std::string name = wind.getName();

        // Create layout and chart widget
        verticalLayout = new QVBoxLayout(this);
        greyPanel1 = new QFrame(this);
        greyPanel1->setObjectName("chartWidget");
        greyPanel1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        verticalLayout->addWidget(greyPanel1);
    }

    // Clear previously allocated objects and reset pointers
    void ChartWidget::insertHumidityChart(Sensor::Humidity *humidity)
    {
        // Delete dynamically allocated objects
        delete greyPanel1;
        delete dataLineChart;
        delete gridLayout;
        delete verticalLayout;

        // Set pointers to nullptr to indicate object deallocation
        greyPanel1 = nullptr;
        dataLineChart = nullptr;
        gridLayout = nullptr;
        verticalLayout = nullptr;

        // Create vertical layout to hold the chart
        verticalLayout = new QVBoxLayout(this);

        // Create line chart with humidity data and set object name and size policy
        dataLineChart = new Chart::LineChart(humidity);
        dataLineChart->setObjectName("lineChartWidget");
        dataLineChart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // Add line chart to vertical layout
        verticalLayout->addWidget(dataLineChart);
    }

    // Clean up previously allocated objects and reset pointers
    void ChartWidget::insertLightChart(Sensor::Light *light)
    {
        // Delete dynamically allocated objects
        delete greyPanel1;
        delete dataLineChart;
        delete gridLayout;
        delete verticalLayout;

        // Set pointers to nullptr to indicate object deallocation
        greyPanel1 = nullptr;
        dataLineChart = nullptr;
        gridLayout = nullptr;
        verticalLayout = nullptr;

        // Create new vertical layout
        verticalLayout = new QVBoxLayout(this);

        // Create new line chart and add it to the layout
        dataLineChart = new Chart::LineChart(light);
        dataLineChart->setObjectName("lineChartWidget");
        dataLineChart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        verticalLayout->addWidget(dataLineChart);
    }

    // Removes dynamically allocated objects previously allocated
    // Sets pointers to nullptr to indicate that the objects have been deallocated
    void ChartWidget::insertTemperatureChart(Sensor::Temperature *temperature)
    {
        // Remove previously allocated objects
        delete greyPanel1;
        delete dataLineChart;
        delete gridLayout;
        delete verticalLayout;

        // Set pointers to nullptr to indicate deallocation
        greyPanel1 = nullptr;
        dataLineChart = nullptr;
        gridLayout = nullptr;
        verticalLayout = nullptr;

        // Create new layout and add widget
        verticalLayout = new QVBoxLayout(this);
        dataLineChart = new Chart::LineChart(temperature);
        dataLineChart->setObjectName("lineChartWidget");
        dataLineChart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        verticalLayout->addWidget(dataLineChart);
    }

    // Remove dynamically allocated objects previously allocated
    // Set pointers to nullptr to signify that the objects have been deallocated
    void ChartWidget::insertWindChart(Sensor::Wind *wind)
    {
        delete greyPanel1;
        delete dataLineChart;
        delete gridLayout;
        delete verticalLayout;

        greyPanel1 = nullptr;
        dataLineChart = nullptr;
        gridLayout = nullptr;
        verticalLayout = nullptr;

        verticalLayout = new QVBoxLayout(this);

        dataLineChart = new Chart::LineChart(wind);
        dataLineChart->setObjectName("lineChartWidget");
        dataLineChart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        verticalLayout->addWidget(dataLineChart);
    }

    // Deallocate dynamically allocated objects in the destructor
    // This is necessary to avoid memory leaks
    ChartWidget::~ChartWidget()
    {
        delete greyPanel1;
        delete dataLineChart;
        delete gridLayout;
        delete verticalLayout;
    }

}

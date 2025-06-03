QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Chart/AbstractChart.cpp\
    Chart/ConcreteChartVisitor.cpp\
    Chart/LineChart.cpp\
    \
    Utility/Converter/Json/Json.cpp\
    Utility/Converter/Json/JsonVisitor.cpp\
    Utility/Converter/Json/Reader.cpp\
    \
    Utility/DataMapper/JsonFile.cpp\
    \
    Utility/Repository/JsonRepository.cpp\
    \
    Sensor/AbstractSensor.cpp\
    Sensor/Humidity.cpp\
    Sensor/Light.cpp\
    Sensor/Temperature.cpp\
    Sensor/Wind.cpp\
    \
    Media/AbstractMedia.cpp\
    Media/Article.cpp\
    Media/Audio.cpp\
    Media/Book.cpp\
    Media/Film.cpp\
    \
    main.cpp\
    \
    View/MainWindow.cpp\
    View/AboveChartLabelsCreatorVisitor.cpp\
    View/AboveChartWidget.cpp\
    View/AbstractDialogueWindow.cpp\
    View/AddSensorDialogueWindow.cpp\
    View/ChartWidget.cpp\
    View/ChartWidgetOnSelectionVisitor.cpp\
    View/ModifySensorDialogueWindow.cpp\
    View/SensorPanel.cpp\
    View/SensorWidget.cpp\
    View/SetTypeAndIconOfSensorWidgetVisitor.cpp\
    View/StatusBar.cpp\
    View/ToolBar.cpp

HEADERS += \
    Chart/AbstractChart.h\
    Chart/ConcreteChartVisitor.h\
    Chart/LineChart.h\
    \
    Utility/Converter/Json/IReader.h\
    Utility/Converter/Json/Json.h\
    Utility/Converter/Json/JsonVisitor.h\
    Utility/Converter/Json/Reader.h\
    \
    Utility/DataMapper/JsonFile.h\
    \
    Utility/Repository/IRepository.h\
    Utility/Repository/JsonRepository.h\
    \
    Sensor/AbstractSensor.h\
    Sensor/Humidity.h\
    Sensor/Light.h\
    Sensor/Temperature.h\
    Sensor/Wind.h\
    Sensor/IConstVisitor.h\
    Sensor/IVisitor.h\
    Sensor/SensorObserver.h\
    \
    Media/AbstractMedia.h\
    Media/Article.h\
    Media/Audio.h\
    Media/Book.h\
    Media/Film.h\
    Media/IConstVisitor.h\
    Media/IVisitor.h\
    Media/MediaObserver.h\
    \
    View/MainWindow.h\
    View/AboveChartLabelsCreatorVisitor.h\
    View/AboveChartWidget.h\
    View/AbstractDialogueWindow.h\
    View/AddSensorDialogueWindow.h\
    View/ChartWidget.h\
    View/ChartWidgetOnSelectionVisitor.h\
    View/ModifySensorDialogueWindow.h\
    View/SensorPanel.h\
    View/SensorWidget.h\
    View/SetTypeAndIconOfSensorWidgetVisitor.h\
    View/StatusBar.h\
    View/ToolBar.h

RESOURCES += \
    resources.qrc

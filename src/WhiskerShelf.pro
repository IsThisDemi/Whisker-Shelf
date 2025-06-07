QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Utility/Converter/Json/Json.cpp\
    Utility/Converter/Json/JsonVisitor.cpp\
    Utility/Converter/Json/Reader.cpp\
    \
    Utility/DataMapper/JsonFile.cpp\
    \
    Utility/Repository/JsonRepository.cpp\
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
    View/AboveImageLabelsCreatorVisitor.cpp\
    View/AboveChartWidget.cpp\
    View/AbstractDialogueWindow.cpp\
    View/AddMediaDialogueWindow.cpp\
    View/ModifyMediaDialogueWindow.cpp\
    View/MediaPanel.cpp\
    View/MediaWidget.cpp\
    View/SetTypeAndIconOfMediaWidgetVisitor.cpp\
    View/StatusBar.cpp\
    View/ToolBar.cpp\
    View/AboveImageWidget.cpp\
    View/ImageCoverWidget.cpp

HEADERS += \
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
    View/AboveImageLabelsCreatorVisitor.h\
    View/AboveChartWidget.h\
    View/AbstractDialogueWindow.h\
    View/AddMediaDialogueWindow.h\
    View/ModifyMediaDialogueWindow.h\
    View/MediaPanel.h\
    View/MediaWidget.h\
    View/SetTypeAndIconOfMediaWidgetVisitor.h\
    View/StatusBar.h\
    View/ToolBar.h\
    View/AboveImageWidget.h\
    View/ImageCoverWidget.h

RESOURCES += \
    resources.qrc

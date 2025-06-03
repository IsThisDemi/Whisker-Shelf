#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>

#include "View/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":Assets/appIcon.png"));

    QFile stylesheet(":Assets/style.qss");
    stylesheet.open(QFile::ReadOnly);
    a.setStyleSheet(QLatin1String(stylesheet.readAll()));

    View::MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}

#include "device\mainwindow.h"

#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    main_window w;
    w.show();
    return a.exec();
}

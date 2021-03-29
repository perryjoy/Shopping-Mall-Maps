#include <QApplication>

#include "device\mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.LoadFile("../resources/a.svg", "../resources/xml_from_excel.xml");
    w.Show();
    return a.exec();
}

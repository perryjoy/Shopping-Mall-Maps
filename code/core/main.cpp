#include <QApplication>

#include "device\mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    main_window w;
    w.LoadFile("a.svg");
    w.Show();
    return a.exec();
}

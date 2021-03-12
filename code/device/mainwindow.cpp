#include <QtWidgets>
#include <QSvgRenderer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "svgview.h"
#include "map.h"

main_window::main_window() :
    mapInfo(new map)
{
    resize(500, 500);
    timerId = startTimer(100);
    connect(mapInfo, &map::MapPictureChanged, this, &main_window::setNewView);
}

bool main_window::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest)
    {
        return true;
    }
    return QWidget::event(event);
}

void main_window::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId)
    {
        //QPaintEvent *e;
        ;
    }
}

void main_window::setNewView(svg_view * toSet)
{
    view = toSet;
}

bool main_window::LoadFile(const QString &fileName)
{
    if (QFileInfo::exists(fileName)) // maybe move checks to view module? - KYG
    {
        mapInfo->SetAnotherMap(fileName, __LEAVE_MAP_AS_IT_IS);
    }

    return false;
}

void main_window::Show()
{
    if (view != nullptr)
    {
        view->show();
    }
}

main_window::~main_window()
{
}

void main_window::Render(QPainter *p)
{
//    p->setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap));
//    p->drawPoint(100, 100);
}


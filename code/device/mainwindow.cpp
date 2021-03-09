#include <QtWidgets>
#include <QSvgRenderer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "svgview.h"

main_window::main_window() :
    view(new svg_view)
{
    resize(500, 500);
    timerId = startTimer(100);
    //setCentralWidget(m_view);
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

bool main_window::LoadFile(const QString &fileName)
{
    if (QFileInfo::exists(fileName))
    {
        if (view->OpenFile(fileName))
        {
            return true;
        }
    }

    return false;
}

void main_window::Show()
{
    view->show();
}

main_window::~main_window()
{
}

void main_window::Render(QPainter *p)
{
//    p->setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap));
//    p->drawPoint(100, 100);
}


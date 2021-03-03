#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

main_window::main_window(QWindow *parent)
    : QWindow(parent),
      backingStore(new QBackingStore(this))
{
    resize(500, 500);
    timerId = startTimer(100);
}

bool main_window::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest)
    {
        RenderNow();
        return true;
    }
    return QWindow::event(event);
}

void main_window::resizeEvent(QResizeEvent *resizeEvent)
{
    backingStore->resize(resizeEvent->size());
}

void main_window::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId)
    {
        requestUpdate();
    }
}

void main_window::exposeEvent(QExposeEvent *)
{
    if (isExposed())
    {
        RenderNow();
    }
}

void main_window::RenderNow()
{
    if (!isExposed())
    {
        return;
    }
    QRect rect(0, 0, width(), height());
    backingStore->beginPaint(rect);

    QPaintDevice *device = backingStore->paintDevice();
    QPainter painter(device);
    painter.fillRect(0, 0, width(), height(), QColor::fromRgb(255, 255, 255));
    Render(&painter);
    painter.end();

    backingStore->endPaint();
    backingStore->flush(rect);
}

main_window::~main_window()
{

}

void main_window::Render(QPainter *p)
{
    p->setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap));
    p->drawPoint(100, 100);
}


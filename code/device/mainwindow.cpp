#include <QtWidgets>
#include <QSvgRenderer>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() : QMainWindow(),
    m_zoomLabel(new QLabel),
    mapViewer(new viewer),
    mapInfo(new map)
{
    resize(500, 500);
    timerId = startTimer(100);
    connect(mapInfo, &map::MapPictureChanged, this, &MainWindow::setNewView);
    connect(mapViewer, &viewer::zoomChanged, this, &MainWindow::updateZoomLabel);
        // создаем кнопку
m_button = new QPushButton("Up", this);
m_button1 = new QPushButton("Down", this);

// устанавливаем размер и положение кнопки
m_button->setGeometry(QRect(QPoint(1800, 100),QSize(100, 50)));
m_button1->setGeometry(QRect(QPoint(1800, 150),QSize(100, 50)));

// подключаем сигнал к соответствующему слоту

connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));
connect(m_button1, SIGNAL (released()), this, SLOT (handleButton()));

}
void MainWindow::handleButton()
{


}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest)
    {
        return true;
    }
    return QWidget::event(event);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId)
    {
        ;
    }
}

void MainWindow::setNewView(QGraphicsSvgItem *toSet)
{
}

bool MainWindow::LoadFile(const QString &svgFileName, const QString &xmlFileName)
{
    if (QFileInfo::exists(svgFileName) && QFileInfo::exists(xmlFileName)) // maybe move checks to view module? - KYG
    {
        mapInfo->SetAnotherMap(svgFileName, xmlFileName);
        mapViewer->InitMap(svgFileName);
    }

    return false;
}


void MainWindow::Show()
{
    if (mapViewer != nullptr)
    {
        mapViewer->show();
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::Render(QPainter *p)
{
}

void MainWindow::updateZoomLabel()
{
    const int percent = qRound(mapViewer->GetMapPicScale() * float(100));
    m_zoomLabel->setText(QString::number(percent) + QLatin1Char('%'));
}

#include <QtWidgets>
#include <QSvgRenderer>
#include <QPushButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() : QMainWindow(),
    m_zoomLabel(new QLabel),
    mapViewer(new viewer),
    mapInfo(new map), layer(0)
{
    resize(500, 500);
    timerId = startTimer(100);
    connect(mapInfo, &map::MapPictureChanged, this, &MainWindow::setNewView);
    connect(mapViewer, &viewer::ZoomChanged, this, &MainWindow::updateZoomLabel);
    // create a button
    m_button_for_up = new QPushButton("Up", this);
    m_button_for_down = new QPushButton("Down", this);

    // set the size and position of the button
    m_button_for_up->setGeometry(QRect(QPoint(1800, 100),QSize(100, 50)));
    m_button_for_down->setGeometry(QRect(QPoint(1800, 150),QSize(100, 50)));

    // connect the signal to the corresponding slot
    connect(m_button_for_up, SIGNAL (released()), this, SLOT (handleButton()));
    connect(m_button_for_down, SIGNAL (released()), this, SLOT (handleButton()));

}
void MainWindow::ChangeLayer(void)
{
    this->layer = this->layer < 0 ? 0 : this->layer > 1 ? 1 : this->layer;
    switch (this->layer)
    {
    case 0:
        LoadFile(":/map1/floors.svg", ":/map1/xml_from_excel.xml");
        break;
    case 1:
    default:
        LoadFile(":/map1/floors.svg", ":/map1/xml_from_excel.xml");
    }
    Show();
}
void MainWindow::handleButtonUp()
{
    layer++;
    ChangeLayer();
}
void MainWindow::handleButtonDown()
{
    layer--;
    ChangeLayer();
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

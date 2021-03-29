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

    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    m_backgroundAction = viewMenu->addAction(tr("&Background"));
    m_backgroundAction->setEnabled(false);
    m_backgroundAction->setCheckable(true);
    m_backgroundAction->setChecked(false);
    //setCentralWidget(mapViewer);
    connect(m_backgroundAction, &QAction::toggled, mapViewer, &viewer::setViewBackground);

    connect(mapInfo, &map::MapPictureChanged, this, &MainWindow::setNewView);

    connect(mapViewer, &viewer::zoomChanged, this, &MainWindow::updateZoomLabel);
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
        //QPaintEvent *e;
        ;
    }
}

void MainWindow::setNewView(QGraphicsSvgItem *toSet)
{
    //mapViewer->InitMap(toSet);
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
//    p->setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap));
//    p->drawPoint(100, 100);
}

void MainWindow::updateZoomLabel()
{
    const int percent = qRound(mapViewer->GetMapPicScale() * qreal(100));
    m_zoomLabel->setText(QString::number(percent) + QLatin1Char('%'));
}

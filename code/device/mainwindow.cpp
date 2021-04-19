#include <QtWidgets>
#include <QSvgRenderer>
#include <QPushButton>
#include <QSignalMapper>
#include "mainwindow.h"
#include "manager.h"

MainWindow::MainWindow(class manager &mgr, bool customGraphicsView) : QMainWindow(),
    zoomLabel(new QLabel),
    manager(mgr)
{
    resize(800, 600);
    SetupUi(customGraphicsView);
}

void MainWindow::SetupUi(bool customGraphicsView)
{
    buttonMapper = new QSignalMapper();
    pathWidget = new PathWidget(this);
    buttonUp = new QPushButton("", this);
    buttonDown = new QPushButton("", this);
    buttonUp->setStyleSheet("QPushButton\
        {\
            image: url(:/based/UP.png);\
            background: transparent;\
            padding-top: 0px;\
            height: 200px;\
            width: 200px;\
        }\
    ");
    buttonDown->setStyleSheet("QPushButton\
        {\
            image: url(:/based/DOWN.png);\
            background: transparent;\
            padding-top: 0px;\
            height: 200px;\
            width: 200px;\
        }\
    ");
    //pathWidget->setGeometry(QRect(QPoint(this->size().width(), 0),QSize(500, 500)));
    buttonUp->setGeometry(QRect(QPoint(this->size().width(), this->size().height() / 2 - 100),QSize(200, 200)));
    buttonDown->setGeometry(QRect(QPoint(this->size().width(), this->size().height() / 2 + 100),QSize(200, 200)));

    buttonMapper->setMapping(buttonUp, BUTTON_UP);
    buttonMapper->setMapping(buttonDown, BUTTON_DOWN);

    connect(buttonUp, SIGNAL(released()), buttonMapper, SLOT(map()));
    connect(buttonDown, SIGNAL(released()), buttonMapper, SLOT(map()));

    connect(buttonMapper, &QSignalMapper::mappedInt, &manager, &manager::OnButton);

    centralWidget = new QWidget(this);
    horizontalLayout = new QHBoxLayout(centralWidget);

    horizontalLayout->addWidget(buttonDown);
    horizontalLayout->addWidget(buttonUp);
    horizontalLayout->addWidget(pathWidget);

    if (!customGraphicsView)
    {
        graphicsView = new QGraphicsView(centralWidget);
        horizontalLayout->addWidget(graphicsView);
        setCentralWidget(centralWidget);
    }
    else
    {
        graphicsView = nullptr;
    }

    setWindowTitle("MainWindow");
}

void MainWindow::SetView(QGraphicsView *view)
{
    if (graphicsView)
    {
        delete graphicsView;
    }
    graphicsView = view;
    horizontalLayout->addWidget(graphicsView);
    setCentralWidget(centralWidget);
}

QWidget * MainWindow::GetCentralWidget()
{
    return centralWidget;
}

bool MainWindow::event(QEvent *event)
{
    return QMainWindow::event(event);
}

void MainWindow::Show()
{
    show();
}

MainWindow::~MainWindow()
{
    delete buttonMapper;
    delete buttonUp;
    delete buttonDown;
    delete zoomLabel;
    delete centralWidget;
    delete horizontalLayout;
    delete graphicsView;
}

void MainWindow::updateZoomLabel()
{
    ///const int percent = qRound(mapViewer->GetMapPicScale() * float(100));
    ///zoomLabel->setText(QString::number(percent) + QLatin1Char('%'));
}

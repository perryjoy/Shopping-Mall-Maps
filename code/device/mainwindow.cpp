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
    resize(1800, 1000);
    SetupUi(customGraphicsView);
}

void MainWindow::SetupUi(bool customGraphicsView)
{
    QFile file("MacOS.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    buttonMapper = new QSignalMapper();
    pathWidget = new path_widget(this);
    buttonUp = new QPushButton("", this);
    buttonDown = new QPushButton("", this);
    buttonUp->setStyleSheet(styleSheet + "QPushButton\
        {\
            image: url(:/based/UP.png);\
            border-style: outset;\
            background: transparent;\
            padding-top: 0px;\
            height: 50px;\
            width: 50px;\
        }\
    ");
    buttonDown->setStyleSheet(styleSheet + "QPushButton\
        {\
            image: url(:/based/UP.png);\
            border-style: outset;\
            background: transparent;\
            padding-top: 0px;\
            height: 50px;\
            width: 50px;\
        }\
    ");

    pathWidget->setGeometry(QRect(QPoint(this->size().width(), this->size().height() / 2 - 400),QSize(300, 300)));
    buttonUp->setGeometry(QRect(QPoint(this->size().width(), this->size().height() / 2 - 100),QSize(50, 50)));
    buttonDown->setGeometry(QRect(QPoint(this->size().width(), this->size().height() / 2 + 100),QSize(50, 50)));

    buttonMapper->setMapping(buttonUp, BUTTON_UP);
    buttonMapper->setMapping(buttonDown, BUTTON_DOWN);
    buttonMapper->setMapping(pathWidget, BUTTON_DRAW_PATH);

    connect(buttonUp, SIGNAL(released()), buttonMapper, SLOT(map()));
    connect(buttonDown, SIGNAL(released()), buttonMapper, SLOT(map()));
    connect(pathWidget, SIGNAL(ButtonPressed()), buttonMapper, SLOT(map()));

    connect(buttonMapper, &QSignalMapper::mappedInt, &manager, &manager::OnButton);

    centralWidget = new QWidget(this);
    horizontalLayout = new QHBoxLayout(centralWidget);

    verticalLayout = new QVBoxLayout(centralWidget);
    horizontalLayout->addLayout(verticalLayout);

    verticalLayout->addWidget(buttonUp);
    verticalLayout->addWidget(buttonDown);
    verticalLayout->addWidget(pathWidget);

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

void MainWindow::AddLabel(QString text, int x, int y)
{
    QLabel * l = new QLabel(centralWidget);
    l->setText(text);
    l->setGeometry(x, y, 100, 30);
    itemsLabels.push_back(l);
}

void MainWindow::ClearLabels()
{
    for (int i =  0; i < itemsLabels.size(); i++)
        delete itemsLabels[i];
    itemsLabels.clear();
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

path_widget * MainWindow::GetPathWidget()
{
    return pathWidget;
}

MainWindow::~MainWindow()
{
    ClearLabels();
    delete buttonMapper;
    delete buttonUp;
    delete buttonDown;
    delete zoomLabel;
    delete graphicsView;
    delete pathWidget;
    delete verticalLayout;
    delete horizontalLayout;
    delete centralWidget;
}

void MainWindow::updateZoomLabel()
{
    ///const int percent = qRound(mapViewer->GetMapPicScale() * float(100));
    ///zoomLabel->setText(QString::number(percent) + QLatin1Char('%'));
}

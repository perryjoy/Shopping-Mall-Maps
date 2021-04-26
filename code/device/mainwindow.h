#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "map.h"
#include "viewer.h"
#include "pathwidget.h"


class manager;

QT_BEGIN_NAMESPACE
class QGraphicsView;
class QSignalMapper;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QLabel;
QT_END_NAMESPACE

enum ui_button{
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LOAD,
    BUTTON_SET_PATH_START,
    BUTTON_SET_PATH_END,
    BUTTON_DRAW_PATH
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    MainWindow(manager &mgr, bool customGraphicsView = false);
    ~MainWindow();

    path_widget * GetPathWidget();
    QWidget * GetCentralWidget();

    void SetView(QGraphicsView * view);

    void Show();

public slots:
    bool event(QEvent *event) override;

private slots:
    void updateZoomLabel();

private:
    void SetupUi(bool customGraphicsView);

    QPushButton *buttonUp;
    QPushButton *buttonDown;
    QSignalMapper *buttonMapper;
    path_widget *pathWidget;

    QLabel *zoomLabel;

    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;

    manager &manager;
};

#endif

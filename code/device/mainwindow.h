#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class svg_view;
class map;

class main_window : public QWidget
{
    Q_OBJECT

public:
    main_window();
    ~main_window();
    virtual void Render(QPainter *painter);
    bool LoadFile(const QString &svgFileName, const QString &xmlFileName);

public slots:
    void Show();
    void setNewView(svg_view * toSet);

protected:
    bool event(QEvent *event) override;
    void timerEvent(QTimerEvent *) override;

private:
    int timerId;
    svg_view *view;
    map *mapInfo;
};
#endif // MAINWINDOW_H

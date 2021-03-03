#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWindow>

class main_window : public QWindow
{
    Q_OBJECT

public:
    main_window(QWindow *parent = nullptr);
    ~main_window();
    virtual void Render(QPainter *painter);

public slots:
    void RenderNow();

protected:
    bool event(QEvent *event) override;
    void timerEvent(QTimerEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;
private:
    QBackingStore *backingStore;
    int timerId;
};
#endif // MAINWINDOW_H

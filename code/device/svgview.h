#ifndef SVGVIEW_H
#define SVGVIEW_H

#include <QGraphicsView>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/qgraphicssvgitem.h>

class svg_view : public QGraphicsView
{
    Q_OBJECT

public:
    enum renderer_type
    {
        RENDERER_NATIVE,
        RENDERER_OPENGL,
        RENDERER_IMAGE
    };

    explicit svg_view(QWidget *parent = nullptr);

    bool OpenFile(const QString &fileName);
    void SetRenderer(renderer_type type = RENDERER_NATIVE);
    void drawBackground(QPainter *p, const QRectF &rect) override;

    QSize SvgSize() const;
    QSvgRenderer *Renderer() const;
    qreal zoomFactor();

public slots:
    void SetAntialiasing(bool antialiasing);
    void SetViewBackground(bool enable);
    void SetViewOutline(bool enable);


signals:
    //void zoomChanged();

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void zoomBy(qreal factor);

    renderer_type rendererType;

    QGraphicsSvgItem *svgItem;
    QGraphicsRectItem *backgroundItem;
    QGraphicsRectItem *outlineItem;
    QSvgRenderer *svgRenderer;
    QImage image;
};

#endif // SVGVIEW_H

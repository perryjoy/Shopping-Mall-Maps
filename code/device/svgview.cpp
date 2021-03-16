#include <QtSvg/QSvgRenderer>

#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QtSvg/QGraphicsSvgItem>
#include <QPaintEvent>
#include <qmath.h>

#ifndef QT_NO_OPENGL
#include <QtOpenGL/QGLWidget>
#endif

#include "svgview.h"

svg_view::svg_view(QWidget *parent) :
    QGraphicsView(parent),
    rendererType(RENDERER_IMAGE),
    svgItem(nullptr),
    backgroundItem(nullptr),
    outlineItem(nullptr)
{
    setScene(new QGraphicsScene(this));
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
    setViewportUpdateMode(FullViewportUpdate);
}

void svg_view::drawBackground(QPainter *p, const QRectF &)
{
    p->save();
    p->resetTransform();
    p->drawTiledPixmap(viewport()->rect(), backgroundBrush().texture());
    p->restore();
}

QSize svg_view::SvgSize() const
{
    return svgItem ? svgItem->boundingRect().size().toSize() : QSize();
}

bool svg_view::OpenFile(const QString &fileName)
{
    QGraphicsScene *s = scene();

    const bool drawBackground = (backgroundItem ? backgroundItem->isVisible() : false);
    const bool drawOutline = (outlineItem ? outlineItem->isVisible() : true);

    svgRenderer = new QSvgRenderer(fileName);
    QGraphicsSvgItem *black = new QGraphicsSvgItem();

    black->setSharedRenderer(svgRenderer);
    black->setElementId(QLatin1String("shop1_1"));


    //QScopedPointer<QGraphicsSvgItem> svgItem(new QGraphicsSvgItem(fileName));
    if (!svgRenderer->isValid())
    {
        return false;
    }

    s->clear();
    resetTransform();

    svgItem = black;//svgItem.take();
    svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
    svgItem->setCacheMode(QGraphicsItem::NoCache);
    svgItem->setZValue(0);

    backgroundItem = new QGraphicsRectItem(svgItem->boundingRect());
    backgroundItem->setBrush(Qt::white);
    backgroundItem->setPen(Qt::NoPen);
    backgroundItem->setVisible(drawBackground);
    backgroundItem->setZValue(-1);

    outlineItem = new QGraphicsRectItem(svgItem->boundingRect());
    QPen outline(Qt::black, 2, Qt::DashLine);
    outline.setCosmetic(true);
    outlineItem->setPen(outline);
    outlineItem->setBrush(Qt::NoBrush);
    outlineItem->setVisible(drawOutline);
    outlineItem->setZValue(1);

    s->addItem(backgroundItem);
    s->addItem(svgItem);
    s->addItem(outlineItem);

    s->setSceneRect(outlineItem->boundingRect().adjusted(-10, -10, 10, 10));
    return true;
}

void svg_view::SetRenderer(renderer_type type)
{
    rendererType = type;

#ifndef QT_NO_OPENGL
    if (rendererType == RENDERER_OPENGL)
    {
        setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    }
    else
#endif
    {
        setViewport(new QWidget);
    }
}

void svg_view::SetAntialiasing(bool antialiasing)
{
    setRenderHint(QPainter::Antialiasing, antialiasing);
}

void svg_view::SetViewBackground(bool enable)
{
    if (!backgroundItem)
    {
          return;
    }

    backgroundItem->setVisible(enable);
}

void svg_view::SetViewOutline(bool enable)
{
    if (!outlineItem)
    {
        return;
    }

    outlineItem->setVisible(enable);
}

void svg_view::paintEvent(QPaintEvent *event)
{
    if (rendererType == RENDERER_IMAGE)
    {
        if (image.size() != viewport()->size())
        {
            image = QImage(viewport()->size(), QImage::Format_ARGB32_Premultiplied);
        }

        QPainter imagePainter(&image);
        QGraphicsView::render(&imagePainter);
        imagePainter.end();

        QPainter p(viewport());
        p.drawImage(0, 0, image);
    }
    else
    {
        QGraphicsView::paintEvent(event);
    }
}

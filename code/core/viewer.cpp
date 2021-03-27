#include "device/viewer.h"


#ifndef QT_NO_OPENGL
#include <QtOpenGL/QGLWidget>
#endif

viewer::viewer(QWidget *parent) :
    QGraphicsView(parent),
    rendererType(RENDERER_IMAGE),
    svgItem(nullptr),
    backgroundItem(nullptr),
    outlineItem(nullptr)
{
    mapScene = new QGraphicsScene();
    setScene(mapScene);
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
    setViewportUpdateMode(FullViewportUpdate);
}

void viewer::paintEvent(QPaintEvent *event)
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

void viewer::drawBackground(QPainter *p, const QRectF &)
{
    p->save();
    p->resetTransform();
    p->drawTiledPixmap(viewport()->rect(), backgroundBrush().texture());
    p->restore();
}

void viewer::SetAntialiasing(bool antialiasing)
{
    setRenderHint(QPainter::Antialiasing, antialiasing);
}

void viewer::SetRenderer(renderer_type type)
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

bool viewer::InitMap(const QString &fileName)
{

    //mapPic = newMap;
    //if (!mapPic->renderer()->isValid())
        //return false;


    svgRenderer = new QSvgRenderer(fileName);
    QGraphicsSvgItem *black = new QGraphicsSvgItem();

    const bool drawBackground = (backgroundItem ? backgroundItem->isVisible() : false);
    const bool drawOutline = (outlineItem ? outlineItem->isVisible() : true);


     black->setSharedRenderer(svgRenderer);
     mapPic = black;
    //mapPic->setElementId(QLatin1String("shop1_1"));


    //QScopedPointer<QGraphicsSvgItem> svgItem(new QGraphicsSvgItem(fileName));

    mapScene->clear();
    resetTransform();

    mapPic->setFlags(QGraphicsItem::ItemClipsToShape);
    mapPic->setCacheMode(QGraphicsItem::NoCache);
    mapPic->setZValue(1);

    backgroundItem = new QGraphicsRectItem(mapPic->boundingRect());
    backgroundItem->setBrush(Qt::blue);
    backgroundItem->setPen(Qt::NoPen);
    backgroundItem->setVisible(drawBackground);
    backgroundItem->setZValue(-1);

    outlineItem = new QGraphicsRectItem(mapPic->boundingRect());
    QPen outline(Qt::black, 2, Qt::DashLine);
    outline.setCosmetic(true);
    outlineItem->setPen(outline);
    outlineItem->setBrush(Qt::NoBrush);
    outlineItem->setVisible(drawOutline);
    outlineItem->setZValue(1);

    mapScene->addItem(backgroundItem);
    mapScene->addItem(mapPic);
    mapScene->addItem(outlineItem);

    mapScene->setSceneRect(outlineItem->boundingRect().adjusted(-10, -10, 10, 10));
    return true;
}

void viewer::ClearMap()
{
    mapPic = nullptr;
}

void viewer::ViewMap()
{
    if(mapPic!=nullptr)
    {
        mapPic->show();
    }
}

void viewer::ViewObject()
{

}

void viewer::ViewGraph()
{

}

void viewer::ViewPath(coord *from, coord *to)
{

}

qreal viewer::GetMapPicScale()
{
    return mapPic->scale();
}

qreal viewer::zoomFactor()
{
    return transform().m11();
}

void viewer::wheelEvent(QWheelEvent *event)
{
    zoomBy(qPow(1.2, event->angleDelta().y() / 240.0));
}

void viewer::zoomBy(qreal factor)
{
    //const qreal currentZoom = zoomFactor();
    const qreal currentZoom = mapPic->scale();
    if ((factor < 1 && currentZoom < 0.1) || (factor > 1 && currentZoom > 10))
        return;
    //scale(factor, factor);
    mapPic->setScale(factor);
    emit zoomChanged();
}

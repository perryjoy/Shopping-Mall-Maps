#include "device/viewer.h"
#include "device/graph.h"
#include <QtSvg/QSvgRenderer>
#include <QtSvg/qgraphicssvgitem.h>
#include <QWheelEvent>
#include <QtMath>
#include <QGestureEvent>

#include <QDebug>

#ifndef QT_NO_OPENGL
#include <QtOpenGL/QGLWidget>
#endif

viewer::viewer(QWidget *parent) :
    QGraphicsView(parent),
    svgRenderer(nullptr),
    rendererType(RENDERER_IMAGE),
    svgItem(nullptr),
    backgroundItem(nullptr),
    outlineItem(nullptr),
    mapPic(nullptr)
{
    mapScene = new QGraphicsScene();
    setScene(mapScene);
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
    setViewportUpdateMode(FullViewportUpdate);
    setAttribute(Qt::WA_AcceptTouchEvents);
}

void viewer::paintEvent(QPaintEvent *event)
{

   if (rendererType == RENDERER_IMAGE)
    {
        if (image.size() != viewport()->size())
        {
            image = QImage(viewport()->size(), QImage::Format_ARGB32_Premultiplied);
        }

        QPainter p(viewport());
        QGraphicsView::render(&p);
        p.end();
        QGraphicsView::paintEvent(event);
        if (isPathNeeded)
        {
           //ViewPathFirst(0, 0);
        }
    }
    else
    {
        QGraphicsView::paintEvent(event);
    }
}

void viewer::AddUnstableVisible(QString id)
{
    QGraphicsSvgItem *newItem = new QGraphicsSvgItem();
    newItem->setSharedRenderer(svgRenderer);
    newItem->setElementId(id);

    newItem->setVisible(true);
    newItem->setZValue(1);
    QRectF bound = svgRenderer->boundsOnElement(id);
    newItem->setPos(bound.x(), bound.y());  // this code is must to set correct posisiton

    unstableVisibleItems[id] = newItem;
    mapScene->addItem(unstableVisibleItems[id]);
}

void viewer::ChangeVisibility(QString id, bool isVisible)
{
    if (unstableVisibleItems.find(id)!=unstableVisibleItems.end())
    {
        unstableVisibleItems[id]->setVisible(isVisible);
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
    qDebug() << "init";
    Clear();

    svgRenderer = new QSvgRenderer(fileName);
    mapPic = new QGraphicsSvgItem();
    mapPic->setSharedRenderer(svgRenderer);
    QRectF bound = svgRenderer->boundsOnElement("layer9");
    mapPic->setPos(bound.x(), bound.y());  // this code is must to set correct posisiton
    mapScene->clear();
    resetTransform();

    mapPic->setFlags(QGraphicsItem::ItemClipsToShape);
    mapPic->setCacheMode(QGraphicsItem::NoCache);
    mapPic->setZValue(-0.5);

    backgroundItem = new QGraphicsRectItem(mapPic->boundingRect());
    backgroundItem->setBrush(Qt::cyan);
    backgroundItem->setPen(Qt::NoPen);
    backgroundItem->setPos(bound.x(), bound.y());  // this code is must to set correct posisiton

    backgroundItem->setVisible(backgroundItem ? backgroundItem->isVisible() : false);
    backgroundItem->setZValue(-1);

    outlineItem = new QGraphicsRectItem(mapPic->boundingRect());
    QPen outline(Qt::black, 2, Qt::DashLine);
    outline.setCosmetic(true);
    outlineItem->setPen(outline);
    outlineItem->setBrush(Qt::NoBrush);
    outlineItem->setVisible(outlineItem ? outlineItem->isVisible() : true);
    outlineItem->setZValue(0);

    mapScene->addItem(backgroundItem);
    mapScene->addItem(mapPic);
//    mapScene->addItem(outlineItem);

    mapScene->setSceneRect(mapScene->itemsBoundingRect());


    setTransform(QTransform::fromScale(totalScaleFactor * 5,
                                       totalScaleFactor * 5));
    return true;
}

void viewer::Clear()
{
    if (svgRenderer)
        delete svgRenderer;
    if (backgroundItem)
        delete backgroundItem;
    if (outlineItem)
        delete outlineItem;
    if (mapPic)
        delete mapPic;
    for (auto & item : unstableVisibleItems)
        delete item.second;
}

viewer::~viewer()
{
    Clear();
    delete mapScene;
}

void viewer::ClearMap()
{
    if (mapPic)
        delete mapPic;

    mapPic = nullptr;
}

void viewer::ViewMap()
{
    if(mapPic != nullptr)
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

void viewer::ViewPathFirst(int start, int finish)
{
    graph w;
    QPen color(Qt::red);
    color.setWidth(5);

    std::vector<vertex_graph> path = w.SearchWay(start, finish);
    mapPic->setZValue(0);
    SetAntialiasing(1);

    for (int i = 0; i < path.size() - 1; ++i)
    {
        mapScene->addLine(path[i].vertexCoordinates.x, path[i].vertexCoordinates.y,
                          path[i + 1].vertexCoordinates.x, path[i + 1].vertexCoordinates.y, color);
    }
}

void viewer::ViewPathSecond(int finish)
{
    graph w;
    std::vector<vertex_graph> temperaryVertex;
    QPen color(Qt::red);
    color.setWidth(5);

    std::vector<vertex_graph> path = w.SearchWayAlternative(finish);
    mapPic->setZValue(0);
    SetAntialiasing(1);

    temperaryVertex = w.ReturnTemperaryVertexs();
    for (int i = 0; i < temperaryVertex.size() - 1; ++i)
    {
    mapScene->addLine(temperaryVertex[i].vertexCoordinates.x, temperaryVertex[i].vertexCoordinates.y,
                      temperaryVertex[i + 1].vertexCoordinates.x, temperaryVertex[i + 1].vertexCoordinates.y, color);
    }

    for (int i = 0; i < path.size() - 1; ++i)
    {
        mapScene->addLine(path[i].vertexCoordinates.x, path[i].vertexCoordinates.y,
                          path[i + 1].vertexCoordinates.x, path[i + 1].vertexCoordinates.y, color);
    }
}


float viewer::GetMapPicScale()
{
    return mapPic->scale();
}

float viewer::ZoomFactor()
{
    return transform().m11();
}

void viewer::wheelEvent(QWheelEvent *event)
{
    ZoomBy(qPow(1.2, event->angleDelta().y() / 240.0));      //Special for Arina and Yakov:
}                                                            //If we don't need scale with mouse wheel, delete
                                                             //functions wheelEvent, ZoomFactor, GetMapPicScale and ZoomBy.

void viewer::ZoomBy(float factor)
{
    //const qreal currentZoom = ZoomFactor();
    const float currentZoom = mapPic->scale();
    if ((factor < 1 && currentZoom < 0.1) || (factor > 1 && currentZoom > 10))
        return;
    scale(factor, factor);
    //mapPic->setScale(factor);
    emit ZoomChanged();
}


bool viewer::viewportEvent(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();

        if (touchPoints.count() == 2)
        {                                                       // determine scale factor
            const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
            const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();
            qreal currentScaleFactor =
                    QLineF(touchPoint0.pos(), touchPoint1.pos()).length()
                    / QLineF(touchPoint0.startPos(), touchPoint1.startPos()).length();

            if (touchEvent->touchPointStates() & Qt::TouchPointReleased)    // if one of the fingers is released, remember the current scale
            {                                                               // factor so that adding another finger later will continue zooming
                totalScaleFactor *= currentScaleFactor;                     // by adding new scale factor to the existing remembered value.
                currentScaleFactor = 1;
            }
            setTransform(QTransform::fromScale(totalScaleFactor * currentScaleFactor,
                                               totalScaleFactor * currentScaleFactor));
        }
        return true;
    }
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);
}

void viewer::ChangeBgrLayer(QString id)
{
    mapPic->setElementId(id);
}


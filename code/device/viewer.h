#ifndef VIEWER_H
#define VIEWER_H
#include <QGraphicsView>
#include <QGestureEvent>

#include "map.h"

class coord;
// class graph;

enum viewer_error_code
{
    VEC_SUCCESFULL,
    VEC_FAILED_TO_OPEN_FILE,
    VEC_ENTITY_CREATION_ERROR
};


class viewer: public QGraphicsView
{
    Q_OBJECT
    enum renderer_type
    {
        RENDERER_NATIVE,
        RENDERER_OPENGL,
        RENDERER_IMAGE
    };

 public:
    explicit viewer(QWidget *parent = nullptr);
    bool InitMap(const QString &fileName);       // Saving new map imame
    void ClearMap();                            // deleting img ptr

    void ViewMap();                             // Draws map
    void ViewObject();                          // Drows something (preparing for future) f.e. selected shop
    void ViewGraph();                           // Shows graph on map (for debug )
    void ViewPath();      // Shows path from firt point to second point (calls Graph)
    float ZoomFactor();
    float GetMapPicScale();
    void AddUnstableVisible(QString id);
    void ChangeVisibility(QString id, bool isVisible);
    void ChangeBgrLayer(QString id);
    void Clear();
    ~viewer();

signals:
    void ZoomChanged();


protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    bool viewportEvent(QEvent *event) override;

    void drawBackground(QPainter *p, const QRectF &) override;

private:
    void ZoomBy(float factor);
    void SetRenderer(renderer_type type = RENDERER_NATIVE);
    void SetAntialiasing(bool antialiasing);

    renderer_type rendererType;

    std::map<QString, QGraphicsSvgItem*> unstableVisibleItems;
    QGraphicsSvgItem *svgItem;
    QGraphicsRectItem *backgroundItem;
    QGraphicsRectItem *outlineItem;
    QSvgRenderer *svgRenderer;
    QGraphicsScene *mapScene;

    QGraphicsSvgItem* mapPic;
    //graph *path;
    QImage image;

    bool isPathNeeded = true;
    qreal totalScaleFactor = 1;
};

#endif // VIEWER_H

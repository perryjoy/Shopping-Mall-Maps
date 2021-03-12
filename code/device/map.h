#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QMap>

class svg_view;
class graph;
class shop_data;


#define __LEAVE_MAP_AS_IT_IS (QString(""))

enum map_error_code
{
    _MEC_DONE,
    _MEC_FAILED_TO_OPEN_FILE,
    _MEC_ENTITY_CREATION_ERROR
};


class map : public QObject // holds information about current map
{
    Q_OBJECT

private:
    QLatin1String svgMapFileName; // *.svg file to be drawn as map
    svg_view* pic; // svg picture loaded from file above
    graph* paths; // paths graph, based on svg pic

    QLatin1String mapInfoFileName; // *xml file, containing extra information for map objects
    QMap<QLatin1String, shop_data*> objects; // loaded and parsed extras data from file above



    // inner functions. im too lazy to incapsulate

    void ClearObjects();
    void ClearPic();
    void ClearGraph();
    void ClearAll();

    void OnChange(quint8 flags);

public:
    explicit map(QObject *parent = nullptr);
    ~map();

    shop_data const* ProvideData(QLatin1String id);
    bool Exists (QLatin1String id);

signals:
    // v = new svg pic ptr
    //NOTE: might be nullptr, check it!
    void MapPictureChanged(svg_view * v);

    // g = new graph ptr
    //NOTE: might be nullptr, check it!
    void PathGraphChanged(graph * g);

    // i = new info
    // NOTE: might be empty
    void MapInfoChanged(QMap<QLatin1String, shop_data*> const & i);

    public slots:
    // called on changing the mall to show
    // call with __LEAVE_MAP_AS_IT_IS instead of parameter you want to keep unchanged
    void SetAnotherMap(QString const & mapToSet, QString const & extrasToSet);

};

#endif // MAP_H

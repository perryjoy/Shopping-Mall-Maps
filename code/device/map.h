#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QMap>

class svg_view;
class shops_data;

class graph_alternative;




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
    graph_alternative* paths; // paths graph, based on svg pic

    QLatin1String mapInfoFileName; // *xml file, containing extra information for map objects
    shops_data* info; // loaded and parsed extras data from file above
    QMap<QLatin1String, quint32> object_indexes; // their indexes


    // inner functions. im too lazy to incapsulate

    void ClearObjects();
    void ClearPic();
    void ClearGraph();
    void ClearAll();

    void OnChange(quint8 flags);

public:
    explicit map(QObject *parent = nullptr);
    ~map();

    quint32 GetIndex(QLatin1String id);  //returns an ordinal number which is used to access info
    bool Exists (QLatin1String id); // checks if the object exists
    shops_data* GetInfo (void); // allows to acces extra info. DO NOT MODIFY THIS INFO. IT WILL HURT.

signals:
    // v = new svg pic ptr
    //NOTE: might be nullptr, check it!
    void MapPictureChanged(svg_view * view);

    // g = new graph ptr
    //NOTE: might be nullptr, check it!
    void PathGraphChanged(graph_alternative* graph);

    // i = new info
    // NOTE: might be empty
    void MapInfoChanged(shops_data const * const & info, QMap<QLatin1String, quint32> indexes);

    public slots:
    // called on changing the mall to show
    // call with __LEAVE_MAP_AS_IT_IS instead of parameter you want to keep unchanged
    void SetAnotherMap(QString const & mapToSet, QString const & extrasToSet);

};

#endif // MAP_H

#include "map.h"
#include "svgview.h"
//#include "graph.h"
#include "graph_alternative1.h"
#include "graph_parser.h"
#include "shops_data.h"

#define __MAP_PIC_CHANGED ((quint8)1)
#define __MAP_GRAPH_CHANGED ((quint8)2)
#define __MAP_INFO_CHANGED ((quint8)4)
#define __MAP_ALL_CHANGED ((__MAP_PIC_CHANGED)|(__MAP_GRAPH_CHANGED)|(__MAP_INFO_CHANGED))



shops_data* map::GetInfo (void)
{
    return info;
}


map::map(QObject *parent) :
    QObject(parent), svgMapFileName(""), pic(new svg_view), mapInfoFileName(""), object_indexes()
{
    //pic = nullptr;
    paths = nullptr;
}

map::~map()
{
    ClearAll();
    OnChange(__MAP_ALL_CHANGED);
}


quint32 map::GetIndex(QLatin1String name)
{
    return object_indexes[name];
}



void map::SetAnotherMap(QString const & mapToSet, QString const & extrasToSet)
{
    quint8 flags = 0;
    if (mapToSet != __LEAVE_MAP_AS_IT_IS && mapToSet != svgMapFileName)
    {
        flags |= __MAP_PIC_CHANGED;
        flags |= __MAP_GRAPH_CHANGED;
    }

    if (extrasToSet != __LEAVE_MAP_AS_IT_IS && extrasToSet != mapInfoFileName)
    {
        flags |= __MAP_INFO_CHANGED;
    }


    if ((flags & __MAP_PIC_CHANGED) != 0)
    {
        //ClearPic();
        pic->OpenFile(mapToSet);
    }

    if ((flags & __MAP_GRAPH_CHANGED) != 0)
    {
        ClearGraph();
        graph_parser gp(mapToSet);
        if (gp.proceedFile())
        {
            paths = gp.produceOtherGraph();
        }
    }
    if ((flags & __MAP_INFO_CHANGED) != 0)
    {
        ClearObjects();
        info = InitInfoFromFile (extrasToSet, object_indexes);
    }

    OnChange(flags);
}





void map::ClearObjects() // doesnt inform anyone. emit signals yourself!
{
    object_indexes.clear();

}
void map::ClearPic()  // doesnt inform anyone. emit signals yourself!
{
    delete pic;
    pic = nullptr;
}
void map::ClearGraph()  // doesnt inform anyone. emit signals yourself!
{
    delete paths;
    paths = nullptr;
}

void map::ClearAll()  // doesnt inform anyone. emit signals yourself!
{
    ClearPic();
    ClearGraph();
    ClearObjects();
}


void map::OnChange(quint8 singal_flags)
{
    if ((singal_flags & __MAP_PIC_CHANGED) != 0)
    {
        emit MapPictureChanged(pic);
    }
    if ((singal_flags & __MAP_GRAPH_CHANGED) != 0)
    {
        emit PathGraphChanged(paths);
    }
    if ((singal_flags & __MAP_INFO_CHANGED) != 0)
    {
        //emit MapInfoChanged(info, object_indexes);
    }
}

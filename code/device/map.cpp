#include "map.h"
#include "svgview.h"

#define __MAP_PIC_CHANGED ((quint8)1)
#define __MAP_GRAPH_CHANGED ((quint8)2)
#define __MAP_INFO_CHANGED ((quint8)4)
#define __MAP_ALL_CHANGED ((__MAP_PIC_CHANGED)|(__MAP_GRAPH_CHANGED)|(__MAP_INFO_CHANGED))



class shop_data //TODO: make an actual class and move to its personal file
{
    // DUMMY
};

class graph //TODO: link it properly when Misha is done
{
    // DUMMY
};

graph* CreateGraphFromSvg (svg_view* v)
{
    if (v == nullptr)
    {
        return nullptr;
    }
    return nullptr; // TDOD: write an actual creation when Misha is done
}

 void CreateInfoFromFile(QString const & file, QMap<QLatin1String, shop_data*>& info)
 {
     return; // TODO: write an actual function and move it to shop_data file
 }

map::map(QObject *parent) :
    pic(new svg_view), QObject(parent), svgMapFileName(""), mapInfoFileName(""), objects()
{
    //pic = nullptr;
    paths = nullptr;
}

map::~map()
{
    ClearAll();
    OnChange(__MAP_ALL_CHANGED);
}


shop_data const* map::ProvideData(QLatin1String id)
{
    return objects[id];
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
        paths = CreateGraphFromSvg (pic);
    }
    if ((flags & __MAP_INFO_CHANGED) != 0)
    {
        ClearObjects();
        CreateInfoFromFile (extrasToSet, objects);
    }

    OnChange(flags);
}





void map::ClearObjects() // doesnt inform anyone. emit signals yourself!
{
    for (auto& obj : objects)
    {
        delete obj;
        obj = nullptr;
    }
    objects.clear();
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
    if (singal_flags & __MAP_PIC_CHANGED != 0)
    {
        emit MapPictureChanged(pic);
    }
    if (singal_flags & __MAP_GRAPH_CHANGED != 0)
    {
        emit PathGraphChanged(paths);
    }
    if (singal_flags & __MAP_INFO_CHANGED != 0)
    {
        emit MapInfoChanged(objects);
    }
}

#include "device/viewer.h"
#include "device/svgview.h"


void viewer::InitMap(svg_view* newMap)
{
    mapPic = newMap;
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

void viewer::ViewPath(Coord *from, Coord *to)
{

}

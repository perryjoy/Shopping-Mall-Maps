#include "device/viewer.h"
#include "device/svgview.h"


void viewer::InitMap(svg_view* newMap)
{
    mapPic = newMap;
}

void viewer::ClearMap()
{
    mapPic = NULL;
}

void viewer::ViewMap()
{
    mapPic->show();
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

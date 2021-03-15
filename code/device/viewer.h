#ifndef VIEWER_H
#define VIEWER_H
#include "map.h"

class Coord; //Misha's
class Graph; //Misha's

enum viewer_error_code
{
    _VEC_SUCCESFULL,
    _VEC_FAILED_TO_OPEN_FILE,
    _VEC_ENTITY_CREATION_ERROR
};


class viewer
{
    svg_view* mapPic;
    Graph *path;
    void InitMap(svg_view* newMapPic);          // Saving new map imame
    void ClearMap();                            // deleting img ptr

    void ViewMap();                             // Draws map
    void ViewObject();                          // Drows something (preparing for future) f.e. selected shop
    void ViewGraph();                           // Shows graph on map (for debug )
    void ViewPath(Coord *from, Coord *to);      // Shows path from firt point to second point (calls Graph)



};












#endif // VIEWER_H

#ifndef VIEWER_H
#define VIEWER_H
#include "map.h"

class coord; //Misha's
// class graph; //Misha's

enum viewer_error_code
{
    VEC_SUCCESFULL,
    VEC_FAILED_TO_OPEN_FILE,
    VEC_ENTITY_CREATION_ERROR
};


class viewer
{
 public:
    void InitMap(svg_view* newMapPic);          // Saving new map imame
    void ClearMap();                            // deleting img ptr

    void ViewMap();                             // Draws map
    void ViewObject();                          // Drows something (preparing for future) f.e. selected shop
    void ViewGraph();                           // Shows graph on map (for debug )
    void ViewPath(coord *from, coord *to);      // Shows path from firt point to second point (calls Graph)
    
 private:
    svg_view* mapPic;
    graph_alternative* path;

};

#endif // VIEWER_H

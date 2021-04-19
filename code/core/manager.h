#ifndef MANAGER_H
#define MANAGER_H

#include <QString>

class map;
class path;
struct coord;

class manager
{
    map *currentMap;
    coord *start, *end;
    path *currentPath;

public:
    manager(void);
    ~manager(void);
    void Update(void);           // for main_window
    void OpenMap(QString name);  // for menu
    path * FindPath(void);       // for viewer to draw
    void SetStart(coord *start); // i dont sure this is nessesary
    void SetEnd(coord *end);     // this too
    const map & GetMap(void);    // and this
};

#endif // MANAGER_H

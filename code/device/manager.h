#ifndef MGR_H
#define MGR_H

#include "device/mainwindow.h"
#include "device/map.h"
#include "device/graph.h"

class viewer;

class manager : public QObject
{
    Q_OBJECT

    MainWindow window;
    map currentMap;
    viewer *mapViewer; //NOTE: ownership of viewer has window but manager can manage its creation and call its methods
    //vertex_graph start, end;
public:
    manager();

    void LoadData(const QString &svgFileName, const QString &xmlFileName);

    void Start() { window.Show(); }
public slots:
    void OnButton(int butttonPressed);
};

#endif // MGR_H

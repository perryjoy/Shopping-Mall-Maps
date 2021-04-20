#include <QFileInfo>
#include "device/viewer.h"
#include "device/manager.h"
#include "device/graph_alternative.h"

manager::manager() : window(*this, true), currentMap()
{
    mapViewer = new viewer(window.GetCentralWidget());
    window.SetView(mapViewer);
    connect(&currentMap, &map::PathGraphChanged, this, &manager::OnNewGraph);
    connect(&currentMap, &map::MapPictureDataChanged, this, &manager::OnNewMap);
}

void manager::OnButton(int butttonPressed)
{
    auto v= (*floorLayers)[2].GetPathsLr().GetObjects();
    switch (butttonPressed){
    case BUTTON_UP:
        for (auto id : v)
        {
            mapViewer->AddUnstableVisible(id);
        }
        break;
    case BUTTON_DOWN:
        for (auto id : v)
        {
            if (rand() % 2)
                 mapViewer->ChangeVisibility(id, false);
        }
        break;

    }
}

void manager::OnNewGraph(graph_alternative *newGraph)
{
    graph = newGraph;
}

void manager::OnNewMap(std::vector<floor_layer>* svgIds)
{
    floorLayers = svgIds;
}

void manager::LoadData(const QString &svgFileName, const QString &xmlFileName)
{
    if (QFileInfo::exists(svgFileName) && QFileInfo::exists(xmlFileName))
    {
        currentMap.SetAnotherMap(svgFileName, xmlFileName);
    }
    if (QFileInfo::exists(svgFileName))
    {
        mapViewer->InitMap(svgFileName);
    }
}

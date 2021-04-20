#include <QFileInfo>
#include "device/viewer.h"
#include "device/manager.h"
#include "device/graph_alternative.h"
#include "device/pathwidget.h"
#include "device/graph_alternative.h"

void manager::SetPath(path *p)
{
    activePath = p;
}

manager::manager() : window(*this, true), currentMap(), currentFloor(0)
{
    mapViewer = new viewer(window.GetCentralWidget());
    window.SetView(mapViewer);
    connect(&currentMap, &map::PathGraphChanged, this, &manager::OnNewGraph);
    connect(&currentMap, &map::MapPictureDataChanged, this, &manager::OnNewMap);
}

void manager::OnButton(int butttonPressed)
{
    std::vector<QString> ids;

    auto v = (*floorLayers)[2].GetPathsLr().GetObjects();
    switch (butttonPressed){
    case BUTTON_UP:
        if (currentFloor < floorLayers->size() - 1)
            currentFloor++;
        for (auto& id : v)
        {
            mapViewer->AddUnstableVisible(id);
        }
        break;
    case BUTTON_DOWN:
        for (auto& e : activePath->defaultEdges)
        {
            mapViewer->ChangeVisibility(e, true);
        }
        break;
    case BUTTON_DRAW_PATH:
        path_data pd = window.GetPathWidget()->GetData();
        vec start(pd.x1, pd.y1);
        vec end(pd.x2, pd.y2);
        graph->SetStart(start, quint32(pd.floor1)-1);
        graph->SetEnd(end, quint32(pd.floor2)-1);
        graph->FindPath();
        break;

    }
}

void manager::OnNewGraph(graph_alternative *newGraph)
{
    graph = newGraph;
    connect(graph, &graph_alternative::PathFound, this, &manager::SetPath);
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

#include <QFileInfo>
#include "device/viewer.h"
#include "device/manager.h"

manager::manager() : window(*this, true), currentMap()
{
    mapViewer = new viewer(window.GetCentralWidget());
    window.SetView(mapViewer);
}

void manager::OnButton(int butttonPressed)
{
    switch (butttonPressed){
    case BUTTON_UP:
        break;
    case BUTTON_SET_PATH_START:
        break;

    }
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

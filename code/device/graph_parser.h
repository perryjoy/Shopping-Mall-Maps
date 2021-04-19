#ifndef GRAPH_PARSER_H
#define GRAPH_PARSER_H

#include <QtXml/QDomDocument>
#include <QRegExp>

class graph;
class graph_alternative;


const QString __XY_COORDS_SEPARATOR = QString(",");

const QString __LAYER_TAG = QString("g");
const QString __LAYER_ATTRIBUTE_NAME = QString("groupmode"); // inkscape:groupmode
const QString __LAYER_ATTRIBUTE_VALUE = QString("layer");

const QString __LAYER_LABEL_ATTRIBUTE = QString("label"); //inkscape:label
const QRegExp __GRAPH_LAYER_LABEL_MASK = QRegExp("[0-9]+_paths");

const QString __ELEVATOR_TAG = QString("circle");
const QString __ELEVATOR_NAME_ATTRIBUTE = QString("id");
const QRegExp __ELEVATOR_NAME_MASK = QRegExp("[0-9]+_lift_[0-9]+");
const QString __ELEVATOR_X_COORDINATES_ATTRIBUTE = QString("cx");
const QString __ELEVATOR_Y_COORDINATES_ATTRIBUTE = QString("cy");

const QString __LADDER_TAG = QString("circle");
const QString __LADDER_NAME_ATTRIBUTE = QString("id");
const QRegExp __LADDER_NAME_MASK = QRegExp("[0-9]+_ladder_[0-9]+");
const QString __LADDER_X_COORDINATES_ATTRIBUTE = QString("cx");
const QString __LADDER_Y_COORDINATES_ATTRIBUTE = QString("cy");

const QString __EDGE_TAG = QString("path");
const QString __EDGE_NAME_ATTRIBUTE = QString("id");
const QString __EDGE_COORDINATES_ATTRIBUTE = QString("d");
enum polyline_attr
{
    PA_START = 0,
    PA_SHIFT_HORISONTAL,
    PA_SHIFT_VERTICAL
};
const QString __PATH_ATTRIBUTES[] = {"M", "H", "V"};


class graph_parser
{
    enum output_graph_type
    {
        EDGE_BASED,
        VERTEX_BASED
    };

    QString docName;
    QDomDocument doc;
    QDomNodeList edges;

    bool errorFlag;
    QString lastError;



public:
    graph_parser();
    graph_parser(QString fileName);
    bool loadFile (QString fileName);
    bool proceedFile ();
    graph* produceGraph();
    graph_alternative* produceOtherGraph();
    QString getLastError();



};

#endif // GRAPH_PARSER_H

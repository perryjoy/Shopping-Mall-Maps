#include "device/graph.h"
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>

void graph::WriteDataFromFile(const std::string &config)
{
    int index = 0;
    std::string line;
    std::ifstream file(config);
    file >> graphSize;
    adjacencyList = new vertex_graph[graphSize];
    while (!file.eof())
    {
        if (index < graphSize)
        {
            file >> adjacencyList[index].vertexCoordinates.x >> adjacencyList[index].vertexCoordinates.y
                 >> adjacencyList[index].vertexFloor;
            index++;
        }
        else
        {
            getline(file,line);
            if (!line.size() || line[0] == '-')
            {
                continue;
            }

            ++index;
            int number = 0;
            int ten = 1;
            for (int i = 0; i < line.length(); ++i)
            {
                number = number * ten + (line[i] - '0');
                ten *= 10;
                if (line[i + 1] == ' ' || i == line.length() - 1)
                {
                    adjacencyList[index - graphSize - 1].weightedEdges.push_back({number,
                    CalculateWeight(adjacencyList[index - graphSize - 1].vertexCoordinates, adjacencyList[number].vertexCoordinates)});
                    number = 0;
                    ten = 1;
                    ++i;
                }
            }
        }
    }

    file.close();
}

float graph::CalculateWeight(vec2 firstVertex, vec2 secondVertex)
{
    return sqrt((firstVertex.x - secondVertex.x) * (firstVertex.x - secondVertex.x) +
                (firstVertex.y - secondVertex.y) * (firstVertex.y - secondVertex.y));
}

void graph::AddVertex(vertex_graph vertex)
{
    temperaryVertexs.push_back(vertex);
}

vec2 graph::MethodKramer(const std::vector<float> & firstEquation, const std::vector<float> & secondEquation)
{
    vec2 newCoordinate;
    newCoordinate.x = (firstEquation[2] * secondEquation[1] - firstEquation[1] * secondEquation[2]) /
                      (firstEquation[0] * secondEquation[1] - firstEquation[1] * secondEquation[0]);
    newCoordinate.y = (firstEquation[0] * secondEquation[2] - firstEquation[2] * secondEquation[0]) /
                      (firstEquation[0] * secondEquation[1] - firstEquation[1] * secondEquation[0]);

    return newCoordinate;
}

std::vector<float> graph::CreateLineEquation(vertex_graph vert, int index)
{
    std::vector<float> lineEquation;
    lineEquation.push_back(-vert.vertexCoordinates.y + adjacencyList[index].vertexCoordinates.y);
    lineEquation.push_back(-adjacencyList[index].vertexCoordinates.x + vert.vertexCoordinates.x);
    lineEquation.push_back(vert.vertexCoordinates.x * adjacencyList[index].vertexCoordinates.y -
                           adjacencyList[index].vertexCoordinates.x * vert.vertexCoordinates.y);

    return lineEquation;
}

std::vector<float> graph::CreateNormalEquation(vertex_graph vert, int index, vec2 coordinates)
{
    std::vector<float> normalEquation;
    normalEquation.push_back(adjacencyList[index].vertexCoordinates.x - vert.vertexCoordinates.x);
    normalEquation.push_back(vert.vertexCoordinates.y - adjacencyList[index].vertexCoordinates.y);
    normalEquation.push_back(-vert.vertexCoordinates.x * coordinates.x + adjacencyList[index].vertexCoordinates.x * coordinates.x +
                             coordinates.y * vert.vertexCoordinates.y - adjacencyList[index].vertexCoordinates.y * coordinates.y);

    return normalEquation;
}

std::vector<edge> graph::CopyDataweightedEdges(vec2 newVertex, edge adjVert, int h)
{
    std::vector<edge> weightedEdges;
    weightedEdges.push_back({h,CalculateWeight(adjacencyList[h].vertexCoordinates, newVertex)});
    weightedEdges.push_back({adjVert.vertex_ID,CalculateWeight(adjacencyList[adjVert.vertex_ID].vertexCoordinates,newVertex)});

    return weightedEdges;
}

void graph::AddTemporaryVertex(vertex_graph vertex)
{
    vec2 newCoordinate;
    vertex_graph newVertex;
    float weight = 0;
    int index = 0;
    float minimalWeight = CalculateWeight(MethodKramer(CreateLineEquation(adjacencyList[0], adjacencyList[0].weightedEdges[0].vertex_ID),
                          CreateNormalEquation(adjacencyList[0], adjacencyList[0].weightedEdges[0].vertex_ID, vertex.vertexCoordinates)),
                          vertex.vertexCoordinates);
    for (int vert = 0; vert < graphSize; ++vert)
    {
        if (vertex.vertexFloor == adjacencyList[vert].vertexFloor)
        {
            for (auto & adjVert : adjacencyList[vert].weightedEdges)
            {
                if (std::max(adjacencyList[vert].vertexCoordinates.x, adjacencyList[adjVert.vertex_ID].vertexCoordinates.x) >=
                            vertex.vertexCoordinates.x &&
                   std::min(adjacencyList[vert].vertexCoordinates.x, adjacencyList[adjVert.vertex_ID].vertexCoordinates.x) <=
                            vertex.vertexCoordinates.x &&
                   std::max(adjacencyList[vert].vertexCoordinates.y, adjacencyList[adjVert.vertex_ID].vertexCoordinates.y) >=
                            vertex.vertexCoordinates.y &&
                   std::min(adjacencyList[vert].vertexCoordinates.y, adjacencyList[adjVert.vertex_ID].vertexCoordinates.y) <=
                            vertex.vertexCoordinates.y &&
                   adjacencyList[adjVert.vertex_ID].vertexFloor == vertex.vertexFloor)
            {
                    newCoordinate = MethodKramer(CreateLineEquation(adjacencyList[vert], adjVert.vertex_ID),
                                             CreateNormalEquation(adjacencyList[vert], adjVert.vertex_ID, vertex.vertexCoordinates));
                    weight = CalculateWeight(newCoordinate, vertex.vertexCoordinates);
                    if(minimalWeight > weight)
                    {
                        minimalWeight = weight;
                        newVertex.vertexCoordinates = newCoordinate;
                        newVertex.weightedEdges = CopyDataweightedEdges(newCoordinate, adjVert, index);
                        newVertex.vertexFloor = vertex.vertexFloor;
                        vertexOne = index;
                        vertexTwo = adjVert.vertex_ID;
                    }
                }
            }
        }
    }
    AddVertex(newVertex);
    AddVertex({{vertex.vertexCoordinates}, vertex.vertexFloor, {{0,CalculateWeight(vertex.vertexCoordinates, newVertex.vertexCoordinates)}}});
}

std::vector<vertex_graph> graph::SearchWay(int vertexStart, int vertexFinish)
{
    const int INF = INT_MAX;
    std::vector<vertex_graph> path;
    std::vector<int> minimalWay(graphSize, INF);
    std::vector<int> temporatyValue(graphSize);
    minimalWay[vertexStart] = 0;
    std::vector<bool> isVisited(graphSize);
    for (int i = 0; i < graphSize; ++i)
    {
        int unattainableValue = -1;
        for (int j = 0; j < graphSize; ++j)
        if (!isVisited[j] && (unattainableValue == -1 || minimalWay[j] < minimalWay[unattainableValue]))
        {
            unattainableValue = j;
        }

        if (minimalWay[unattainableValue] == INF)
        {
            break;
        }

        isVisited[unattainableValue] = true;

        for (size_t j = 0; j < adjacencyList[unattainableValue].weightedEdges.size(); ++j)
        {
            int to = adjacencyList[unattainableValue].weightedEdges[j].vertex_ID,
            weight = adjacencyList[unattainableValue].weightedEdges[j].weight;
            if (minimalWay[unattainableValue] + weight < minimalWay[to])
            {
                minimalWay[to] = minimalWay[unattainableValue] + weight;
                temporatyValue[to] = unattainableValue;
            }
        }
    }

    for (int i = vertexFinish; i != vertexStart; i = temporatyValue[i])
    {
        path.push_back(adjacencyList[i]);
    }

    path.push_back(adjacencyList[vertexStart]);
    reverse(path.begin(), path.end());

    return path;
}

std::vector<vertex_graph> graph::ReturnTemperaryVertexs()
{
    return temperaryVertexs;
}

void graph::DeleteTemperaryVertex()
{
    temperaryVertexs.clear();
}

std::vector<vertex_graph> graph::SearchWayAlternative(int vertexFinish)
{
    std::vector<vertex_graph> pathFirst;
    std::vector<vertex_graph> pathSecond;

    pathFirst = SearchWay(vertexOne, vertexFinish);
    pathSecond = SearchWay(vertexTwo, vertexFinish);

    if (pathFirst.size() > pathSecond.size())
    {
        return pathSecond;
    }
    else
    {
        return pathFirst;
    }
}

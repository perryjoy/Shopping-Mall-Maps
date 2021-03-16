#include "device\graf.h"

float graf::CalculateWeight(std::pair<float,float> firstVertex, std::pair<float,float> secondVertex)
{
    return sqrt((firstVertex.first - secondVertex.first) * (firstVertex.first - secondVertex.first) +
             (firstVertex.second - secondVertex.second) * (firstVertex.second - secondVertex.second));
}

void graf::AddVertex(vertex_graf vertex)
{
    adjacencyList.push_back(vertex);
    for(auto i : vertex.edgeWeight)
    {
        adjacencyList[i.first].edgeWeight.push_back({adjacencyList.size() - 1, i.second});
    }
}

void graf::DeleteVertex(int index)
{
    for(auto & i : adjacencyList)
    {
        int tmp = 0;
        for(auto & j : i.edgeWeight)
        {
            if(j.first == index)
            {
                i.edgeWeight.erase(i.edgeWeight.begin() + tmp);
                break;
            }
            tmp++;
        }
    }

    adjacencyList.erase(adjacencyList.begin() + index);
}

vertex_graf graf::SearchVertex(std::pair<float, float> coordinates)
{
    float minimalLenght = CalculateWeight(adjacencyList[0].vertexCoordinates, coordinates);
    float tmp = 0;
    vertex_graf vertexNearest = adjacencyList[0];
    for(auto & i : adjacencyList)
    {
        tmp = CalculateWeight(i.vertexCoordinates, coordinates);
        if(tmp < minimalLenght)
        {
            minimalLenght = tmp;
            vertexNearest = i;
        }
    }

    return vertexNearest;
}

int graf::SearchVertexInAdjacenct(std::pair<float, float> coordinates)
{
    int index = 0;
    for(auto & i : adjacencyList)
    {
        if(i.vertexCoordinates.first == coordinates.first && i.vertexCoordinates.second == coordinates.second)
        {
            break;
        }
        ++index;
    }

    return index;
}

void graf::AddTemporaryVertex(std::pair<float, float> coordinates)
{
    vertex_graf vertexNearestToFirst;
    vertex_graf vertexNearestToSecond;
    vertex_graf newVertex;
    vertexNearestToFirst = SearchVertex(coordinates);
    float minimalLenght = CalculateWeight(adjacencyList[vertexNearestToFirst.edgeWeight[0].first].vertexCoordinates, coordinates);
    float tmp = 0;
    vertexNearestToSecond = adjacencyList[vertexNearestToFirst.edgeWeight[0].first];
    for(auto & i : vertexNearestToFirst.edgeWeight)
    {
        tmp = CalculateWeight(adjacencyList[i.first].vertexCoordinates, coordinates);
        if(tmp < minimalLenght)
        {
            minimalLenght = tmp;
            vertexNearestToSecond = adjacencyList[i.first];
        }
    }

    newVertex.vertexCoordinates.first = (vertexNearestToFirst.vertexCoordinates.first + vertexNearestToSecond.vertexCoordinates.first)/2;
    newVertex.vertexCoordinates.second = (vertexNearestToFirst.vertexCoordinates.second + vertexNearestToSecond.vertexCoordinates.second)/2;
    newVertex.edgeWeight = {{SearchVertexInAdjacenct(vertexNearestToFirst.vertexCoordinates),
                             CalculateWeight(newVertex.vertexCoordinates, vertexNearestToFirst.vertexCoordinates)},
                            {SearchVertexInAdjacenct(vertexNearestToSecond.vertexCoordinates),
                             CalculateWeight(newVertex.vertexCoordinates, vertexNearestToSecond.vertexCoordinates)}};
    newVertex.vertexFloor = vertexNearestToFirst.vertexFloor;
    AddVertex(newVertex);
}

std::vector<std::vector<std::pair<int, float>>> graf::CopyAdjacencyList()
{
    std::vector<std::vector<std::pair<int, float>>> newList;
    for(auto & i : adjacencyList)
    {
        newList.push_back(i.edgeWeight);
    }

    return newList;
}

std::vector<int> graf::SearchWay(int vertexStart, int vertexFinish)
{
    const int INF = 2000000000;
    std::vector<int> path;
    std::vector<std::vector<std::pair<int, float>>> newGraf = CopyAdjacencyList();
    size_t grafSize = newGraf.size();
    std::vector<int> minimalWay (grafSize, INF);
    std::vector<int> temporatyValue (grafSize);
    minimalWay[vertexStart] = 0;
    std::vector<bool> isVisited (grafSize);
    for (size_t i=0; i < grafSize; ++i)
    {
        int unattainableValue = -1;
        for (size_t j = 0; j < grafSize; ++j)
        if (!isVisited[j] && (unattainableValue == -1 || minimalWay[j] < minimalWay[unattainableValue]))
        {
            unattainableValue = j;
        }

        if (minimalWay[unattainableValue] == INF)
        {
            break;
        }

        isVisited[unattainableValue] = true;

        for (size_t j = 0; j < newGraf[unattainableValue].size(); ++j)
        {
            int to = newGraf[unattainableValue][j].first,
            len = newGraf[unattainableValue][j].second;
            if (minimalWay[unattainableValue] + len < minimalWay[to])
            {
                minimalWay[to] = minimalWay[unattainableValue] + len;
                temporatyValue[to] = unattainableValue;
            }
        }
    }

    for (int i = vertexFinish; i != vertexStart; i = temporatyValue[i])
    {
        path.push_back(i);
    }

    path.push_back(vertexStart);
    reverse(path.begin(), path.end());

    for(auto & i : path)
        std::cout<<i<<"->"<<std::endl;

    return path;
}

#ifndef GRAF_H
#define GRAF_H

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

typedef struct vertex_graf
{
    std::pair<float, float> vertexCoordinates;
    int vertexFloor;
    std::vector<std::pair<int, float>> edgeWeight;
}vertex_graf;

class graf
{
public:
    std::vector<vertex_graf> adjacencyList;
    float CalculateWeight(std::pair<float, float> firstVertex, std::pair<float, float> secondVertex);
    void AddVertex(vertex_graf vertex);
    void DeleteVertex(int index);
    void AddTemporaryVertex(std::pair<float, float> coordinates);
    std::vector<int> SearchWay(int vertexStart, int vertexFinish);
private:
    vertex_graf SearchVertex(std::pair<float, float> coordinates);
    int SearchVertexInAdjacenct(std::pair<float, float> coordinates);
    std::vector<std::vector<std::pair<int, float>>> CopyAdjacencyList();
};

#endif // GRAF_H

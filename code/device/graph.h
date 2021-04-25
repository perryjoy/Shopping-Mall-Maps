#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

struct vec2
{
    float x; // x coordinate
    float y; // y coordinates
};

struct edge
{
    int vertex_ID; // index of adjacent vertex
    float weight;  // edge Weight
};

struct vertex_graph
{
    vec2 vertexCoordinates;
    int vertexFloor;
    std::vector<edge> weightedEdges;
};

class graph
{
public:
    void DeleteVertex(int index);
    void AddTemporaryVertex(vertex_graph vertex);
    void WriteDataFromFile(const std::string &config);
    void DeleteTemperaryVertex();
    std::vector<vertex_graph> SearchWay(int vertexStart, int vertexFinish);
    std::vector<vertex_graph> SearchWayAlternative(int vertexFinish);
    std::vector<vertex_graph> ReturnTemperaryVertexs();

    ~graph()
    {
        delete [] adjacencyList;
    }
private:
    void AddVertex(vertex_graph vertex);
    float CalculateWeight(vec2 firstVertex, vec2 secondVertex);
    vec2 MethodKramer(const std::vector<float> & firstEquation, const std::vector<float> & secondEquation);
    std::vector<edge> CopyDataweightedEdges(vec2 newVertex, edge adjVert, int h);
    std::vector<float> CreateLineEquation(vertex_graph vert, int index);
    std::vector<float> CreateNormalEquation(vertex_graph vert, int index, vec2 coordinates);

    std::vector<vertex_graph> temperaryVertexs;
    vertex_graph *adjacencyList;
    int graphSize;
    int vertexOne;
    int vertexTwo;
};

#endif // GRAPH_H

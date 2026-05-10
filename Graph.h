#pragma once
#include <vector>

struct IGraph
{

};
struct AdjacencyMatrix
{
    public:
    AdjacencyMatrix();
    AdjacencyMatrix(int SIZE);
    ~AdjacencyMatrix();
    void AddEdge(int x,int y,int weight);
    private:
    std::vector<std::vector<int>> Matrix; 
};
struct AdjacencyList
{
    std::vector<std::vector<int>> List; 
    AdjacencyList();
    AdjacencyList(int SIZE);
    ~AdjacencyList();
};
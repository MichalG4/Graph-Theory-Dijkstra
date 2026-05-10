#include <iostream>
#include <vector>
#include "Graph.h"
#include "Constants.h"
// to-do: 
// implement hash-map
// one directional edges
// error handling at connecting one point to self
AdjacencyMatrix::AdjacencyMatrix()
{
    Matrix=std::vector<std::vector<int>>(V, std::vector<int>(V,0));
}
AdjacencyMatrix::AdjacencyMatrix(int SIZE)
{
    Matrix=std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE,0));
}
AdjacencyMatrix::~AdjacencyMatrix(){}
void AdjacencyMatrix::AddEdge(int x,int y,int weight)
{
    if(x!=y)
    {
    Matrix[x][y]=weight;
    Matrix[y][x]=weight;   
    }
}
AdjacencyList::AdjacencyList()
{
    List=std::vector<std::vector<int>>(V, std::vector<int>(0,0));
}
AdjacencyList::AdjacencyList(int SIZE)
{
    List=std::vector<std::vector<int>>(SIZE, std::vector<int>(0,0));
}
AdjacencyList::~AdjacencyList(){}


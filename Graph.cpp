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
    Matrix=std::vector<std::vector<int>>(V, std::vector<int>(V,-1));
    size=V;
    edges=0;
}
AdjacencyMatrix::AdjacencyMatrix(int SIZE)
{
    Matrix=std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE,-1));
    size=SIZE;
    edges=0;
}
AdjacencyMatrix::~AdjacencyMatrix(){}
void AdjacencyMatrix::AddEdge(int x,int y,int weight)
{
    if(x!=y && x<size && y<size && Matrix[x][y]==-1)
    {
    Matrix[x][y]=weight;
    Matrix[y][x]=weight;   
    edges++;
    }
}

void AdjacencyMatrix::RemoveEdge(int x,int y)
{
    if(x<size && y<size)
    {
        Matrix[x][y]=-1;
        Matrix[y][x]=-1;
    }
}
void AdjacencyMatrix::CountDensity()
{
    density=edges/(size*(size-1));
}
float AdjacencyMatrix::GiveDensity()
{
    return density;
}
ListNode::ListNode(int WEIGHT,int VERTICE)
{
    weight=WEIGHT;
    vertice=VERTICE;
}
AdjacencyList::AdjacencyList()
{
    List=std::vector<std::vector<ListNode>>(V, std::vector<ListNode>(0));
    size=V;
    edges=0;
}
AdjacencyList::AdjacencyList(int SIZE)
{
    List=std::vector<std::vector<ListNode>>(SIZE, std::vector<ListNode>(0));
    size=SIZE;
    edges=0;
}
AdjacencyList::~AdjacencyList(){}
void AdjacencyList::AddEdge(int x,int y,int weight)
{
    if(x!=y && x<size && y<size) //checking if it is not present (-1) would be ineficient 
    {
        List[x].push_back(ListNode(weight,y));
        List[y].push_back(ListNode(weight,x));
    }
}
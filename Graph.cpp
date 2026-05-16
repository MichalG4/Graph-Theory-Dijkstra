#include <iostream>
#include <vector>
#include "Graph.h"
#include "Constants.h"
// to-do: 
// implement hash-map
// one directional edges
// error handling at connecting one point to self
// could sort list to make removing easier OR hash map
// add out of bounds for matrix
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
size_t AdjacencyMatrix::GetSize()
{
    return Matrix.size();
}
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
    if(x<size && y<size && x>-1)
    {
        Matrix[x][y]=-1;
        Matrix[y][x]=-1;
        edges--;
    }
}
void AdjacencyMatrix::CountDensity()
{
    density=(float)edges/((float)size*((float)size-1));
}
float AdjacencyMatrix::GetDensity()
{
    return density;
}
std::vector<int> AdjacencyMatrix::GetEdges(int y) //get a vector o edges assigned to specified vertice, maybe should return &?
{
    return Matrix[y];
}
int AdjacencyMatrix::GetSpecificEdge(int x,int y)
{
    return Matrix[x][y];
}
ListNode::ListNode() {}
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
        edges++;
    }
}
void AdjacencyList::RemoveEdge(int x,int y) // O(n)
{
    for(auto i=List[x].begin(); i!=List[x].end();i++)
    {
        if(i->vertice == y)
        {
            List[x].erase(i);
            break;
        }
    }
    for(auto i=List[y].begin(); i!=List[y].end();i++)
    {
        if(i->vertice == x)
        {
            List[y].erase(i);
            edges--;
            break;
        }
    }
}
void AdjacencyList::CountDensity()
{
    density=(float)edges/((float)size*((float)size-1));
}
float AdjacencyList::GetDensity()
{
    return density;
}
std::vector<ListNode> AdjacencyList::GetEdges(int y)//possibly shold return &
{
    return List[y];
}
size_t AdjacencyList::GetSize()
{
    return List.size();
}
int AdjacencyList::GetSpecificEdge(int x,int y)
{
    for(int i=0; i<(int)List[x].size();i++)
    {
        if(List[x][i].vertice==y)
        return (int)List[x][i].weight;
    }
    return -1;
}
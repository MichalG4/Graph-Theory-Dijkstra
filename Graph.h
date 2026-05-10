#pragma once
#include <vector>

struct IGraph
{
    public:
    virtual void AddEdge(int x,int y,int weight)=0;
    virtual void RemoveEdge(int x,int y)=0;
    virtual void CountDensity()=0;
    virtual float GiveDensity()=0;
    virtual ~IGraph() = default;
    protected:
    float density;
    int size; //number of vertices
    int edges;

};
struct AdjacencyMatrix:public IGraph
{
    public:
    AdjacencyMatrix();
    AdjacencyMatrix(int SIZE);
    ~AdjacencyMatrix();
    void AddEdge(int x,int y,int weight);
    void RemoveEdge(int x,int y);
    void CountDensity();
    float GiveDensity();
    private:
    std::vector<std::vector<int>> Matrix; 
};
struct ListNode
{
    public:
    int vertice;
    int weight;
    ListNode(int weight,int vertice);
};
struct AdjacencyList:public IGraph
{
    public:
    AdjacencyList();
    AdjacencyList(int SIZE);
    ~AdjacencyList();
    void AddEdge(int x,int y,int weight);
    void RemoveEdge(int x,int y);
    void CountDensity();
    float GiveDensity();
    private:
    std::vector<std::vector<ListNode>> List; 
};
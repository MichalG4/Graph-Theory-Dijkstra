#pragma once
#include <vector>

struct IGraph
{
    public:
    virtual void AddEdge(int x,int y,int weight)=0;
    virtual void RemoveEdge(int x,int y)=0;
    virtual void CountDensity()=0;
    virtual float GetDensity()=0;
    virtual ~IGraph() = default;
    virtual int GetSpecificEdge(int x,int y)=0;
    virtual size_t GetSize()=0;
    protected:
    float density;
    int size; //number of vertices i guess not needed as we have vector.size
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
    float GetDensity();
    int GetSpecificEdge(int x,int y);
    std::vector<int> GetEdges(int y);
    size_t GetSize();
    private:
    std::vector<std::vector<int>> Matrix; 
};
struct ListNode
{
    public:
    int vertice;
    int weight;
    ListNode();
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
    float GetDensity();
    int GetSpecificEdge(int x,int y);
    size_t GetSize();
    std::vector<ListNode> GetEdges(int y);
    private:
    std::vector<std::vector<ListNode>> List; 
};
#pragma once
#include <vector>
#include "Graph.h"
#include "MaxHeapPQ.h"

struct Dijkstra_node
{
    int vertice;
    int distance;
    bool is_explored;
    int last_node;

    Dijkstra_node(int v);
};

struct Dijkstra
{
    virtual ~Dijkstra() = default;

    virtual std::vector<int> PathTo(int source, int destination) = 0;
    virtual std::vector<std::vector<int>> PathToAll(int source) = 0;

protected:
    std::vector<Dijkstra_node> node_table;

    virtual void EnqueueDistances(int x) = 0;

    std::vector<int> PathReconstruct(int source, int destination);
};

struct Dijkstra_list : public Dijkstra
{
    Dijkstra_list();
    explicit Dijkstra_list(AdjacencyList &list);

    std::vector<int> PathTo(int source, int destination) override;
    std::vector<std::vector<int>> PathToAll(int source) override;

private:
    AdjacencyList *List;
    MAX_PQ min_pq;

    void EnqueueDistances(int x) override;
};

struct Dijkstra_matrix : public Dijkstra
{
    Dijkstra_matrix();
    explicit Dijkstra_matrix(AdjacencyMatrix &matrix);

    std::vector<int> PathTo(int source, int destination) override;
    std::vector<std::vector<int>> PathToAll(int source) override;

private:
    AdjacencyMatrix *Matrix;
    MAX_PQ min_pq;

    void EnqueueDistances(int x) override;
};
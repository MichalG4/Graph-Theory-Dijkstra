#include "Dijkstra.h"

Dijkstra_node::Dijkstra_node(int v) : vertice(v), distance(-1), is_explored(false), last_node(-1) {}

std::vector<int> Dijkstra::PathReconstruct(int source, int destination)
{
    std::vector<int> path;
    path.push_back(node_table[destination].distance);
    path.push_back(destination);
    while (node_table[destination].last_node != -1)
    {
        destination = node_table[destination].last_node;
        path.push_back(destination);
    }
    if (destination != source)
        path.push_back(source);
    return path;
}

Dijkstra_list::Dijkstra_list()
    : List(nullptr), min_pq() {}

Dijkstra_list::Dijkstra_list(AdjacencyList &list)
    : List(&list), min_pq()
{
    for (int i = 0; i < List->GetSize(); ++i)
        node_table.emplace_back(i);
}

std::vector<int> Dijkstra_list::PathTo(int source, int destination)
{
    node_table[source].distance = 0;
    node_table[source].is_explored = true;
    node_table[source].last_node = -1;
    min_pq.enqueue(0, source);

    while (min_pq.peek() != -1)
        EnqueueDistances(min_pq.dequeue());

    return PathReconstruct(source, destination);
}

std::vector<std::vector<int>> Dijkstra_list::PathToAll(int source)
{
    std::vector<std::vector<int>> answer;

    if (!node_table[source].is_explored)
        PathTo(source, List->GetSize() - 1);

    for (int i = 0; i < List->GetSize(); ++i)
    {
        if (i == source)
            answer.push_back(std::vector<int>(2, -1));
        else
            answer.push_back(PathReconstruct(source, i));
    }
    return answer;
}

void Dijkstra_list::EnqueueDistances(int x)
{
    if (node_table[x].is_explored)
        return;

    for (ListNode &neighbor : List->GetEdges(x))
    {
        int i = neighbor.vertice;
        int weight = neighbor.weight;

        if (!node_table[i].is_explored)
        {
            int newDist = node_table[x].distance + weight;
            if (node_table[i].distance == -1 || newDist < node_table[i].distance)
            {
                node_table[i].distance = newDist;
                node_table[i].last_node = x;
                min_pq.enqueue(-node_table[i].distance, i);
            }
        }
    }
    node_table[x].is_explored = true;
}

Dijkstra_matrix::Dijkstra_matrix()
    : Matrix(nullptr), min_pq() {}

Dijkstra_matrix::Dijkstra_matrix(AdjacencyMatrix &matrix)
    : Matrix(&matrix), min_pq()
{
    for (int i = 0; i < Matrix->GetSize(); ++i)
        node_table.emplace_back(i);
}

std::vector<int> Dijkstra_matrix::PathTo(int source, int destination)
{
    node_table[source].distance = 0;
    node_table[source].is_explored = true;
    node_table[source].last_node = -1;
    min_pq.enqueue(0, source);

    while (min_pq.peek() != -1)
        EnqueueDistances(min_pq.dequeue());

    return PathReconstruct(source, destination);
}

std::vector<std::vector<int>> Dijkstra_matrix::PathToAll(int source)
{
    std::vector<std::vector<int>> answer;

    if (!node_table[source].is_explored)
        PathTo(source, Matrix->GetSize() - 1);

    for (int i = 0; i < Matrix->GetSize(); ++i)
    {
        if (i == source)
            answer.push_back(std::vector<int>(2, -1));
        else
            answer.push_back(PathReconstruct(source, i));
    }
    return answer;
}

void Dijkstra_matrix::EnqueueDistances(int x)
{
    if (node_table[x].is_explored)
        return;

    for (int i = 0; i < Matrix->GetSize(); ++i)
    {
        int edgeWeight = Matrix->GetSpecificEdge(x, i);
        if (!node_table[i].is_explored && edgeWeight > -1)
        {
            int newDist = node_table[x].distance + edgeWeight;
            if (node_table[i].distance == -1 || newDist < node_table[i].distance)
            {
                node_table[i].distance = newDist;
                node_table[i].last_node = x;
                min_pq.enqueue(-node_table[i].distance, i);
            }
        }
    }
    node_table[x].is_explored = true;
}
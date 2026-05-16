#include <iostream>
#include "Graph.h"
#include "MaxHeapPQ.h"
#include "Constants.h"
//we assume no negative weight edges and no disconnected vertices
struct Dijkstra_node
{
    int vertice;
    int distance;
    bool is_explored;
    int last_node;
    Dijkstra_node(int v) : vertice(v), distance(-1), is_explored(false), last_node(-1) {} //instead of -1 distance, could give constant "Dijkstra infnity"
};
struct Dijkstra
{
    
};
struct Dijkstra_list
{
    AdjacencyList* List;
    MAX_PQ min_pq;
    std::vector<Dijkstra_node> node_table;

    Dijkstra_list() : List(), min_pq() {}

    Dijkstra_list(AdjacencyList &list) : List(&list), min_pq()
    {
        for (int i = 0; i < List->GetSize(); ++i)
            node_table.emplace_back(i);
    }

    std::vector<int> PathTo(int source, int destination)
    {
        node_table[source].distance = 0;
        node_table[source].is_explored = true;
        node_table[source].last_node = -1;
        min_pq.enqueue(0, source);
        while (min_pq.peek() != -1)
        {
            EnqueueDistances(min_pq.dequeue());
        }
        std::vector<int> answer = PathReconstruct(source, destination);
        return answer;
    }

    std::vector<std::vector<int>> PathToAll(int source)
    {
        std::vector<std::vector<int>> answer;
        if (node_table[source].is_explored == false) PathTo(source, List->GetSize() - 1);
        for (int i = 0; i < List->GetSize(); ++i)
        {
            if (i == source) answer.push_back(std::vector<int>(2, -1));
            else answer.push_back(PathReconstruct(source, i));
        }
        return answer;
    }

    private:
    std::vector<int> PathReconstruct(int source, int destination)
    {
        std::vector<int> path;
        path.push_back(node_table[destination].distance);
        path.push_back(destination);
        while (node_table[destination].last_node != -1)
        {
            destination = node_table[destination].last_node;
            path.push_back(destination);
        }
        if (destination != source) path.push_back(source);
        return path;
    }

    void EnqueueDistances(int x)
    {
        if (node_table[x].is_explored == true) return;
        // key difference: iterate over neighbors directly instead of all vertices
        for (ListNode& neighbor : List->GetEdges(x))
        {
            int i = neighbor.vertice;
            int weight = neighbor.weight;
            if (!node_table[i].is_explored)
            {
                if ((node_table[i].distance == -1) || (node_table[x].distance + weight) < node_table[i].distance)
                {
                    node_table[i].distance = node_table[x].distance + weight;
                    node_table[i].last_node = x;
                    min_pq.enqueue(-node_table[i].distance, i);
                }
            }
        }
        node_table[x].is_explored = true;
    }
};
struct Dijkstra_matrix
{
    AdjacencyMatrix* Matrix;
    MAX_PQ min_pq; //have to reverse pq since the implemented one is max pq;
    std::vector<Dijkstra_node> node_table;
    Dijkstra_matrix() : Matrix(), min_pq() 
    {
    }
    Dijkstra_matrix(AdjacencyMatrix &matrix) : Matrix(&matrix),min_pq()
    {
        for (int i = 0; i < Matrix->GetSize(); ++i)
        node_table.emplace_back(i);
    }
    std::vector<int> PathTo(int source,int destination) //no protection from using it twice - and it will give wrong paths, easily fixable but for demonstation purposes will stay as is
    {
        node_table[source].distance=0;
        node_table[source].is_explored=true;
        node_table[source].last_node=-1;
        min_pq.enqueue(0,source);
        while ((min_pq.peek())!=-1)
        {
            EnqueueDistances(min_pq.dequeue());
        }
        //path reconstruction
        std::vector<int> answer=PathReconstruct(source,destination);
        return answer;
    }

    std::vector<std::vector<int>> PathToAll(int source)
    {
        std::vector<std::vector<int>> answer;
        if(node_table[source].is_explored==false) PathTo(source,Matrix->GetSize()-1);
        for (int i = 0; i < Matrix->GetSize(); ++i)
        {
            if(i==source) answer.push_back(std::vector<int>(2,-1));
            else
            {
                answer.push_back(PathReconstruct(source,i));
            }
        }
        return answer;
    }
    private:
    std::vector<int> PathReconstruct(int source,int destination)//at the end gives distance
    {
        std::vector<int> path;
        path.push_back(node_table[destination].distance);
        path.push_back(destination);
        while(node_table[destination].last_node!=-1)
        {
            destination=node_table[destination].last_node;
            path.push_back(destination);
        }
        if(destination!=source)path.push_back(source);
        return path;
    }
    void EnqueueDistances(int x) 
    {
        if(node_table[x].is_explored==true) return; //skip left out entries
        for(int i=0;i<Matrix->GetSize();i++)
        {
            if(!node_table[i].is_explored && Matrix->GetSpecificEdge(x,i)>-1/*if it exists*/)
                {
                    if((node_table[i].distance==-1 || (node_table[x].distance+Matrix->GetSpecificEdge(x,i))<node_table[i].distance))
                    {
                        node_table[i].distance=(node_table[x].distance+Matrix->GetSpecificEdge(x,i));
                        node_table[i].last_node=x;
                        min_pq.enqueue(-node_table[i].distance,i);
                    }
                }
        }
        node_table[x].is_explored=true;
    }

    
};
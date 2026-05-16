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
    
};
struct Dijkstra_matrix
{
    AdjacencyMatrix* Matrix;
    MAX_PQ min_pq; //have to reverse pq since the implemented one is max pq;
    std::vector<Dijkstra_node> node_table;
    std::vector<int> path;
    
    Dijkstra_matrix() : Matrix(), min_pq() 
    {
    }
    Dijkstra_matrix(AdjacencyMatrix &matrix) : Matrix(&matrix),min_pq(),explored_count(0)
    {
        for (int i = 0; i < Matrix->GetSize(); ++i)
        node_table.emplace_back(i);
    }
    std::vector<int> PathTo(int source,int destination)
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
        std::vector<int> answer;
        answer.push_back(node_table[destination].distance);
        answer.push_back(destination);
        while(node_table[destination].last_node!=-1)
        {
            destination=node_table[destination].last_node;
            answer.push_back(destination);
        }
        answer.push_back(source);
        return answer;
    }
    private:
    void EnqueueDistances(int x) 
    {
        if(node_table[x].is_explored==true) return; //skip left out entries
        for(int i=0;i<Matrix->GetSize();i++)
        {
            if(!node_table[i].is_explored && Matrix->GetSpecificEdge(x,i)>-1/*if it exists*/)
                {
                    if((node_table[i].distance==-1 || node_table[x].distance+Matrix->GetSpecificEdge(x,i))<node_table[i].distance)
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
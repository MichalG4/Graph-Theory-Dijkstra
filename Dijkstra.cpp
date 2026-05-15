#include <iostream>
#include "Graph.h"
#include "MaxHeapPQ.h"
#include "Constants.h"

struct Dijkstra
{
    
};
struct Dijkstra_list
{
    
};
struct Dijkstra_matrix
{
    AdjacencyMatrix Matrix;
    MAX_PQ min_pq; //have to reverse pq since the implemented one is max pq;
    int Node;
    int distance;
    bool is_explored;
    int last_node;
    Dijkstra_matrix() : Matrix(), min_pq() 
    {
    }
    Dijkstra_matrix(AdjacencyMatrix matrix) : min_pq()
    {
        Matrix=matrix;
    }
    
};
#include <iostream>
#include <cmath>
const int V = 100; // number of vertices
// to-do: implement hash-map

struct heap_max_priority_queue
{
    int *table;
    int size;
    heap_max_priority_queue()
    {
        table = new int[V];
        size = 0;
    }
    heap_max_priority_queue(int SIZE)
    {
        table = new int[SIZE];
        size = 0;
    }
    ~heap_max_priority_queue()
    {
        delete[] table;
    }
    int left_node(int index)
    {
        return ((2 * index) + 1);
    }
    int right_node(int index)
    {
        return ((2 * index) + 2);
    }
    int parent_node(int index)
    {
        return (index) >= 0 ? floor((index - 1) / 2) : 0;
    }
    void swap(int a, int b)
    {
        int temp = table[a];
        table[a] = table[b];
        table[b] = temp;
    }
    void heap_up(int index)
    {
        int parent_index = parent_node(index);
        if (index == 0)
            return;
        else if (table[parent_index] < table[index])
        {
            swap(parent_index, index);
            heap_up(parent_index);
        }
    }
    void heap_down(int index)
    {
        int max_child; // max child's index
        max_child = table[left_node(index)] > table[right_node(index)] ? left_node(index) : right_node(index);
        if (table[max_child] > table[index])
        {
            swap(index, max_child);   
            heap_down(max_child);         
        }
    }
    void insert(int element)
    {
        table[size] = element;
        heap_up(size);
        size++;
    }
    int peek()
    {
        return table[0];
    }
    void delete_max()
};
typedef struct heap_max_priority_queue MAX_PQ;
int main()
{

    return 0;
}

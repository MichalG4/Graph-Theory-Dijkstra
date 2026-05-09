#include <iostream>
#include <cmath>
const int V = 100; // number of vertices
// to-do: 
// implement hash-map
// error_handler for peek(),dequeure() and delete_max()

struct binary_heap_max_priority_queue
{
    int *table;
    int size;
    binary_heap_max_priority_queue()
    {
        table = new int[V];
        size = 0;
    }
    binary_heap_max_priority_queue(int SIZE)
    {
        table = new int[SIZE];
        size = 0;
    }
    ~binary_heap_max_priority_queue()
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
        return index >= 0 ? floor((index - 1) / 2) : 0; //floor() for readability 
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
        int max_child = 0;  // max child's index
        if (right_node(index) < size)                                                                              // Find max child
            max_child = table[left_node(index)] > table[right_node(index)] ? left_node(index) : right_node(index); // Find max child
        else if (left_node(index) < size)                                                                          // Find max child
            max_child = left_node(index);                                                                   // Find max child
        else
            return;
        if ((max_child > 0) && (table[max_child] > table[index]))
        {
            swap(index, max_child);
            heap_down(max_child);
        }
    }
    void enqueue(int element)
    {
        table[size] = element;
        heap_up(size);
        size++;
    }
    int dequeue()
    {
        if (size == 0) return -1;
        swap(0,--size);
        heap_down(0);
        return table[size];
    }
    int peek()
    {
        if (size == 0) return -1;
        return table[0];
    }
    void delete_max()
    {
        if (size == 0) return;
        swap(0,--size);
        heap_down(0);
    }

};
typedef struct binary_heap_max_priority_queue MAX_PQ;
int main()
{

    return 0;
}

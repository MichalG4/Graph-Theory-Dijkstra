#include <iostream>
#include <cmath>
#include "MaxHeapPQ.h"
#include "Constants.h"
// to-do:
// error_handler for peek(),dequeure() and delete_max()

int binary_heap_max_priority_queue::left_node(int index)
{
    return ((2 * index) + 1);
}

int binary_heap_max_priority_queue::right_node(int index)
{
    return ((2 * index) + 2);
}

int binary_heap_max_priority_queue::parent_node(int index)
{
    return index >= 0 ? floor((index - 1) / 2) : 0; //floor() for readability 
}

void binary_heap_max_priority_queue::swap(int a, int b)
{
    PQElement temp = table[a];
    table[a] = table[b];
    table[b] = temp;
}

void binary_heap_max_priority_queue::heap_up(int index)
{
    int parent_index = parent_node(index);
    if (index == 0)
        return;
    else if (table[parent_index].priority < table[index].priority)
    {
        swap(parent_index, index);
        heap_up(parent_index);
    }
}

void binary_heap_max_priority_queue::heap_down(int index)
{
    int max_child = 0;  // max child's index
    if (right_node(index) < size)                                                                              // Find max child
        max_child = table[left_node(index)].priority > table[right_node(index)].priority ? left_node(index) : right_node(index); // Find max child
    else if (left_node(index) < size)                                                                          // Find max child
        max_child = left_node(index);                                                                   // Find max child
    else
        return;
    if ((max_child > 0) && (table[max_child].priority > table[index].priority))
    {
        swap(index, max_child);
        heap_down(max_child);
    }
}

binary_heap_max_priority_queue::binary_heap_max_priority_queue()
{
    table = new PQElement[V*V];
    size = 0;
}

binary_heap_max_priority_queue::binary_heap_max_priority_queue(int SIZE)
{
    table = new PQElement[SIZE*SIZE];
    size = 0;
}

binary_heap_max_priority_queue::~binary_heap_max_priority_queue()
{
    delete[] table;
}

void binary_heap_max_priority_queue::enqueue(int priority, int vertice)
{
    table[size] = {priority, vertice};
    heap_up(size);
    size++;
}

int binary_heap_max_priority_queue::dequeue() //vertice with highest priority
{
    if (size == 0) return -1;
    swap(0, --size);
    heap_down(0);
    return table[size].vertice;
}

int binary_heap_max_priority_queue::peek()
{
    if (size == 0) return -1;
    return table[0].vertice;
}

void binary_heap_max_priority_queue::delete_max()
{
    if (size == 0) return;
    swap(0, --size);
    heap_down(0);
}
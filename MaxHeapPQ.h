#pragma once

struct PQElement {
    int priority;
    int vertice;
};
struct binary_heap_max_priority_queue : PQElement
{
    private:
    PQElement *table;
    int size;
    int left_node(int index);
    int right_node(int index);
    int parent_node(int index);
    void swap(int a, int b);
    void heap_up(int index);
    void heap_down(int index);
    public:
    binary_heap_max_priority_queue();
    binary_heap_max_priority_queue(int SIZE);
    ~binary_heap_max_priority_queue();
    void enqueue(int priority, int vertice);
    int dequeue();
    int peek();
    void delete_max();
};
typedef binary_heap_max_priority_queue MAX_PQ;
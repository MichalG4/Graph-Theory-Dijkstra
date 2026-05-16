# Graph & Dijkstra's Shortest Path

A C++ implementation of weighted undirected graphs with Dijkstra's shortest-path algorithm, supporting both adjacency list and adjacency matrix representations.

---

## Overview

This project provides two graph representations and a Dijkstra implementation that works with either. It is built from scratch using a custom binary max-heap priority queue.

```
Graph (IGraph)
├── AdjacencyMatrix   — O(1) edge lookup, O(V²) space
└── AdjacencyList     — O(degree) edge lookup, O(V + E) space

Dijkstra
├── Dijkstra_matrix   — uses AdjacencyMatrix
└── Dijkstra_list     — uses AdjacencyList

MAX_PQ (binary_heap_max_priority_queue)
└── used internally by both Dijkstra variants
```

---

## Files

| File | Description |
|---|---|
| `Constants.h` | Global constant `V` (default graph size) |
| `Graph.h / .cpp` | `AdjacencyMatrix` and `AdjacencyList` implementations |
| `Dijkstra.h / .cpp` | Dijkstra's algorithm for both graph types |
| `MaxHeapPQ.h / .cpp` | Binary max-heap priority queue |

---

## Usage

### Building a graph

```cpp
// Adjacency list (recommended for sparse graphs)
AdjacencyList graph(6);
graph.AddEdge(0, 1, 4);
graph.AddEdge(0, 2, 1);
graph.AddEdge(2, 1, 2);
graph.AddEdge(1, 3, 1);
graph.AddEdge(2, 3, 5);

// Adjacency matrix (recommended for dense graphs)
AdjacencyMatrix matrix(6);
matrix.AddEdge(0, 1, 4);
matrix.AddEdge(0, 2, 1);
```

### Finding the shortest path

```cpp
Dijkstra_list dijkstra(graph);

// Single destination — returns [distance, ...vertices in reverse order]
std::vector<int> path = dijkstra.PathTo(0, 3);

// All destinations from source
std::vector<std::vector<int>> all = dijkstra.PathToAll(0);
```

### Reading the result

`PathTo` returns a vector where `path[0]` is the **total distance** and the remaining elements are the **vertices in reverse order** (destination → source).

```cpp
// Example result: path = {4, 3, 1, 2, 0}
// Shortest path:  0 → 2 → 1 → 3  (distance 4)
int distance = path[0];
// Vertices: path[1] = destination, path.back() = source
```

### Priority queue (standalone)

```cpp
MAX_PQ pq(50);
pq.enqueue(10, 0);   // priority 10, vertex 0
pq.enqueue(3,  1);   // priority 3,  vertex 1
int top = pq.peek();      // returns vertex 0 (highest priority)
int v   = pq.dequeue();   // removes and returns vertex 0
```

---

## Complexity

| Operation | AdjacencyList | AdjacencyMatrix |
|---|---|---|
| `AddEdge` | O(1) | O(1) |
| `RemoveEdge` | O(degree) | O(1) |
| `GetEdges` | O(1) | O(1) |
| `GetSpecificEdge` | O(degree) | O(1) |
| Space | O(V + E) | O(V²) |

| Dijkstra operation | Complexity |
|---|---|
| `PathTo` | O((V + E) log V) |
| `PathToAll` | O((V + E) log V) — single run, all paths reconstructed |

The priority queue uses a **lazy deletion** strategy: outdated entries are left in the heap and skipped when dequeued. This means the heap can hold up to O(E) entries rather than O(V).

---

## Design Notes

**Two graph representations** serve different use cases. The adjacency matrix offers O(1) `GetSpecificEdge` at the cost of O(V²) memory — suitable for dense graphs. The adjacency list is more memory-efficient for sparse graphs, with edge lookup proportional to the vertex degree.

**The priority queue is a max-heap used as a min-heap** by negating priorities on enqueue (`-distance`). Dijkstra requires a min-priority queue; rather than implementing a separate structure, distances are stored as negatives so the largest value at the top always corresponds to the smallest actual distance.

**Lazy deletion** means that when a shorter path to a node is found, a new entry is pushed rather than updating the existing one. Stale entries are detected and skipped in `EnqueueDistances` via the `is_explored` flag.

**`PathReconstruct`** traces back through the `last_node` chain stored during relaxation. The first element of the returned vector is the total distance, followed by vertices from destination to source.

**Distance sentinel:** Unvisited nodes are initialised with distance `-1` rather than a conventional infinity constant. This is a recognised trade-off — a named `DIJKSTRA_INF` constant would make intent clearer, but `-1` is unambiguous given the non-negative weight assumption.

---

## Assumptions & Limitations

- **Non-negative edge weights only.** The algorithm is Dijkstra's; negative weights require Bellman-Ford.
- **Connected graph.** All vertices are assumed to be reachable from the source. Unreachable vertices will retain distance `-1` in the result.
- **Single-use per instance.** A `Dijkstra` object should not be reused after `PathTo` or `PathToAll` has been called — the internal `node_table` is not reset between runs. This is intentional for this demonstration; a `Reset()` method would be a straightforward addition.
- **Default graph size** is 100.
- **Undirected edges only.** `AddEdge(x, y, w)` always creates both directions.
- **No duplicate edge detection** in `AdjacencyList::AddEdge`.

---

## Possible Extensions

- `Reset()` method on `Dijkstra` to allow reuse with a different source
- Directed edge support (`AddDirectedEdge`)
- Named infinity constant (`DIJKSTRA_INF`) instead of `-1` sentinel
- Negative-weight support via Bellman-Ford
- `decrease-key` in the priority queue for cleaner O((V + E) log V) without lazy deletion
- Hash map backing for the adjacency list for faster edge lookup and removal
- Out-of-bounds guards on matrix indexing

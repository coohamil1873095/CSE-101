//-----------------------------------------------------------------------------
//  Connor Hamilton 
//  coohamil 
//  2023 Fall PA3
//  Graph.h
//  Header file for Graph ADT
//-----------------------------------------------------------------------------
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include <stdbool.h>
#include "List.h"

#define UNDEF -1        // Infinity (for negative int values)
#define NIL 0         // Undefined vertex label (for non-positive int values)

// Exported types -------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------

// Returns a Graph pointing to a newly created GraphObj representing a graph having
// n vertices and no edges
Graph newGraph(int n);
// Frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------

// Returns the number of vertices (order) in graph
int getOrder(Graph G);
// Returns the number of edges (size) in graph
int getSize(Graph G);
// Returns the source vertex most recently used in function BFS(),
// or NIL if BFS() has not yet been called
int getSource(Graph G);
// Returns the parent of vertex u in the BFS tree created by BFS(),
// or NIL if BFS() has not yet been called
// Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getParent(Graph G, int u);
// Returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called
// Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDist(Graph G, int u);
// Returns the discover time of vertex u in the DFS tree created by DFS(),
// or INF if DFS() has not yet been called
// Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDiscover(Graph G, int u);
// Returns the finish time of vertex u in the DFS tree created by DFS(),
// or INF if DFS() has not yet been called
// Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getFinish(Graph G, int u);
// Appends to the List L the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exists
// Pre: getSource(G)!=NIL, so BFS() must be called before getPath() is called
// Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
void getPath(List L, Graph G, int u);

// Manipulation procedures ----------------------------------------------------

// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G);
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v,
// and v to the adjacency List of u
// Pre: Two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v);
// inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u
// (but not u to the adjacency List of v)
// Pre: Two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v);
// Runs the BFS algorithm on the Graph G with source s,
// setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s);
// Runs the DFS algorithm on the Graph G with List S, which serves two purposes:
    // First it defines the order in which vertices are to be processed in the main loop (5-7) of DFS
    // Second, when DFS is complete, it will store the vertices by decreasing finish times (hence 𝑆 is considered to be a stack)
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S);

// Other operations -----------------------------------------------------------

// Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);
// Returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G);
// Prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);

#endif
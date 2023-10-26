//-----------------------------------------------------------------------------
//  Connor Hamilton 
//  coohamil 
//  2023 Fall PA3
//  Graph.h
//  Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"
#include "Graph.h"

// struct --------------------------------------------------------------------

// private GraphObj type 
typedef struct GraphObj {
    // Universal (both DFS and BFS) fields
    List* vertexNeighbors;   // array of Lists whose ith element contains the neighbors of vertex i
    char* colors;            // array of ints (or chars, or strings) whose ith element is the color (white, gray, black) of vertex i
    int* parents;            // array of ints whose ith element is the parent of vertex i
    int numVertices;         // order of graph
    int numEdges;            // size of graph

    // DFS fields
    int* discoverTimes;      // array of ints for discovery time of each vertex
    int* finishTimes;        // array of ints for finish time of each vertex
    int time;                // time incrementor for DFS visits

    // BFS fields
    int* distances;          // array of ints whose ith element is the distance from the (most recent) source to vertex i
    int recentVertex;        // label of the vertex that was most recently used as source for BFS
} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// Returns a Graph pointing to a newly created GraphObj representing a graph having
// n vertices and no edges
Graph newGraph(int n) {
    Graph G = (GraphObj*) malloc(sizeof(GraphObj));
    assert(G);
    G->vertexNeighbors = (List*) calloc(n + 1, sizeof(List));
    G->colors = (char*) calloc(n + 1, sizeof(char));
    for (int i = 1; i <= n; i++) {
        G->vertexNeighbors[i] = newList();
        G->colors[i] = 'w';
    }
    G->parents = (int*) calloc(n + 1, sizeof(int));
    G->distances = (int*) calloc(n + 1, sizeof(int));
    G->discoverTimes = (int*) calloc(n + 1, sizeof(int));
    G->finishTimes = (int*) calloc(n + 1, sizeof(int));
    G->numVertices = n;
    G->numEdges = 0;
    G->time = 0;
    G->recentVertex = NIL;

    return G;
}

// Frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG) {
    if (pG && *pG) {
        for (int i = 1; i <= (*pG)->numVertices; i++) {
            freeList(&((*pG)->vertexNeighbors[i]));
        }
        free((*pG)->vertexNeighbors);
        free((*pG)->colors);
        free((*pG)->parents);
        free((*pG)->distances);
        free((*pG)->discoverTimes);
        free((*pG)->finishTimes);
        free(*pG);
        *pG = NULL;
    }
}

// Error functions

void checkGraphExist(Graph G, char* function) {
    if(!G){
        fprintf(stderr, "Graph Error: calling %s() on NULL Graph reference\n", function);
        exit(EXIT_FAILURE);
    }
}
void checkVertex(Graph G, int v, char* function) {
    if (v < 1 || v > G->numVertices) {
        fprintf(stderr, "Graph Error: calling %s() with invalid vertex\n", function);
        exit(EXIT_FAILURE);
    }
}

// Access functions -----------------------------------------------------------

// Returns the number of vertices (order) in graph
int getOrder(Graph G) {
    checkGraphExist(G, "getOrder");
    return G->numVertices;
}

// Returns the number of edges (size) in graph
int getSize(Graph G) {
    checkGraphExist(G, "getSize");
    return G->numEdges;
}

// Returns the source vertex most recently used in function BFS(),
// or NIL if BFS() has not yet been called
int getSource(Graph G) {
    checkGraphExist(G, "getSource");
    return G->recentVertex ? G->recentVertex : NIL;
}

// Returns the parent of vertex u in the BFS tree created by BFS(),
// or NIL if BFS() has not yet been called
// Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getParent(Graph G, int u) {
    checkGraphExist(G, "getParent");
    checkVertex(G, u, "getParent");
    return G->recentVertex || G->time ? G->parents[u] : NIL;
}

// Returns the distance from the most recent BFS source to vertex u,
// or UNDEF if BFS() has not yet been called
// Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDist(Graph G, int u) {
    checkGraphExist(G, "getDist");
    checkVertex(G, u, "getDist");
    return G->recentVertex ? G->distances[u] : UNDEF;
}

// Returns the discover time of vertex u in the DFS tree created by DFS(),
// or UNDEF if DFS() has not yet been called
// Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDiscover(Graph G, int u) {
    checkGraphExist(G, "getDiscover");
    checkVertex(G, u, "getDiscover");
    return G->time ? G->discoverTimes[u] : UNDEF;
}

// Returns the finish time of vertex u in the DFS tree created by DFS(),
// or UNDEF if DFS() has not yet been called
// Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getFinish(Graph G, int u) {
    checkGraphExist(G, "getFinish");
    checkVertex(G, u, "getFinish");
    return G->time ? G->finishTimes[u] : UNDEF;
}

// Appends to the List L the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exists
// Pre: getSource(G)!=NIL, so BFS() must be called before getPath() is called
// Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
void getPath(List L, Graph G, int u) {
    if(!L){
        fprintf(stderr, "List Error: calling getPath() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        fprintf(stderr, "Graph Error: calling getPath() without calling BFS first\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > G->numVertices || (G->distances[u] == NIL && G->recentVertex != u)) {
        append(L, NIL);
        return;
    }

    if (G->recentVertex == u) {
        append(L, G->recentVertex);
    }
    else {
        getPath(L, G, G->parents[u]);
        if (back(L) != 0) {
            append(L, u);
        }
    }
}

// Manipulation procedures ----------------------------------------------------

// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G) {
    checkGraphExist(G, "makeNull");
    for (int i = 1; i <= G->numVertices; i++) {
        clear((G->vertexNeighbors[i]));
        G->parents[i] = NIL;
        G->distances[i] = NIL;
        G->colors[i] = 'w';
    }
    G->numEdges = 0;
    G->recentVertex = NIL;
}

// Helper function for addEdge and addArc
void sortEdge(List L, int e) {
    moveFront(L);
    while (index(L) >= 0) {
        if (e > get(L)) {
            moveNext(L);
        }
        else {
            insertBefore(L, e);
            break;
        }
    }
    if (index(L) == -1) {
        append(L, e);
    }
}

// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v,
// and v to the adjacency List of u
// Pre: Two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v) {
    checkGraphExist(G, "addEdge");
    checkVertex(G, u, "addEdge");
    checkVertex(G, v, "addEdge");

    List L1 = G->vertexNeighbors[u];
    List L2 = G->vertexNeighbors[v];
    moveFront(L1);
    while (index(L1) >= 0) {
        if (v == get(L1)) {
            return;
        }
        moveNext(L1);
    }
    moveFront(L2);
    while (index(L2) >= 0) {
        if (u == get(L2)) {
            return;
        }
        moveNext(L2);
    }

    sortEdge(G->vertexNeighbors[v], u);
    sortEdge(G->vertexNeighbors[u], v);
    G->numEdges += 1;
}

// inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u
// (but not u to the adjacency List of v)
// Pre: Two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v) {
    checkGraphExist(G, "addArc");
    checkVertex(G, u, "addEdge");
    checkVertex(G, v, "addEdge");

    List L = G->vertexNeighbors[u];
    moveFront(L);
    while (index(L) >= 0) {
        if (v == get(L)) {
            return;
        }
        moveNext(L);
    }

    sortEdge(G->vertexNeighbors[u], v);
    G->numEdges += 1;
}

// Runs the BFS algorithm on the Graph G with source s,
// setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s) {
    checkGraphExist(G, "BFS");
    int x;

    for (x = 1; x <= G->numVertices; x++) {
        if (x != s) {
            G->colors[x] = 'w';
            G->distances[x] = UNDEF;
            G->parents[x] = NIL;
        }
    }

    G->colors[s] = 'g';
    G->distances[s] = 0;
    G->parents[s] = NIL;
    List L = newList();
    append(L, s);

    while (length(L) > 0) {
        x = front(L);
        deleteFront(L);
        moveFront(G->vertexNeighbors[x]);
        while (index(G->vertexNeighbors[x]) >= 0) {
            int y = get(G->vertexNeighbors[x]);
            
            if (G->colors[y] == 'w') {
                G->colors[y] = 'g';
                G->distances[y] = (G->distances[x] + 1);
                G->parents[y] = x;
                append(L, y);
            }
            
            moveNext(G->vertexNeighbors[x]);
        }
        G->colors[x] = 'b';
    }

    G->recentVertex = s;
    freeList(&L);
}

// Helper function for DFS, recursive algorithm for visiting vertices from DFS loop using static variable time
void Visit(Graph G, int x) {
    G->discoverTimes[x] = (++G->time);
    G->colors[x] = 'g';

    moveFront(G->vertexNeighbors[x]);
    while (index(G->vertexNeighbors[x]) >= 0) {
        int y = get(G->vertexNeighbors[x]);
        if (G->colors[y] == 'w') {
            G->parents[y] = x;
            Visit(G, y);
        }
        moveNext(G->vertexNeighbors[x]);
    }
    G->colors[x] = 'b';
    G->finishTimes[x] = (++G->time);
}

// Runs the DFS algorithm on the Graph G with List S, which serves two purposes:
    // First it defines the order in which vertices are to be processed in the main loop (5-7) of DFS
    // Second, when DFS is complete, it will store the vertices by decreasing finish times (hence 𝑆 is considered to be a stack)
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S) {
    checkGraphExist(G, "DFS");
    if (length(S) != G->numVertices) {
        fprintf(stderr, "Graph Error: calling DFS() with Graph order that isn't equal to List length\n");
        exit(EXIT_FAILURE);
    }

    G->time = 0;
    int x;
    for (x = 1; x <= G->numVertices; x++) {
        G->colors[x] = 'w';
        G->parents[x] = NIL;
    }
    
    int b = back(S);
    for (x = 1; x <= G->numVertices; x++) {
        int y = front(S);
        if (G->colors[y] == 'w') {
            Visit(G, y);
        }

        moveBack(S);
        while (get(S) != b) {
            if (G->finishTimes[y] > G->finishTimes[get(S)]) {
                movePrev(S);
            }
            else {
                insertAfter(S, y);
                break;
            }
        }
        if (get(S) == b) {
            insertAfter(S, y);
        }

        deleteFront(S);
    }
    
}

// Other operations -----------------------------------------------------------

// Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G) {
    checkGraphExist(G, "transpose");

    Graph newG = newGraph(G->numVertices);
    for (int i = 1; i <= G->numVertices; i++) {
        List curr = G->vertexNeighbors[i];
        moveFront(curr);
        while (index(curr) >= 0) {
            addArc(newG, get(curr), i);
            moveNext(curr);
        }
    }
    return newG;
}

// Returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G) {
    checkGraphExist(G, "copyGraph");

    Graph newG = newGraph(G->numVertices);
    for (int i = 1; i <= G->numVertices; i++) {
        List newL = copyList(G->vertexNeighbors[i]);
        newG->vertexNeighbors[i] = newL;
        newG->colors[i] = G->colors[i];
        newG->parents[i] = G->parents[i];
        newG->discoverTimes[i] = G->discoverTimes[i];
        newG->finishTimes[i] = G->finishTimes[i];
    }
    newG->numVertices = G->numVertices;
    newG->numEdges = G->numEdges;
    return newG;
}

// Prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G) {
    checkGraphExist(G, "printGraph");
    for (int i = 1; i <= G->numVertices; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->vertexNeighbors[i]);
        fprintf(out, "\n");
    }
}
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_COMM_LEN 3
#define MAX_LINE_LEN 256
#define DELIM_OPER " :\n"

// Definition of a graph node.
typedef struct GraphNode {
    char *name;             // Node name identifier.
    struct GraphNode *next;
} GraphNode;

// Definition of a graph.
typedef struct Graph {
    int V;                  // Number of vertices.
    char **idxMap;          // Mapping of vertex names to indices.
    GraphNode **adjList;    // Adjacency list representation of the graph.
} Graph;

// Get the index of a vertex by its name.
int         Get_IdxNode         (Graph *g, char *name);
// Get the name of a vertex by its index.
char*       Get_ValNode         (Graph *g, int idx);

//Create an array for mapping vertex names to indices.
char**      Create_IdxMap       (int V, char *buffer);
// Add an edge between two vertices in the graph.
void        Add_Edge            (Graph *g, char *V1, char *V2);

// Create an empty graph.
Graph*      Create_Graph        (void);
// Create the transposed graph of a given graph.
Graph*      Create_TGraph       (Graph *g);
// Create a graph with adjacency list representation.
Graph*      Create_AdjList      (int V, char *buffer);

// Free the memory occupied by a graph.
void        Free_Graph          (Graph *g);
// Print the adjacency list representation of a graph.
void        Print_Graph         (Graph *g);

#endif /* _GRAPH_H_ */

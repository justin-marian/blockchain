#include "../include/evolve.h"

/**
 * @brief Returns the past set of nodes reachable from a given vertex.
 * 
 * @param g   The graph.
 * @param src The index of the vertex.
 * @return The past set of nodes as a linked list.
 */
ListVal* Past(Graph *g, int src) {
    return Path_Vis(g, src);
}

/**
 * @brief Returns the future set of nodes that can reach a given vertex.
 * 
 * @param g   The graph.
 * @param src The index of the vertex.
 * @return The future set of nodes as a linked list.
 */
ListVal* Future(Graph *g, int src) {
    if (!g || !g->adjList || !g->idxMap) return NULL;
    // The future can be seen by going in reverse.
    Graph *graphT = Create_TGraph(g);
    // Find the path in the transpose graph.
    ListVal *path = Path_Vis(graphT, src);

    Free_Graph(graphT);
    return path;
}

/**
 * @brief Returns the anticone set of nodes for a given vertex.
 * The anticone set contains nodes that are neither in the past nor in the future.
 * 
 * @param g      The graph.
 * @param src    The index of the vertex.
 * @param past   The past set of nodes.
 * @param future The future set of nodes.
 * @return The anticone set of nodes as a linked list.
 */
ListVal* Anticone(Graph *g, int src, ListVal *past, ListVal *future) {
    if (!g || !g->adjList || !g->idxMap) return NULL;

    ListVal *path = NULL;

    // Iterate through all nodes in the graph.
    for (int pass = 0; pass < g->V; pass++) {
        char *name = Get_ValNode(g, pass);
        if (src != pass) {
            // If the node is not in the past and not in the future, add it to the anticone.
            if (!Contains_Ord(past, name) && !Contains_Ord(future, name)) {
                path = Insert_Ord(path, name);
            }
        }
    }

    return path;
}

/**
 * @brief Returns the tips set of nodes in the graph.
 * The tips set contains nodes with no incoming edges.
 * 
 * @param g The graph.
 * @return The tips set of nodes as a linked list.
 */
ListVal* Tips(Graph *g) {
    if (!g || !g->adjList || !g->idxMap) return NULL;

    // Allocate memory for an array to store in-degrees of nodes.
    int *inDeg = (int*)calloc(g->V, sizeof(int));

    if (!inDeg) {
        fprintf(stderr, "Memory INDEG allocation failed...");
        return NULL;
    }

    // Calculate in-degrees for all nodes in the graph.
    for (int pass = 0; pass < g->V; pass++) {
        GraphNode *node = g->adjList[pass];
        while (node) {
            int idx = Get_IdxNode(g, node->name);
            inDeg[idx]++;
            node = node->next;
        }
    }

    ListVal *path = NULL;

    // Find nodes with zero in-degrees and add them to the tips set.
    for (int pass = 0; pass < g->V; pass++) {
        if (!inDeg[pass]) {
            path = Insert_Ord(path, Get_ValNode(g, pass));
        }
    }

    free(inDeg);
    return path;
}
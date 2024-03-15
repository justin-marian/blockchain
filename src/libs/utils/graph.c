#include "../include/graph.h"

/* ----------------------------------------------------------------------------------- */

/**
 * @brief Get the name of a node in the graph by its index.
 * 
 * @param g The graph.
 * @param v The index of the node.
 * @return The name of the node.
 */
char* Get_ValNode(Graph *g, int v) {
    if (!g || !g->idxMap || v >= g->V)
        return NULL;
    return g->idxMap[v];
}

/**
 * @brief Get the index of a node in the graph by its name.
 * 
 * @param g    The graph.
 * @param name The name of the node.
 * @return The index of the node.
 */
int Get_IdxNode(Graph *g, char *name) {
    if (!g || !g->idxMap || !name) return -1;
    // Iterate through the vertexes until we found the index node.
    for (int v = 0; v < g->V; v++)
        if (!strcmp(g->idxMap[v], name))
            return v;
    return -1;
}

/**
 * @brief Add an edge between two nodes in the graph.
 * 
 * @param g  The graph.
 * @param V1 The name of the first node.
 * @param V2 The name of the second node.
 */
void Add_Edge(Graph *g, char *V1, char *V2) {
    if (!g || !g->adjList || !g->idxMap || !V1 || !V2) return;

    // Get the index of the first node (V1).
    int v1 = Get_IdxNode(g, V1);
    if (v1 == -1) return; // Not found.

    // Create a new graph node for the second node (V2)
    GraphNode *v2 = (GraphNode*)malloc(sizeof(GraphNode));
    if (!v2) return;

    // Duplicate the name of the second node.
    // Ensure it's not modified externally.
    v2->name = strdup(V2);
    if (!v2->name) {
        free(v2);
        return;
    }

    // Add the new node (V2) to the adjacency list of the first node (V1).
    v2->next = g->adjList[v1];
    g->adjList[v1] = v2;
}

/* ----------------------------------------------------------------------------------- */


/**
 * @brief Create a graph based on data from a file.
 * 
 * @return A pointer to the created graph.
 */
Graph* Create_Graph(void) {
    FILE *fin = fopen("blockdag.in", "r");
 
    if (!fin) {
        fprintf(stderr, "Couldn't open file for reading");
        exit(EXIT_FAILURE);
    }

    size_t len = 0;
    char *line = NULL;

    // Read the first line to determine the number of vertices (V).
    if (getline(&line, &len, fin) == -1)
        fprintf(stderr, "LINE READ");

    int V = atoi(line);

    // Read the second line containing vertex names.
    if (getline(&line, &len, fin) == -1)
        fprintf(stderr, "LINE READ");

    // Create an adjacency list,
    // representation of the graph using the provided data.
    Graph *g = Create_AdjList(V, line);

    if (!g) {
        fclose(fin);
        free(line);
        return NULL;
    }

    // Read and process the remaining lines to add edges between vertices.
    if (getline(&line, &len, fin) == -1)
        fprintf(stderr, "LINE READ");

    while (getline(&line, &len, fin) != -1) {
        char *V1 = strtok(line, DELIM_OPER), *V2 = NULL;
        // Add an edge between vertices V1 and V2 in the graph.
        while ((V2 = strtok(NULL, DELIM_OPER))) {
            Add_Edge(g, V1, V2);
        }
    }

    fclose(fin);
    free(line);
    return g;
}

/**
 * @brief Create a transpose graph of the given graph.
 * 
 * @param g The original graph.
 * @return A pointer to the transpose graph.
 */
Graph* Create_TGraph(Graph *g) {
    if (!g || !g->adjList || !g->idxMap) return NULL;

    FILE *fin = fopen("blockdag.in", "r");

    if (!fin) {
        fprintf(stderr, "Couldn't open file for reading");
        exit(EXIT_FAILURE);
    }

    size_t len = 0;
    char *line = NULL;

    // Read the first two lines from the file,
    // which are not used in this function.
    if (getline(&line, &len, fin) == -1) 
        fprintf(stderr, "LINE READ");
    if (getline(&line, &len, fin) == -1)
        fprintf(stderr, "LINE READ");

    fclose(fin);

    // Create an adjacency list representation of the transpose graph.
    Graph *graphT = Create_AdjList(g->V, line);
    if (!graphT) return NULL;

    // Iterate through the vertices of the original graph
    // and reverse edges in the transpose graph.
    for (int u = 0; u < g->V; u++) {
        GraphNode* v = g->adjList[u];
        while (v) {
            Add_Edge(graphT, v->name, Get_ValNode(g, u));
            v = v->next;
        }
    }

    free(line);
    return graphT;
}

/**
 * @brief Create an adjacency list representation of a graph.
 * 
 * @param V      The number of vertices in the graph.
 * @param buffer A buffer containing vertex names.
 * @return A pointer to the created graph.
 */
Graph* Create_AdjList(int V, char *buffer) {
    Graph *g = (Graph*)malloc(sizeof(Graph));

    if (!g) {
        fprintf(stderr, "Memory GRAPH allocation failed...");
        return NULL;
    }

    // Set the number of vertices in the graph.
    g->V = V;
    // Create an index map for vertex names using the provided buffer.
    g->idxMap = Create_IdxMap(V, buffer);

    if (!g->idxMap) {
        free(g);
        return NULL;
    }

    // Allocate memory for the adjacency list (array of linked lists).
    g->adjList = (GraphNode**)calloc(V, sizeof(GraphNode*));

    if (!g->adjList) {
        fprintf(stderr, "Memory ADJLIST allocation failed...");
        free(g->idxMap);
        free(g);
        return NULL;
    }

    // Return a pointer to the created graph.
    return g;
}

/* ----------------------------------------------------------------------------------- */

/**
 * @brief Free the memory allocated for a graph.
 * 
 * @param g The graph to be freed.
 */
void Free_Graph(Graph *g) {
    if (!g) return;

    if (g->adjList) {
        // Iterate through each vertex in the adjacency list.
        for (int u = 0; u < g->V; u++) {
            GraphNode *v = g->adjList[u];

            while (v) {
                GraphNode *del = v;
                v = v->next;
                // Free the memory allocated for
                //  the name of the node and node itself.
                free(del->name);
                free(del);
            }
        }
        free(g->adjList);
    }

    if (g->idxMap) {
        // Iterate through each vertex in the index map
        // and free the memory for vertex names.
        for (int u = 0; u < g->V; u++) {
            free(g->idxMap[u]);
        }
        free(g->idxMap);
    }

    // Free graph itself.
    free(g);
}

/**
 * @brief Print the adjacency list representation of a graph.
 * 
 * @param g The graph to be printed.
 */
void Print_Graph(Graph *g) {
    if (!g || !g->adjList || !g->idxMap) return;

    for (int u = 0; u < g->V; u++) {
        printf("Node [%s] : ", Get_ValNode(g, u));

        GraphNode *v = g->adjList[u];
        while (v) {
            printf("(%s) -> ", v->name);
            v = v->next;
        }

        printf("(null)\n");
    }
}

/* ----------------------------------------------------------------------------------- */

/**
 * @brief Create an index map for vertex names from a buffer.
 * 
 * @param V      The number of vertices.
 * @param buffer A buffer containing vertex names.
 * @return An array of strings representing vertex names.
 */
char** Create_IdxMap(int V, char *buffer) {
    char **idxMap = (char**)calloc(V, sizeof(char*));

    if (!idxMap) return NULL;

    int idx = 0;

    for (int v = 0; v < V; v++) {
        // Find the start of the next word
        while (buffer[idx] && strchr(DELIM_OPER, buffer[idx])) {
            idx++;
        }
        // Find the end of the current word
        int wordStart = idx;
        while (buffer[idx] && !strchr(DELIM_OPER, buffer[idx])) {
            idx++;
        }
        if (wordStart == idx) {
            // No more words found, so free allocated memory and return
            for (int i = 0; i < v; i++) {
                free(idxMap[i]);
            }
            free(idxMap);
            return NULL;
        }

        // Calculate word length
        int wordLength = idx - wordStart;
        // Allocate memory for the word and copy it
        idxMap[v] = malloc((wordLength + 1) * sizeof(char));
        if (!idxMap[v]) {
            for (int i = 0; i <= v; i++) {
                free(idxMap[i]);
            }
            free(idxMap);
            return NULL;
        }

        strncpy(idxMap[v], &buffer[wordStart], wordLength);
        idxMap[v][wordLength] = '\0';
    }

    return idxMap;
}

/* ----------------------------------------------------------------------------------- */

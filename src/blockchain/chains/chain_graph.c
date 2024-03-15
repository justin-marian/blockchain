#include "../include/chain_graph.h"

/**
 * @brief Perform Breadth-First Search (BFS) on the graph starting from a source node.
 * 
 * @param g     A pointer to the graph.
 * @param src   The index of the source node.
 * @return      A list of values visited during BFS, or NULL on failure.
 */
ListVal* Path_Vis(Graph *g, int src) {
    if (!g || !g->adjList || !g->idxMap) return NULL;

    // Create a queue for BFS traversal.
    Queue *queue = Create_Queue();
    if (!queue) return NULL;

    // Initialize an array to track visited nodes.
    bool *vis = (bool*)calloc(g->V, sizeof(bool));

    if (!vis) {
        fprintf(stderr, "ERROR: Memory VIS allocation failed...");
        Free_Queue(queue);
        return NULL;
    }

    Enqueue(queue, src);  // Enqueue the source node.
    vis[src] = true;      // Mark the source node as visited.
    ListVal* path = NULL; // Initialize the list of visited nodes.

    while (!IsEmpty_Queue(queue)) {
        int node = Front(queue);  // Get the front node from the queue.
        Dequeue(queue);           // Dequeue the front node.

        // Add the node to the visited list if not the source node.
        if (node != src) {
            path = Insert_Ord(path, Get_ValNode(g, node));
        }

        // Get the adjacent nodes of the current node.
        GraphNode* srcNode = g->adjList[node];

        while (srcNode) {
            // Get the index of the neighbor node.
            int neighbor = Get_IdxNode(g, srcNode->name);
            // Mark the neighbor node as visited.
            if (!vis[neighbor]) {
                vis[neighbor] = true;        
                Enqueue(queue, neighbor);    // Enqueue the neighbor node.
            }
            srcNode = srcNode->next;  // Move to the next adjacent node.
        }
    }

    free(vis);
    Free_Queue(queue);
    return path;
}

/**
 * @brief Recursively checks for a cycle in the graph using depth-first search (DFS).
 * 
 * @param g     A pointer to the graph.
 * @param src   The current source node index.
 * @param vis   An array to track visited nodes.
 * @param stack An array to track nodes in the current recursion stack.
 * @return true if a cycle is found, false otherwise.
 */
bool TopoSort(Graph *g, int src, bool *vis, bool *stack) {
    if (!g || !g->adjList || !g->idxMap) return false;
    // If the node is in the current stack, a cycle is detected.
    if (stack[src]) return true;
    // If the node is already visited and not in the stack, no cycle.
    if (vis[src]) return false;

    vis[src] = true;       // Mark the node as visited.
    stack[src] = true;     // Mark the node as part of the current recursion stack.
    GraphNode* srcNode = g->adjList[src];  // Get the adjacent nodes of the current node.

    while (srcNode) {
        // Get the index of the neighbor node.
        int neighbor = Get_IdxNode(g, srcNode->name);
        // Recursively check the neighbor nodes for cycles.
        if (TopoSort(g, neighbor, vis, stack)) {
            return true;
        }
        srcNode = srcNode->next;  // Move to the next adjacent node
    }

    // If the recursion stack is unwound, mark the node as not in the stack.
    stack[src] = false;
    // No cycle found in this branch.
    return false;
}

/**
 * @brief Checks if the graph has a cycle using topological sorting.
 * 
 * @param g A pointer to the graph.
 * @return true if the graph has a cycle, false otherwise.
 */
bool HasCycle(Graph *g) {
    if (!g || !g->adjList || !g->idxMap) return false;

    // Initialize array for visited, and nodes that are in recursion stack.
    bool* vis = (bool*)calloc(g->V, sizeof(bool));
    bool* stack = (bool*)calloc(g->V, sizeof(bool));

    if (!vis || !stack) {
        fprintf(stderr, "ERROR: VIS/STACK Memory allocation failed...");
        free(vis);
        free(stack);
        return false;
    }

    bool hasCycle = false;

    // Check for cycles starting from each unvisited node.
    for (int node = 0; node < g->V && !hasCycle; node++) {
        if (!vis[node]) {
            hasCycle = TopoSort(g, node, vis, stack);
        }
    }

    free(vis);
    free(stack);
    return hasCycle;
}

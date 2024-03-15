#ifndef _CHAIN_GRAP_H_
#define _CHAIN_GRAP_H_

#include "./block_dag.h"

// Function to find the path visited from a source node in the graph.
ListVal*    Path_Vis    (Graph *g, int s);
// Function to check if a graph contains a cycle.
bool        HasCycle    (Graph *g);
// Recursive function used in topological sorting to detect cycles.
bool        TopoSort    (Graph *g, int src, bool *vis, bool *stack);

#endif /* _CHAIN_GRAP_H_ */

#ifndef _EVOLVE_H_
#define _EVOLVE_H_

#include "./block_dag.h"

// Returns the past set of nodes reachable from a given vertex.
ListVal*    Past        (Graph *g, int src);
// Returns the future set of nodes that can reach a given vertex.
ListVal*    Future      (Graph *g, int src);

// The tips set contains nodes with no incoming edges.
ListVal*    Tips        (Graph *g);
// The anticone set contains nodes that are neither in the past nor in the future.
ListVal*    Anticone    (Graph *g, int src, ListVal *past, ListVal *future);

#endif /* _EVOLVE_H_ */

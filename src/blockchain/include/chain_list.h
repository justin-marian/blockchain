#ifndef _CHAIN_LIST_H_
#define _CHAIN_LIST_H_

#include "./block_dag.h"

// Create a new ordered list containing a single value.
ListVal*    Create_Ord      (char *name);
// Insert a value into an ordered list while maintaining the order.
ListVal*    Insert_Ord      (ListVal *list, char *name);

// Check if a value exists in an ordered list.
bool        Contains_Ord    (ListVal *list, char *name);

// Print the values in an ordered list to a file.
void        Print_Ord       (ListVal *list, FILE *fout);
// Free the memory allocated for an ordered list.
void        Free_Ord        (ListVal *list);

#endif /* _CHAIN_LIST_H_ */

#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition of a doubly-linked list node.
typedef struct ListNode {
    int val;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

// Definition of a doubly-linked list.
typedef struct List {
    ListNode *head;
} List;

// Definition of a linked list node for values.
typedef struct ListVal {
    char *name;         // Node name identifier.
    struct ListVal *next;
} ListVal;

// Create a new empty list.
List* Create_List(void);
// Check if the list is empty.
bool IsEmpty_List(List *list);
//Free the memory occupied by the list and its elements.
void Free_List(List *list);

#endif /* _LIST_H_ */

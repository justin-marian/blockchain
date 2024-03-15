#ifndef _STACK_H_
#define _STACK_H_

#include "list.h"

// Define Stack as an alias for List.
typedef List Stack;

// Create a new stack.
Stack*      Create_Stack    (void);
// Check if the stack is empty.
bool        IsEmpty_Stack   (Stack *stack);
// Free the memory occupied by the stack and its elements.
void        Free_Stack      (Stack *stack);

// Get the top element of the stack.
int         Top             (Stack *stack);
// Push an element onto the stack.
void        Push            (Stack *stack, int elem);
// Pop and remove the top element from the stack.
void        Pop             (Stack *stack);

#endif /* _STACK_H_ */

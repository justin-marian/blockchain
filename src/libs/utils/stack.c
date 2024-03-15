#include "../include/stack.h"

/**
 * @brief Create a new stack (wrapper over List).
 * 
 * @return A pointer to the created stack.
 */
Stack* Create_Stack(void) {
    return Create_List();
}

/**
 * @brief Check if the stack is empty (wrapper over List).
 * 
 * @param stack The stack to check.
 * @return true if the stack is empty, false otherwise.
 */
bool IsEmpty_Stack(Stack *stack) {
    return IsEmpty_List(stack);
}

/**
 * @brief Free the memory occupied by the stack (wrapper over List).
 * 
 * @param stack The stack to free.
 */
void Free_Stack(Stack *stack) {
    Free_List(stack);
}

/**
 * @brief Get the top element of the stack.
 * 
 * @param stack The stack to get the top element from.
 * @return The top element of the stack or -1 if the stack is empty.
 */
int Top(Stack *stack) {
    if (IsEmpty_Stack(stack)) return -1;
    return stack->head->next->val;
}

/**
 * @brief Push (add) an element onto the stack.
 * 
 * @param stack The stack to push the element onto.
 * @param val The value to push onto the stack.
 */
void Push(Stack *stack, int val) {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) return;

    node->val = val;
    node->next = stack->head->next;
    node->prev = stack->head;

    stack->head->next->prev = node;
    stack->head->next = node;
}

/**
 * @brief Pop (remove) the top element from the stack.
 * 
 * @param stack The stack to pop from.
 */
void Pop(Stack *stack) {
    if (IsEmpty_Stack(stack)) return;

    ListNode *temp = stack->head->next;
    stack->head->next = stack->head->next->next;
    stack->head->next->prev = stack->head;

    free(temp);
}

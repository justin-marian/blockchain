#include "../include/list.h"

/**
 * @brief Create a new linked list.
 * 
 * @return A pointer to the created linked list.
 */
List* Create_List(void) {
    List *list = (List*)malloc(sizeof(List));
    if (!list) return NULL;

    list->head = (ListNode*)malloc(sizeof(ListNode));
    if (!list->head) {
        perror("Memory LISTNODE allocation failed...");
        free(list);
        return NULL;
    }

    list->head->next = list->head;
    list->head->prev = list->head;

    return list;
}

/**
 * @brief Check if the linked list is empty.
 * 
 * @param list The linked list to check.
 * @return true if the linked list is empty, false otherwise.
 */
bool IsEmpty_List(List *list) {
    if (!list || !list->head) return true;
    return (list->head->next == list->head);
}

/**
 * @brief Free the memory occupied by the linked list and its nodes.
 * 
 * @param list The linked list to free.
 */
void Free_List(List *list) {
    if (!list) return;

    ListNode *pass = list->head->next;

    while (pass != list->head) {
        ListNode* temp = pass;
        pass = pass->next;
        free(temp);
    }

    free(list->head);
    free(list);
}

#include "../include/queue.h"

/**
 * @brief Create a new queue (wrapper over List).
 * 
 * @return A pointer to the created queue.
 */
Queue* Create_Queue(void) {
    return Create_List();
}

/**
 * @brief Check if the queue is empty (wrapper over List).
 * 
 * @param queue The queue to check.
 * @return true if the queue is empty, false otherwise.
 */
bool IsEmpty_Queue(Queue *queue) {
    return IsEmpty_List(queue);
}

/**
 * @brief Free the memory occupied by the queue (wrapper over List).
 * 
 * @param queue The queue to free.
 */
void Free_Queue(Queue *queue) {
    Free_List(queue);
}

/**
 * @brief Get the front element of the queue.
 * 
 * @param queue The queue to get the front element from.
 * @return The front element of the queue or -1 if the queue is empty.
 */
int Front(Queue *queue) {
    if (IsEmpty_Queue(queue)) return -1;
    return queue->head->prev->val;
}

/**
 * @brief Enqueue (add) an element to the back of the queue.
 * 
 * @param queue The queue to enqueue the element into.
 * @param val The value to enqueue.
 */
void Enqueue(Queue *queue, int val) {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) return;

    node->val = val;
    node->next = queue->head->next;
    node->prev = queue->head;

    queue->head->next->prev = node;
    queue->head->next = node;
}

/**
 * @brief Dequeue (remove) the front element from the queue.
 * 
 * @param queue The queue to dequeue from.
 */
void Dequeue(Queue *queue) {
    if (IsEmpty_Queue(queue)) return;

    ListNode *temp = queue->head->prev;
    queue->head->prev = queue->head->prev->prev;
    queue->head->prev->next = queue->head;

    free(temp);
}

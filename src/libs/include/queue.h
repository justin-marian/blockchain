#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "list.h"

// Define Queue as an alias for List.
typedef List Queue;

// Create a new queue.
Queue*      Create_Queue    (void);
// Check if the queue is empty.
bool        IsEmpty_Queue   (Queue *queue);
// Free the memory occupied by the queue and its elements.
void        Free_Queue      (Queue *queue);

// Get the front element of the queue.
int         Front           (Queue *queue);
// Enqueue an element onto the queue.
void        Enqueue         (Queue *queue, int elem);
// Dequeue and remove the front element from the queue.
void        Dequeue         (Queue *queue);

#endif /* _QUEUE_H_ */

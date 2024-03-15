#include "../include/chain_list.h"

/**
 * @brief Create a new node with a given name.
 * 
 * @param name The name to be stored in the new node.
 * @return A pointer to the newly created node, or NULL if allocation fails.
 */
ListVal* Create_Ord(char *name) {
    // Create a new node with a given name.
    ListVal* node = (ListVal*)malloc(sizeof(ListVal));

    if (node) {
        // Copy the name into the node.
        node->name = strdup(name);
        // Memory allocation fails.
        if (!node->name) {
            fprintf(stderr, "Memory NODE allocation failed...");
            free(node);
            return NULL;
        }
        // Initialize the next pointer to NULL.
        node->next = NULL;
    }

    // Return current created node.
    return node;
}

/**
 * @brief Compare two strings and return their order.
 * 
 * @param str1 The first string.
 * @param str2 The second string.
 * @return -1 if str1 is smaller, 1 if str2 is smaller, 0 if equal.
 */
static int Compare(char *str1, char *str2) {
    if (!strcmp(str1, "Genesis")) return -1;
    if (!strcmp(str2, "Genesis")) return 1;
    return strcmp(str1, str2);
}

/**
 * @brief Insert a node into the linked list in an ordered manner.
 * 
 * @param list The linked list.
 * @param name The name to be inserted.
 * @return A pointer to the updated linked list.
 */
ListVal* Insert_Ord(ListVal *list, char *name) {
    // Create a new node with the given name.
    ListVal* node = Create_Ord(name);
    if (!node) return list;

    // Initialize a pointer to traverse the list.
    ListVal* pass = list;
    // Initialize a pointer to keep track the previous node.
    ListVal* prev = NULL;

    // Traverse the list until the correct position is found.
    while (pass && Compare(pass->name, name) < 0) {
        prev = pass;
        pass = pass->next;
    }

    // Insert the new node.
    if (pass == list) {
        // At the begging.
        node->next = list;
        list = node;
    } else if (!pass) {
        // At the end.
        prev->next = node;
    } else {
        // In the middle.
        node->next = pass;
        prev->next = node;
    }

    // Return the updated list.
    return list;
}

/**
 * @brief Print the elements of the list in order to a file.
 * 
 * @param list The linked list to be printed.
 * @param fout The file to which the elements will be printed.
 */
void Print_Ord(ListVal *list, FILE *fout) {
    while (list) {
        fprintf(fout, "%s ", list->name);
        list = list->next;
    }
    fprintf(fout, "\n");
}

/**
 * @brief Check if a given name exists in the list.
 * 
 * @param list The linked list to be checked.
 * @param name The name to search for.
 * @return true if the name is found in the list, false otherwise.
 */
bool Contains_Ord(ListVal *list, char *name) {
    while (list) {
        if (!strcmp(list->name, name))
            return true; // Name is found, return true.
        list = list->next;
    }
    return false; // Name is not found.
}

/**
 * @brief Free the memory allocated for the linked list.
 * 
 * @param list The linked list to be freed.
 */
void Free_Ord(ListVal* list) {
    while (list) {
        ListVal* elem = list;
        list = list->next;
        // Free the memory for the name and node.
        free(elem->name);
        free(elem);
    }
}

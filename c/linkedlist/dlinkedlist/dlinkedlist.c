//
// Created by Dewey Jose on 4/24/17.
//

#include <stdlib.h>
#include "dlinkedlist.h"


/*********************************************************
 * Remove the node from the list for the given value
 * @param list
 * @param value
 ********************************************************/

int dll_remove(dlinkedlist* list, void* value) {
    dnode* node = dll_search(list, value);
    if (node == NULL) {
        return 0;
    }

    node->previous->next = node->next;
    node->next->previous = node->previous;

    dll_deallocate_dnode(&node);

    return 1;
}

/*********************************************************
 * Search for a node with the given value
 * @param list
 * @param value
 * @return
 ********************************************************/

dnode* dll_search(dlinkedlist* list, void* value) {
    dnode* current = list->NIL->next;
    while (current != list->NIL) {
        comparator_func func = *(list->comparator);
        if (func(current->value, value) == 0) {
            return current;
        } else {
            current = current->next;
        }
    }
    return NULL;
}

/*********************************************************
 * Pop a value from the head of the list
 * @param list
 * @return
 ********************************************************/

int dll_pop_head(dlinkedlist* list, void** value) {
    if (dll_list_is_empty(list)) {  return 0; }

    *value = list->NIL->next->value;

    dnode* head = list->NIL->next;

    list->NIL->next = list->NIL->next->next;
    list->NIL->next->previous = list->NIL;

    dll_deallocate_dnode(&head);

    return 1;
}

/*********************************************************
 * Pop a value from the tail of the list
 * @param list
 * @param tail
 * @return
 ********************************************************/

int dll_pop_tail(dlinkedlist* list, void** value) {
    if (dll_list_is_empty(list)) { return 0; }

    *value = list->NIL->previous->value;

    dnode* tail = list->NIL->previous;

    list->NIL->previous = list->NIL->previous->previous;
    list->NIL->previous->next = list->NIL;

    dll_deallocate_dnode(&tail);

    return 1;
}

/*********************************************************
 * Push a value at the head of the list
 * @param list
 * @param value
 ********************************************************/

void dll_push_head(dlinkedlist* list, void* value) {
    dnode* node = dll_allocate_dnode(value);

    node->previous = list->NIL;
    node->next = list->NIL->next;

    list->NIL->next->previous = node;
    list->NIL->next = node;
}

/*********************************************************
 *
 * @param list
 * @param value
 ********************************************************/

void dll_push_tail(dlinkedlist* list, void* value) {
    dnode* node = dll_allocate_dnode(value);

    node->previous = list->NIL->previous;
    node->next = list->NIL;

    list->NIL->previous->next = node;
    list->NIL->previous = node;
}

/*********************************************************
 * Allocate a node for value
 * @param value
 * @return
 ********************************************************/

dnode* dll_allocate_dnode(void* value) {
    dnode* node = malloc(sizeof(struct dnode));
    node->previous = NULL;
    node->next = NULL;
    node->value = value;
    return node;
}

/*********************************************************
 * Deallocate the node, set everything to NULL;
 * @param value
 * @return
 ********************************************************/

void dll_deallocate_dnode(dnode** node) {
    free(*node);
    *node = NULL;
}

/*********************************************************
 * Allocate dlinkedlist
 * @return
 ********************************************************/

dlinkedlist* dll_allocate_dlinkedlist(comparator_func comparator) {
    dlinkedlist* list = malloc(sizeof(struct dlinkedlist));
    list->NIL = dll_allocate_dnode(0);
    list->NIL->next = list->NIL;
    list->NIL->previous = list->NIL;
    list->comparator = (comparator == NULL ? &compare_ptr : comparator);
    return list;
}

/*********************************************************
 * Deallocate dlinkedlist. First deallocate all the nodes
 * then the dlinkedlist.
 * @param list
 ********************************************************/

void dll_deallocate_dlinkedlist(dlinkedlist** list) {
    dlinkedlist* x = *list;
    if (!dll_list_is_empty(*list)) {
        dnode *next = x->NIL->next;
        while (next != x->NIL) {
            dnode *next_next = next->next;
            dll_deallocate_dnode(&next);
            next = next_next;
        }
    }
    dll_allocate_dnode(&(x->NIL));
    free(x);
    *list = NULL;
}

/*********************************************************
 * Helper to determine if the list is empty
 * @param list
 * @return
 ********************************************************/

int dll_list_is_empty(dlinkedlist* list) {
    return (list->NIL->next == list->NIL);
}
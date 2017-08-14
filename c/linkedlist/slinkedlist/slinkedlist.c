//
// Created by Dewey Jose on 4/11/17.
//

#include <stdlib.h>
#include "slinkedlist.h"

/*********************************************************
 * Allocate a new node for the value, insert at the head
 * @param list
 * @param value
 * @return node*
 *********************************************************/

void sll_insert(slinkedlist *list, void* value) {
    snode* node = sll_allocate_node(value);
    node->next = list->NIL->next;
    list->NIL->next = node;
}

/*********************************************************
 * Removal helper, find based on value,
 * then remove using previous pointer
 * @param list
 * @param value
 ********************************************************/

void* sll_remove(slinkedlist *list, void* value) {
    snode* current = list->NIL->next;
    snode* previous = list->NIL;

    while (current != list->NIL) {

        comparator_func func = *(list->comparator);
        if (func(current->value, value) == 0) {
            void* old_value = current->value;
            previous->next = current->next;
            sll_deallocate_node(&current);
            return old_value;
        }

        previous = current;
        current = current->next;
    }

    return NULL;
}

/*********************************************************
 * Find the node with value
 * @param list
 * @param value
 * @return
 ********************************************************/

snode * sll_search(slinkedlist *list, void* value) {
    snode * current = list->NIL->next;
    while (current != list->NIL) {
        comparator_func func = *(list->comparator);
        if (func(current->value, value) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/*********************************************************
 * Allocate node
 * @param value
 * @return
 ********************************************************/

snode * sll_allocate_node(void* value) {
    snode * node = malloc(sizeof(struct snode));
    node->value = value;
    node->next = NULL;
    return node;
}

/*********************************************************
 * deallocate nodes of slinkedlist
 * @param list
 ********************************************************/

void sll_deallocate_nodes(slinkedlist* list) {
    snode * x = list->NIL->next;
    while (x != list->NIL) {
        snode* next = x->next;
        sll_deallocate_node(&x);
        x = next->next;
    }
    list->NIL->next = list->NIL;
}

/*********************************************************
 * deallocate node
 * @param node
 *********************************************************/

void sll_deallocate_node(snode **node) {
    free(*node);
    *node = NULL;
}

/*********************************************************
 * Allocate slinkedlist
 * @return
 ********************************************************/

slinkedlist* sll_allocate_list(comparator_func comparator) {
    slinkedlist* list = (slinkedlist*)malloc(sizeof(struct slinkedlist));
    list->NIL = sll_allocate_node(0);
    list->NIL->next = list->NIL;
    list->comparator = (comparator == NULL) ? &compare_ptr : comparator;
    return list;
}

/*********************************************************
 * Deallocate slinkedlist and its nodes
 * @param list
 ********************************************************/

void sll_deallocate_list(slinkedlist** list) {
    if (!sll_is_empty(list)) {
        sll_deallocate_nodes(*list);
    }
    sll_deallocate_node(&((*list)->NIL));
    free(*list);
    *list = NULL;
}

/*********************************************************
 * Helper to determine if the slinkedlist is empty
 * @param list
 * @return
 ********************************************************/

int sll_is_empty(slinkedlist* list) {
    return list->NIL->next == list->NIL;
}
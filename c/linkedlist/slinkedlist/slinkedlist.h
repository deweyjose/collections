//
// Created by Dewey Jose on 4/11/17.
//

#include <stdbool.h>
#include "../llcompare.h"

#ifndef COLLECTIONS_SLINKEDLIST_H
#define COLLECTIONS_SLINKEDLIST_H

typedef struct snode snode;
struct snode {
    snode* next;
    void * value;
};

typedef struct slinkedlist slinkedlist;
struct slinkedlist {
    snode* NIL;
    comparator_func comparator;
};

void sll_insert(slinkedlist* list, void* value);

void* sll_remove(slinkedlist* list, void* value);

snode* sll_search(slinkedlist* list, void* value);

int sll_is_empty(slinkedlist* list);

snode* sll_allocate_node(void* value);

void sll_deallocate_node(snode** node);

void sll_deallocate_nodes(slinkedlist* list);

slinkedlist* sll_allocate_list(comparator_func comparator);

void sll_deallocate_list(slinkedlist** list);

#endif //COLLECTIONS_SLINKEDLIST_H

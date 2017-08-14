//
// Created by Dewey Jose on 4/24/17.
//

#include "../llcompare.h"

#ifndef COLLECTIONS_DLINKEDLIST_H
#define COLLECTIONS_DLINKEDLIST_H

typedef struct dnode dnode;
struct dnode {
    dnode* previous;
    dnode* next;
    void* value;
};

typedef struct dlinkedlist dlinkedlist;
struct dlinkedlist {
    dnode* NIL;
    comparator_func comparator;
};

void dll_push_head(dlinkedlist* list, void* value);

void dll_push_tail(dlinkedlist* list, void* value);

int dll_pop_head(dlinkedlist* list, void** head);

int dll_pop_tail(dlinkedlist* list, void** tail);

dnode* dll_search(dlinkedlist* list, void* value);

int dll_remove(dlinkedlist* list, void* value);

dnode* dll_allocate_dnode(void* value);

void dll_deallocate_dnode(dnode** node);

dlinkedlist* dll_allocate_dlinkedlist(comparator_func comparator);

void dll_deallocate_dlinkedlist(dlinkedlist** list);

int dll_list_is_empty(dlinkedlist* list);

#endif //COLLECTIONS_DLINKEDLIST_H

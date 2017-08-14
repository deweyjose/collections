//
// Created by Dewey Jose on 4/24/17.
//
#include <stdlib.h>
#include "assert.h"
#include "../dlinkedlist.h"
#include "../../../tharness/tharness.h"

#define TCMP(x, y) *((int*)x) == y

/*********************************************************
 * Test dnode allocation/deallocation
 *
 ********************************************************/

void test_allocate_dnode() {
    int x = 3;
    dnode* node = dll_allocate_dnode(&x);
    assert(node->previous == NULL);
    assert(node->next     == NULL);
    assert(TCMP(node->value, x));

    dll_deallocate_dnode(&node);
    assert(node           == NULL);
}

/*********************************************************
 * Test dnode allocation/deallocation
 ********************************************************/

void test_allocate_dlinkedlist() {
    dlinkedlist* list = dll_allocate_dlinkedlist(NULL);
    dll_deallocate_dlinkedlist(&list);
    assert(list == NULL);
}

/*********************************************************
 * Test pushing elements to the head of the list
 ********************************************************/

void test_push_head() {
    dlinkedlist* list = dll_allocate_dlinkedlist(&compare_int);

    int numbers[] = {1, 2, 3};

    dll_push_head(list, &numbers[0]);
    assert(TCMP(list->NIL->next->value, numbers[0]));
    assert(TCMP(list->NIL->previous->value, numbers[0]));
    assert(list->NIL->next->next == list->NIL);
    assert(list->NIL->previous->next == list->NIL);

    dll_push_head(list, &numbers[1]);
    assert(TCMP(list->NIL->next->value, numbers[1]));
    assert(TCMP(list->NIL->previous->value, numbers[0]));

    dll_push_head(list, &numbers[2]);
    assert(TCMP(list->NIL->next->value, numbers[2]));
    assert(TCMP(list->NIL->next->next->value, numbers[1]));
    assert(TCMP(list->NIL->previous->previous->value, numbers[1]));
    assert(TCMP(list->NIL->previous->value, numbers[0]));

    dll_deallocate_dlinkedlist(&list);
    assert(list == NULL);
}

/*********************************************************
 * Test pushing elements to the tail of the list
 ********************************************************/

void test_push_tail() {
    dlinkedlist* list = dll_allocate_dlinkedlist(&compare_int);

    int numbers[] = {3, 2, 1};
    dll_push_tail(list, &numbers[0]);

    assert(TCMP(list->NIL->next->value, numbers[0]));
    assert(TCMP(list->NIL->previous->value, numbers[0]));

    dll_push_tail(list, &numbers[1]);
    assert(TCMP(list->NIL->next->value, numbers[0]));
    assert(TCMP(list->NIL->previous->value, numbers[1]));

    dll_push_tail(list, &numbers[2]);
    assert(TCMP(list->NIL->next->value, numbers[0]));
    assert(TCMP(list->NIL->next->next->value, numbers[1]));
    assert(TCMP(list->NIL->previous->previous->value, numbers[1]));
    assert(TCMP(list->NIL->previous->value, numbers[2]));

    dll_deallocate_dlinkedlist(&list);
    assert(list == NULL);
}

/*********************************************************
 * Test popping from the head of the list
 ********************************************************/

 void test_pop_head() {
    dlinkedlist* list = dll_allocate_dlinkedlist(&compare_int);

    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int SIZE = sizeof(numbers)/sizeof(int);

    for (int i = 0; i < SIZE; i++) {
        dll_push_head(list, &numbers[i]);
    }

    for (int i = SIZE - 1; i >= 0; i--) {
        void* value;
        assert(dll_pop_head(list, &value) == 1);
        assert(TCMP(value, numbers[i]));
    }

    for (int i = 0; i < SIZE; i++) {
        dll_push_tail(list, &numbers[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        void* value;
        assert(dll_pop_head(list, &value) == 1);
        assert(TCMP(value, numbers[i]));
    }

    dll_deallocate_dlinkedlist(&list);
    assert(list == NULL);

}

/*********************************************************
 * Test popping from the tail of the list
 ********************************************************/

void test_pop_tail() {
    dlinkedlist* list = dll_allocate_dlinkedlist(&compare_int);

    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int SIZE = sizeof(numbers)/sizeof(int);

    for (int i = 0; i < SIZE; i++) {
        dll_push_head(list, &numbers[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        void* value;
        assert(dll_pop_tail(list, &value) == 1);
        assert(TCMP(value, numbers[i]));
    }

    for (int i = 0; i < SIZE; i++) {
        dll_push_tail(list, &numbers[i]);
    }

    for (int i = SIZE-1; i >= 0; i--) {
        void* value;
        assert(dll_pop_tail(list, &value) == 1);
        assert(TCMP(value, numbers[i]));
    }

    dll_deallocate_dlinkedlist(&list);
    assert(list == NULL);
}

/*********************************************************
 * Test test searching the list for a value
 ********************************************************/

void test_search() {
    dlinkedlist* list = dll_allocate_dlinkedlist(&compare_int);

    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int SIZE = sizeof(numbers)/sizeof(int);

    for (int i = 0; i < SIZE; i++) {
        dll_push_head(list, &numbers[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        dnode* found = dll_search(list, &numbers[i]);
        assert(found != list->NIL);
        assert(TCMP(found->value, numbers[i]));
    }

    dll_deallocate_dlinkedlist(&list);
    assert(list == NULL);
}

/*********************************************************
 * Test node removal
 ********************************************************/

 void test_remove() {
    dlinkedlist* list = dll_allocate_dlinkedlist(&compare_int);

    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int SIZE = sizeof(numbers)/sizeof(int);

    for (int i = 0; i < SIZE; i++) {
        dll_push_head(list, &numbers[i]);
    }

    for (int i = 1; i < SIZE; i += 2) {
        assert(dll_remove(list, &numbers[i]));
        assert(dll_search(list, &numbers[i]) == NULL);
    }

    for (int i = 0; i < SIZE; i += 2) {
        assert(TCMP(dll_search(list, &numbers[i])->value, numbers[i]));
    }

    for (int i = 0; i < SIZE; i += 2) {
        assert(dll_remove(list, &numbers[i]));
        assert(dll_search(list, &numbers[i]) == NULL);
    }

    for (int i = 0; i < SIZE; i++) {
        assert(dll_search(list, &numbers[i]) == NULL);
    }

    assert(dll_list_is_empty(list));

    dll_deallocate_dlinkedlist(&list);
    assert(list == NULL);
}

int main(int argc, char** argv) {
    BEGIN_DECLARE_TESTS
        DECLARE_TEST(allocate_dnode)
        DECLARE_TEST(allocate_dlinkedlist)
        DECLARE_TEST(push_head)
        DECLARE_TEST(push_tail)
        DECLARE_TEST(pop_head)
        DECLARE_TEST(pop_tail)
        DECLARE_TEST(search)
        DECLARE_TEST(remove)
    END_DECLARE_TESTS

    RUN_TESTS;

    DEALLOCATE_TESTS;
}

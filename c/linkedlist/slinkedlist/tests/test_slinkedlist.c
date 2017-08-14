#include <stdlib.h>
#include "assert.h"
#include "../slinkedlist.h"
#include "../../../tharness/tharness.h"

int compare_vptr(void* lhs, void* rhs) {
         if (lhs == rhs) { return  0; }
    else if (lhs  > rhs) { return  1; }
    else                 { return -1; }
}

void test_insert() {
    slinkedlist* list = sll_allocate_list(&compare_int);

    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int SIZE = sizeof(numbers)/sizeof(int);

    // allocate them
    for (int i = 0; i < SIZE; i++) {
        sll_insert(list, &numbers[i]);
    }

    // find them by value
    for (int i = 0; i < SIZE; i++) {
        snode* x = sll_search(list, &i);
        assert(x != NULL);
        assert(*(int*)(x->value) == i);
    }

    // remove head to tail
    for (int i = (SIZE-1); i >= 0; ) {
        assert(sll_remove(list, &i));
        if (i == 0) {  assert(sll_is_empty(list));   --i; }
        else        {  --i; assert(sll_search(list, &i)); }
    }

    // make sure it's empty
    assert(sll_is_empty(list));

    // add them all back
    for (int i = 0; i < SIZE; i++) {
        sll_insert(list, &numbers[i]);
    }

    // remove tail to head
    for (int i = 0; i < SIZE; ) {
        assert(sll_remove(list, &numbers[i]));
        if (i == SIZE-1) {
            assert(sll_is_empty(list));
            ++i;
        } else {
            ++i;
            assert(sll_search(list, &numbers[i]));
        }
    }

    // add them all back
    for (int i = 0; i < SIZE; i++) {
        sll_insert(list, &numbers[i]);
    }

    assert(sll_remove(list, &numbers[0]));
    assert(!sll_search(list, &numbers[0]));
    assert(sll_remove(list, &numbers[2]));
    assert(!sll_search(list, &numbers[2]));
    assert(sll_remove(list, &numbers[4]));
    assert(!sll_search(list, &numbers[4]));
    assert(sll_remove(list, &numbers[6]));
    assert(!sll_search(list, &numbers[6]));
    assert(sll_search(list, &numbers[1]));
    assert(sll_search(list, &numbers[3]));
    assert(sll_search(list, &numbers[5]));
    assert(sll_search(list, &numbers[7]));
    assert(sll_search(list, &numbers[8]));

    sll_deallocate_list(&list);
    assert(list == NULL);
}

void test_compare_ptr() {
    slinkedlist* list = sll_allocate_list(NULL);

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // allocate them
    for (int i = 0; i < sizeof(numbers)/sizeof(int); i++) {
        sll_insert(list, &numbers[i]);
    }

    for (int i = 0; i < sizeof(numbers)/sizeof(int); i++) {
        assert((int*)sll_search(list, &numbers[i])->value == &numbers[i]);
    }


    sll_deallocate_list(&list);
    assert(list == NULL);
}

/*********************************************************
 * Buildup/Teardown
 ********************************************************/

void test_allocate() {
    slinkedlist* list = sll_allocate_list(&compare_int);

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // allocate them
    for (int i = 0; i < sizeof(numbers)/sizeof(int); i++) {
        sll_insert(list, &numbers[i]);
    }

    sll_deallocate_list(&list);
    assert(list == NULL);
}

int main(int argc, char** argv) {
    BEGIN_DECLARE_TESTS
        DECLARE_TEST(allocate)
        DECLARE_TEST(insert)
        DECLARE_TEST(compare_ptr)
    END_DECLARE_TESTS

    RUN_TESTS;

    DEALLOCATE_TESTS;
}
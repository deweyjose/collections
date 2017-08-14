#include <memory.h>
#include <stdlib.h>
#include <printf.h>
#include <assert.h>
#include "tharness.h"

/*********************************************************
 * Testing harness, this
 ********************************************************/

test_info* allocate_test(char* name, void* test_func) {
    test_info* test_info = malloc(sizeof(struct test_info));
    test_info->name = name;
    test_info->test_func = test_func;
    return test_info;
}

int test_count(test_info* tests[]) {
    return sizeof(*tests)/sizeof(test_info);
}

void deallocate_tests(test_info* tests[]) {
    for (int i = 0; i < test_count(tests); i++) {
        free(tests[i]);
    }
}

void run_test(test_info* tests[], char* test_name) {
    for (int i = 0; tests[i] != NULL; i++) {
        if (strcmp(tests[i]->name, test_name) == 0) {
            tests[i]->test_func();
            return;
        }
    }
    assert(1);
}

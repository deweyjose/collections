//
// Created by Dewey Jose on 4/18/17.
//

#ifndef COLLECTIONS_TESTING_H
#define COLLECTIONS_TESTING_H


typedef struct test_info {
    char * name;
    void (*test_func)();
} test_info;

test_info* allocate_test(char* name, void* test_func);
int test_count(test_info** tests);
void deallocate_tests(test_info* tests[]);
void run_test(test_info* tests[], char* test_name);

#define BEGIN_DECLARE_TESTS test_info* tests[] = {
#define DECLARE_TEST(TNAME) allocate_test(#TNAME, &test_ ## TNAME),
#define END_DECLARE_TESTS NULL};
#define RUN_TESTS run_test(tests, argv[1])
#define DEALLOCATE_TESTS deallocate_tests(tests)

#endif //COLLECTIONS_TESTING_H

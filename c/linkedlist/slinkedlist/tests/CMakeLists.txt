enable_testing()
add_executable(test_slinkedlist test_slinkedlist.c)
target_link_libraries(test_slinkedlist slinkedlist llcompare tharness)
add_test(allocate test_slinkedlist allocate)
add_test(insert test_slinkedlist insert)
add_test(compare_ptr test_slinkedlist compare_ptr)
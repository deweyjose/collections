//
// Created by Dewey Jose on 6/14/17.
//

#include "gtest/gtest.h"
#include "../dlinkedlist.h"

class test_class {

private:
    int test_value;

public:
    test_class() {}
    test_class(int test_value) : test_value(test_value) {}
    test_class(const test_class& ref) : test_value(ref.test_value) {}

    void set_test_value(int i)  {  test_value = i; }
    int  get_test_value() const { return test_value; }
};

TEST(DLINKEDLIST, ISEMPTY) {
    dlinkedlist<int> dlinkedlist;
    ASSERT_TRUE(dlinkedlist.isEmpty());
}

TEST(DLINKEDLIST, PUSH_FRONT) {
    dlinkedlist<int> list;

    list.push_front(99);
    ASSERT_EQ(99, *list.begin());

    list.push_front(98);
    ASSERT_EQ(98, *list.begin());
    ASSERT_EQ(99, ++(*list.begin()));
}

TEST(DLINKEDLIST, POSTPREFIX) {
    dlinkedlist<int> list;
    list.push_front(99);
    list.push_front(98);
    list.push_front(97);

    dlinkedlist<int>::iterator iter = list.begin();

    ASSERT_EQ(97, *iter);
    ASSERT_EQ(97, (*iter)++);
    ASSERT_EQ(98, *iter);
    ASSERT_EQ(99, ++(*iter));
    ASSERT_EQ(99, *iter);
}

TEST(DLINKEDLIST, ITERATOR) {
    dlinkedlist<int> list;

    for (int i = 0; i < 5; ++i) {
        list.push_front(i);
    }

    int i = 4;
    for (dlinkedlist<int>::iterator iter = list.begin(); iter != list.end(); ++iter) {
        ASSERT_EQ(i--, *iter);
    }
}

TEST(DLINKEDLIST, CONST_ITERATOR) {
    dlinkedlist<test_class> list;

    for (int i = 0; i < 5; ++i) {
        list.push_front(test_class(i));
    }

    (*list.begin()).set_test_value(99);
    ASSERT_EQ(99, (*list.cbegin()).get_test_value());
    (*list.begin()).set_test_value(4);

    int i = 4;
    for (dlinkedlist<test_class>::const_iterator citer = list.cbegin(); citer != list.cend(); ++citer) {
        ASSERT_EQ(i--, (*citer).get_test_value());
    }
}

TEST(DLINKEDLIST, SIZE) {
    dlinkedlist<test_class> list;
    for (int i = 0; i < 10; ++i) {
        list.push_front(test_class(i));
        ASSERT_EQ(i+1, list.size());
    }

    int expected_size = 10;
    while (!list.isEmpty()) {
        list.erase(list.begin());
        ASSERT_EQ(--expected_size, list.size());
    }

    ASSERT_TRUE(list.isEmpty());
}

TEST(DLINKEDLIST, ERASE) {
    dlinkedlist<test_class> list;

    list.push_front(test_class(1));
    ASSERT_EQ(1, (*list.begin()).get_test_value());
    list.erase(list.begin());
    ASSERT_TRUE(list.isEmpty());
    ASSERT_TRUE(list.begin() == list.end());

    // add 10 items to the list
    for (int i = 0; i < 10; ++i) {
        list.push_front(test_class(i));
    }

    // remove items with even numbers
    for (int i = 0; i < 10; i+=2) {
        dlinkedlist<test_class>::iterator iterator = list.begin();
        while ((*iterator).get_test_value() != i) { ++iterator; }
        list.erase(iterator);
    }

    // make sure only odd exist in the list
    for (int i = 1; i < 10; ++i) {
        dlinkedlist<test_class>::iterator iterator = list.begin();
        while ((*iterator).get_test_value() != i) { ++iterator; }

        if (i % 2 == 0) {
            ASSERT_TRUE(iterator == list.end());
        } else {
            ASSERT_TRUE(iterator != list.end());
        }
    }
}
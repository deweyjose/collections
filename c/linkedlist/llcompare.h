//
// Created by Dewey Jose on 5/9/17.
//

#ifndef COLLECTIONS_LLCOMPARE_H
#define COLLECTIONS_LLCOMPARE_H

typedef int(*comparator_func)(void*, void*);

int compare_ptr(void* lhs, void* rhs);
int compare_int(void* lhs, void* rhs);

#endif //COLLECTIONS_LLCOMPARE_H

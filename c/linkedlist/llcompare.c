//
// Created by Dewey Jose on 5/9/17.
//

#include "llcompare.h"

/*********************************************************
 * Default compart func - compare pointers
 * @param lhs
 * @param rhs
 * @return
 ********************************************************/

int compare_ptr(void* lhs, void* rhs) {
         if (lhs == rhs) { return  0; }
    else if (lhs  > rhs) { return  1; }
    else                 { return -1; }
}

/*********************************************************
 * Insert at the head position
 * Ensure we can find the insertions
 * Esnure we deallocate
 ********************************************************/

int compare_int(void* lhs, void* rhs) {
    int ilhs = *((int*)lhs);
    int irhs = *((int*)rhs);

         if (ilhs == irhs) { return  0; }
    else if (ilhs  > irhs) { return  1; }
    else                   { return -1;}

}

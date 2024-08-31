// Set <Project5.cpp>
// ECE 312 Project 5 submission by
// Walter Contreras
// Wac944
// Slip days used: <1>
// Fall 2023

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }

    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {


int i = 0; 
int j = self->len - 1;
    while (i <= j) {
        int middle = i + (j - i) / 2;
        if (self->elements[middle] == x) {
            return true;
        }
        if (self->elements[middle] < x) {
            i = middle + 1;
        } else {
            j = middle - 1;
        }
    }
    return false;


}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {



    if (isMemberSet(self, x)) {
        return;
    }
    self->elements = (int*)realloc(self->elements, (self->len + 1) * sizeof(int));
    int i = self->len - 1;
    while (i >= 0 && self->elements[i] > x) {
        self->elements[i + 1] = self->elements[i];
        i--;
    }
    self->elements[i + 1] = x;
    self->len++;


}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {

int index = -1;
    for (int i = 0; i < self->len; i++) {
        if (self->elements[i] == x) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return;
    }
    for (int i = index; i < self->len - 1; i++) {
        self->elements[i] = self->elements[i + 1];
    }
    self->elements = (int*)realloc(self->elements, (self->len - 1) * sizeof(int));
    self->len--;

}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {


 if (self->len != other->len) {
        return false;
    }
    for (int i = 0; i < self->len; i++) {
        if (self->elements[i] != other->elements[i]) {
            return false;
        }
    }
    return true;



}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
  

// int i = 0;
// int j = 0;

//     while (i < self->len && j < other->len) {
//         if (self->elements[i] < other->elements[j]) {
//             return false;
//         }
//         else if(self->elements[i] > other->elements[j]){
//             j++;
//         }
//         else{
//         j++;
//         i++ ; 
//         }
//     }

    
//     return (i ==self->len) ;
 int i = 0 ; 
 int j = 0;
    while (i < self->len && j < other->len) {
        if (self->elements[i] == other->elements[j]) {
            i++;
        }
        j++;
    }
    return i == self->len;



}


/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {

 int* Elements = (int*)malloc(self->len * sizeof(int));
    int l = 0;
    int i = 0;
    int j = 0;

    while (i < self->len && j < other->len) {
        if (self->elements[i] < other->elements[j]) {
            i++;
        } else if (self->elements[i] > other->elements[j]) {
            j++;
        } else {
            Elements[l++] = self->elements[i++];
            j++;
        }
    }

    free(self->elements);
    self->elements = Elements;
    self->len = l;
    

}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
int* Elements = (int*)malloc(self->len * sizeof(int));
    int l = 0;
    int i = 0 ;
    int j = 0;

    while (i < self->len && j < other->len) {
        if (self->elements[i] < other->elements[j]) {
            Elements[l++] = self->elements[i++];
        } else if (self->elements[i] > other->elements[j]) {
            j++;
        } else {
            i++;
            j++;
        }
    }

    while (i < self->len) {
        Elements[l++] = self->elements[i++];
    }

    free(self->elements);
    self->elements = Elements;
    self->len = l;



}





/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {

int* Elements = (int*)malloc((self->len + other->len) * sizeof(int));
    int i = 0;
    int j = 0;
    int  l = 0;

    while (i < self->len && j < other->len) {
        if (self->elements[i] < other->elements[j]) {
            Elements[l++] = self->elements[i++];
        } else if (self->elements[i] > other->elements[j]) {
            Elements[l++] = other->elements[j++];
        } else {
            Elements[l++] = self->elements[i++];
            j++;
        }
    }

    while (i < self->len) {
        Elements[l++] = self->elements[i++];
    }

    while (j < other->len) {
        Elements[l++] = other->elements[j++];
    }

    free(self->elements);
    self->elements = Elements;
    self->len = l;


}

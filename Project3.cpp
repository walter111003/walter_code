/**
 * NAME: Walter Contreras
 * EID: Wac944 
 * Spring 2024
 * Santacruz
 */

#include "UTQueue.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>

/*
 * ALREADY DONE FOR YOU
 * Prints the passed in queue to make it easy to visualize.
 */
void utqueueprint(UTQueue *src) {
  printf("[");
  for (int i = 0; i < src->size - 1; i++)
    printf("%d, ", src->data[i]);
  printf("%d]\n", src->data[src->size - 1]);
}

/*
 * Allocate a UTQueue on the heap.
 * The size of the input array is n.
 * Initialize the queue correctly by copying src
 * Return a pointer to the newly created UTQueue.
 */
  
  




UTQueue *utqueuedup(const int *src, int n) { 

UTQueue *ptr;
ptr =(UTQueue*)malloc(sizeof(UTQueue));

assert( ptr != NULL);


ptr->size = n ;  

ptr->data =(int*) malloc(n * sizeof(int)); 
  

for(int i = 0; i<n; i++){
  ptr->data[i] = src[i];

}

return ptr; 
}
/*
 * Free all memory associated with the given UTQueue.
 */



void utqueuefree(UTQueue *self) {
if(self != NULL){

free(self->data);
free(self);
}
}
/*
 * Push (enqueue) an integer "value" into the queue.
 */


UTQueue *utqueuepush(UTQueue *src, int value) {

src->size++;

//UTQueue* copy = (UTQueue*)malloc(src->size*sizeof(UTQueue));
 src->data = (int*)realloc(src->data, src->size*sizeof(int));

 assert(src->data != NULL);


src->data[(src->size)-1] = value; 

return src;




}







/*
 * Pop (dequeue) an element from the queue
 * should fail an assertion if the queue is empty
 */



int utqueuepop(UTQueue *src) {
  assert(src->size != 0); // change false to make this assertion fail only if src has 0
                 // elements.
  
int val = src->data[0]; 
  src->size--; 

  for(int i = 0; i < src->size; i++) {
        src->data[i] = src->data[i + 1];
    }

  src->data = (int*)realloc(src->data, (src->size *sizeof(int)));
  assert(src->data != NULL|| src->size == 0 );

 return val; 



}

/*
 * Reverses the queue in src.
 */


UTQueue *utqueuerev(UTQueue *src) {


int var = 0; 
for(int i = 0, j =src->size-1; i<j; i++, j--){
  var = src->data[j];
    src->data[j] = src->data[i];
    src->data[i] = var;

}

return src;



}

/*
 * combines the elements of UTQueues dst and src INTO dst.
 * src should be deleted after the combination
 */

UTQueue *utqueuecombine(UTQueue *dst, UTQueue *src) { //return NULL; 

  int ogSize = dst->size; 
  int totalSize = dst->size + src->size ; 
  dst->data = (int*)realloc(dst->data, totalSize* sizeof(int));


  assert(dst->data != NULL);

  for (int i = 0; i < src->size; i++) {
        dst->data[ogSize + i] = src->data[i]; 
    }

 
 dst->size = totalSize;

 free(src->data);


 free(src);

 return dst; 

}

/*
 * Swap the two queues.
 * q1 should "have" the contents of q2 and vice verse.
 * There is more than one way to do this
 */


void utqueueswap(UTQueue *q1, UTQueue *q2) {



  int* pt2 = q2->data; 
  int size2 = q2->size; 


q2->data = q1->data; 

q1->data = pt2; 

q2->size = q1->size; 

q1->size = size2;



}

/*
 * Copy values from src array into dst.
 * Assume dst is a valid UTQueue.
 * src is an array of numbers.
 * Do not allocate any additional storage: only copy as many numbers
 * as will actually fit into the current UTQueue dst.
 * If all of src can fit into dst, leave the remaining ints in dst.
 * return the pointer to dst with the changes.
 */



UTQueue *utqueuecpy(UTQueue *dst, const int *src, int n) { 



  if(dst->size > n){
    for(int i = 0 ; i<n; i++){
      dst->data[i] = src[i];
    }
  }

  else{
    for(int i = 0; i <dst->size; i++){
    dst->data[i] = src[i];

    }
  }

return  dst;

 }

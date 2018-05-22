/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Taylor Griffin
 * Email: griftayl@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"
#include <assert.h>

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq {
  struct dynarray* arr;
};

struct node {
  void* val;
  int pri;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq*));
  pq->arr = dynarray_create();
  return(pq);
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  dynarray_free(pq->arr);
  free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  return(dynarray_size(pq->arr)==0);
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  struct node* insert = malloc(sizeof(struct node));
  insert->val = value;
  insert->pri = priority;
  int i = dynarray_size(pq->arr);
  dynarray_insert(pq->arr,-1,insert);
  heapifyUp(pq,i);
}

void heapifyUp(struct pq* pq,int index) {
  if (index==0)
    return;
  struct node* child = dynarray_get(pq->arr,index);
  if (index%2==0) {
    struct node* parent = dynarray_get(pq->arr,(index-2)/2);
    if (child->pri < parent->pri) {
      swapNodes(child,parent);
      index=(index-2)/2;
      heapifyUp(pq,index);
    }
  }
  if (index%2==1) {
    struct node* parent = dynarray_get(pq->arr,(index-1)/2);
    if (child->pri < parent->pri) {
      swapNodes(child,parent);
      index=(index-1)/2;
      heapifyUp(pq,index);
    }
  }
}

void swapNodes(struct node* n1, struct node* n2) {
  struct node temp = *n1;
  *n1=*n2;
  *n2=temp;
}
/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  struct node* temp = dynarray_get(pq->arr,0);
  return(temp->val);
}
/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  struct node* temp = dynarray_get(pq->arr,0);
  return(temp->pri);
}
/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  if (dynarray_size(pq->arr)==0)
    return;
  struct node* lastIndex = dynarray_get(pq->arr,dynarray_size(pq->arr) - 1);
  struct node* firstIndex = dynarray_get(pq->arr,0);
  void* val = firstIndex->val;
  swapNodes(lastIndex,firstIndex);
  free(lastIndex);
  dynarray_remove(pq->arr,dynarray_size(pq->arr) - 1);
  if (dynarray_size!=0)
    heapifyDown(pq,0);
  return(val);
}

void heapifyDown(struct pq* pq, int index) {
  int leftIndex, rightIndex, minIndex;
  leftIndex=index*2+1;
  rightIndex=index*2+2;
  if (rightIndex>=dynarray_size(pq->arr)) {
    if (leftIndex>=dynarray_size(pq->arr))
      return;
    else {
      minIndex=leftIndex;
    }
  }
  else {
    struct node* rightChild = dynarray_get(pq->arr,rightIndex);
    struct node* leftChild = dynarray_get(pq->arr,leftIndex);
    if (rightChild->pri > leftChild->pri )
      minIndex=leftIndex;
    else
      minIndex=rightIndex;
    struct node* parent = dynarray_get(pq->arr,index);
    struct node* child = dynarray_get(pq->arr,minIndex);
    if (parent->pri > child->pri) {
      swapNodes(parent,child);
      index=minIndex;
      heapifyDown(pq,index);
    }
  }
}

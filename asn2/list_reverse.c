/*
 * This is the file in which you'll write a function to reverse a linked list.
 * Make sure to add your name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdio.h>

#include "list_reverse.h"

/*
 * In this function, you will be passed the head of a singly-linked list, and
 * you should reverse the linked list and return the new head.  The reversal
 * must be done in place, and you may not allocate any new memory in this
 * function.
 *
 * Params:
 *   head - the head of a singly-linked list to be reversed
 *
 * Return:
 *   Should return the new head of the reversed list.  If head is NULL, this
 *   function should return NULL.
 */
struct link* list_reverse(struct link* head) {
  //if the list is empty
  if (head==NULL)
    return(NULL);
  //if the list only has one element
  if (head->next==NULL)
    return(head);
  //if the list has more than one element
  struct link* prev;
  struct link* nex;
  struct link* temp;
  temp=head;
  nex=head->next;
  prev=temp;
  prev->next=NULL;
  while (nex->next!=NULL) {
    temp=nex;
    nex=nex->next;
    temp->next=prev;
    prev=temp;
  }
  nex->next=temp;
  head=nex;
  return(head);
}

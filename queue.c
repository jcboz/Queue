/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    /* What if malloc returned NULL? */
    
    queue_t *q = (queue_t*)(malloc(sizeof(queue_t)));
    if (q == NULL){
       return NULL;
    }
    q->head = NULL;

    q->size = 0;
    q->tail = NULL;

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL){
        return;
    }

    list_ele_t *curr;
    list_ele_t *tmp;
    curr = q->head;

    while (curr != NULL)            //loops through each linked list element and frees the memory of it
    {
        tmp = curr;
        free(curr->value);
        curr = curr->next;
        free(tmp);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *str = s;
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }

    str = malloc(sizeof(char) * strlen(s) + 1);   // +1 for '\0'
    newh = malloc(sizeof(list_ele_t));

    if (str == NULL || newh == NULL) {
        if (newh != NULL) {
            free(newh);
        }
        if (str != NULL) {
            free(str);
        }
        return false;
    }
    strcpy(str, s);
    newh->value = str;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    q->size = (q->size)+1;
    if (q->tail == NULL) {
        q->tail = newh;
    }
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    list_ele_t *newt;
    char *str = s;

    if (q == NULL) {
        return false;
    }

    str = malloc(sizeof(char) * strlen(s) + 1);   // +1 for '\0'
    newt = malloc(sizeof(list_ele_t));

    if (str == NULL || newt == NULL) {
        if (newt != NULL) {
            free(newt);
        }
        if (str != NULL) {
            free(str);
        }
        return false;
    }
    strcpy(str, s);
    newt->value = str;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    q->size = (q->size) + 1;
    newt->next = NULL;

    if (q->tail == NULL) {
        q->head = newt;
    } else {
        q->tail->next = newt;
    }
    q->tail = newt;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */

    list_ele_t *tmp;
    
    if (q == NULL) {
        return false;
    }

    if (sp == NULL) {
        return false;
    }

    if (q->head == NULL) {                   //checks if empty
        return false;
    }

    strncpy(sp, (q->head->value), bufsize);
    
    (*(sp + (bufsize-1))) = 0;              //adds null terminator

    tmp = q->head->next;
    free(q->head->value);
    free(q->head);
    q->head = tmp;
    q->size = (q->size)-1;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL) {
        return 0;
    }
    if (q->head == NULL) {
        return 0;
    }
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */

        if (q == NULL) {            //case to test if linked list is empty
            return;
        }
        if (q->head == NULL) {      // case to test if there is no head meaning no start to linked list
            return;
        }

        list_ele_t *prev;           // This creates and sets a previous pointer that is equal to NULL
        prev = NULL;

        list_ele_t *curr;           // Creates a current pointer that points at head of linked list
        curr = (q->head);

        list_ele_t *tmp;            // Creates a temporary pointer that points to NULL
        tmp = NULL;

        q->tail = q->head;          // This line sets the tail pointer now to where head is 


        while (curr != NULL) {      // sets a previous pointer that lags behind by a position. Sets next pointer equal to previous. 
            tmp = curr->next;       
            curr->next = prev;      
            prev = curr;            
            curr = tmp;             
        }
        q->head = prev;             // This sets the head pointer equal to the now front of the linked list so it is reversed
}


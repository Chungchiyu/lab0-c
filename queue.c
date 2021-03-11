#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q) {
        return NULL;
    }
    q->head = NULL;
    // q->head->next = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;

    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }

    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* TODO: What should you do if the q is NULL? */
    if (!q)
        return false;

    int value_size = strlen(s) + 1;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t) + value_size);

    if (!newh)
        return false;

    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    newh->next = q->head;
    q->head = newh;

    if (q->size == 0)
        q->tail = newh;
    q->head->size = value_size - 1;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q)
        return false;

    int value_size = strlen(s) + 1;

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t) + value_size);

    if (!newt)
        return false;

    if (!q->head)
        q_insert_head(q, s);
    else {
        newt->next = q->tail->next;
        q->tail->next = newt;
        q->tail = newt;
        q->size++;
        q->head->size = value_size - 1;
    }

    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return false;

    if (sp) {
        size_t copySize = (bufsize - 1 > strlen(q->head->value))
                              ? strlen(q->head->value)
                              : bufsize - 1;
        sp[copySize] = '\0';
        strncpy(sp, q->head->value, copySize);
    }

    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    q->size--;

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return 0;

    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || q->size < 2)
        return;

    list_ele_t *prev = NULL, *now = q->head, *next = NULL;

    while (now != NULL) {
        next = now->next;
        now->next = prev;
        prev = now;
        now = next;
    }
    q->tail = q->head;
    q->head = prev;

    return;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || q->size < 2)
        return;

    mergeSort(&(q->head));

    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}

void mergeSort(list_ele_t **head)
{
    if (!(*head) || !(*head)->next)
        return;

    list_ele_t *fast = (*head)->next;
    list_ele_t *slow = *head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;
    slow = (*head);

    mergeSort(&slow);
    mergeSort(&fast);

    (*head) = NULL;
    list_ele_t **ptr = head;
    (*head)->next = (*ptr);

    while (slow && fast) {
        int compare = strcasecmp(slow->value, fast->value);
        if (compare == 0 ? strcmp(slow->value, fast->value) < 0 : compare < 0) {
            (*ptr)->next = slow;
            slow = slow->next;
        } else {
            (*ptr)->next = fast;
            fast = fast->next;
        }
        (*ptr) = (*ptr)->next;
    }

    if (slow)
        (*ptr)->next = slow;
    if (fast)
        (*ptr)->next = fast;

    (*head) = (*head)->next;
}

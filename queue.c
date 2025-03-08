#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *tmp = malloc(sizeof(struct list_head));
    if (!tmp) {
        return NULL;
    }
    INIT_LIST_HEAD(tmp);
    return tmp;
}


/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (head) {
        if (!list_empty(head)) {
            element_t *safe;
            element_t *entry;
            list_for_each_entry_safe(entry, safe, head, list)
                q_release_element(entry);
        }
        free(head);
    }
}


/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;
    element_t *tmp = malloc(sizeof(element_t));
    if (!tmp)
        return false;
    tmp->value =
        strdup(s);  // It returns NULL if insufficient memory was available.
    if (!tmp->value) {
        free(tmp);
        return false;
    }
    list_add(&tmp->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;
    element_t *tmp = malloc(sizeof(element_t));
    if (!tmp)
        return false;
    tmp->value =
        strdup(s);  // It returns NULL if insufficient memory was available.
    if (!tmp->value) {
        free(tmp);
        return false;
    }
    list_add_tail(&tmp->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (head) {
        if (!list_empty(head)) {
            element_t *removed = list_first_entry(head, element_t, list);
            list_del(&removed->list);
            if ((removed->value) && sp) {
                strncpy(sp, removed->value, bufsize);
                sp[bufsize - 1] = '\0';
            }
            return removed;
        }
    }
    return NULL;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (head) {
        if (!list_empty(head)) {
            element_t *removed = list_last_entry(head, element_t, list);
            list_del(&removed->list);
            if ((removed->value) && sp) {
                strncpy(sp, removed->value, bufsize);
                sp[bufsize - 1] = '\0';
            }
            return removed;
        }
    }
    return NULL;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;
    int len = 0;
    struct list_head *li;
    list_for_each(li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}

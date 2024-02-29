#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */
/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *temp = malloc(sizeof(struct list_head));
    if (!temp) {
        return NULL;
    }
    INIT_LIST_HEAD(temp);
    return temp;  //?????
}


/* Free all storage used by queue */
void q_free(struct list_head *l)
{  // don't delete l
    if (!l)
        return;
    element_t *safe;
    element_t *entry;
    if (!list_empty(l)) {
        free(l);
        return;
    }
    // the type of list_head is struct list_head not element
    list_for_each_entry_safe (entry, safe, l, list) {
        // list_del_init(&(entry->list));
        q_release_element(entry);
    }
    free(l);  // thanks
}


/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;
    element_t *temp = malloc(sizeof(element_t));
    if (!temp) {
        return false;
    }
    temp->value = strdup(s);
    if (!temp->value) {
        free(temp);
        return false;
    }
    INIT_LIST_HEAD(&temp->list);
    list_add(&temp->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;
    element_t *temp = malloc(sizeof(element_t));
    if (!temp)
        return false;
    temp->value = strdup(s);
    if (!temp->value) {
        free(temp);


        return false;
    }
    INIT_LIST_HEAD(&temp->list);
    list_add_tail(&temp->list, head);
    return true;
}


/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head,
                         char *sp,
                         size_t bufsize)  // size_t=> unsigned integer
{
    if (!head || list_empty(head))
        return NULL;
    // struct list_head *temp = head->next;
    // if (!temp)
    //     return NULL;  // empty
    // element_t *removed = list_entry(temp, element_t, list);
    element_t *removed = list_first_entry(head, element_t, list);
    if (removed) {
        list_del_init(&(removed->list));
        if ((removed->value) && sp) {
            strncpy(sp, removed->value, (bufsize - 1));
        }
        return removed;
    }
    return NULL;
}


/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *removed = list_last_entry(head, element_t, list);
    if (removed) {
        list_del_init(&(removed->list));
        if ((removed->value) && sp) {
            strncpy(sp, removed->value, (bufsize - 1));
        }
        return removed;
    }
    return NULL;
}


/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head))
        return 0;


    int len = 0;
    struct list_head *li;


    list_for_each (li, head)
        len++;
    return len;
}



/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head || list_empty(head))
        return false;
    struct list_head *node;
    struct list_head *safe;
    struct list_head *rev_node = head->prev;
    /*delete !=> free*/
    list_for_each_safe (node, safe, head) {
        if ((node == rev_node || node->next == rev_node) && rev_node != head) {
            list_del_init(rev_node);
            q_release_element(list_entry(rev_node, element_t, list));
            return true;
        }
        rev_node = rev_node->prev;
    }
    return false;
}


/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    if (!head)
        return false;
    element_t *entry;
    element_t *safe;
    list_for_each_entry_safe (entry, safe, head, list) {
        // printf("entry now=%s\n",entry->value);
        if (entry->list.next != head &&
            !strcmp(entry->value,
                    list_entry(entry->list.next, element_t, list)->value)) {
            while (

                !strcmp(entry->value,
                        list_entry(entry->list.next, element_t, list)->value)) {
                element_t *Next = list_entry(entry->list.next, element_t, list);
                list_del(&Next->list);
                q_release_element(Next);
                // printf("ee\n");
            }
            if (list_entry(entry->list.next, element_t, list) != safe) {
                safe = list_entry(entry->list.next, element_t, list);
                list_del_init(&entry->list);
                q_release_element(entry);
            }
        }
    }
    return true;
}



/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    if (!head || list_empty(head))
        return;
    struct list_head *node;
    list_for_each (node, head) {
        q_reverseK(node, 2);
    }
}


/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    // thanks yanjiew1
    if (!head || list_empty(head))
        return;
    struct list_head *node;
    struct list_head *safe;
    list_for_each_safe (node, safe, head) {
        list_move(node, head);
    }
}


/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    if (!head || list_empty(head) || k == 1)
        return;
    struct list_head *node;
    struct list_head *safe;
    int i = k;
    struct list_head *new_head = head;
    list_for_each_safe (node, safe, head) {
        if (!i--) {
            new_head = node->prev;
            // printf("new_head=%s\n",
            // list_entry(new_head, element_t, list)->value);
            i = k - 1;
        }
        list_move(node, new_head);
        // printf("%d move %s \n", i,list_entry(node, element_t, list)->value);
    }
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
/* the right side of it */
int q_descend(struct list_head *head)
{
    if (!head || list_empty(head))
        return 0;
    if (list_is_singular(head))
        return 1;
    element_t *entry;
    element_t *safe;
    element_t *min = list_last_entry(head, element_t, list);
    int i = 0;
    for (entry = list_entry(head->prev, element_t, list),
        safe = list_entry(entry->list.prev, __typeof__(*entry), list);
         &entry->list != (head); entry = safe,
        safe = list_entry(safe->list.prev, __typeof__(*entry), list)) {
        // printf("node =%s \n", entry->value);
        if (strcmp(entry->value, min->value) < 0) {
            // printf("delete %s \n", entry->value);
            list_del(&entry->list);
            q_release_element(entry);
        } else {
            min = entry;
            i++;
        }
    }
    return i;
}


/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}

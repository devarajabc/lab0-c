#include "worst_case.h"

void worst_case(struct list_head *head)
{
    if (q_size(head) < 2)
        return;
    LIST_HEAD(even);
    LIST_HEAD(odd);
    struct list_head *node;
    struct list_head *safe;
    int index = 0;
    list_for_each_safe (node, safe, head) {
        if ((index++) % 2 == 0)
            list_move_tail(node, &even);
        else
            list_move_tail(node, &odd);
    }
    worst_case(&even);
    worst_case(&odd);
    // merge
    list_splice_tail_init(&odd, &even);
    list_splice(&even, head);
}

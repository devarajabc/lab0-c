#include <stdio.h>
#include "list.h"
#include "queue.h"

typedef int
    __attribute__((nonnull(2, 3))) (*list_cmp_func_t)(void *priv,
                                                      struct list_head *,
                                                      struct list_head *);
void worst_case(struct list_head *head);
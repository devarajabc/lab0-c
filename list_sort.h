#include "list.h"

typedef int
    __attribute__((nonnull(2, 3))) (*list_cmp_func_t)(void *priv,
                                                      struct list_head *,
                                                      struct list_head *);

__attribute__((nonnull(1, 2))) void list_sort(void *priv,
                                              struct list_head *head,
                                              list_cmp_func_t cmp);
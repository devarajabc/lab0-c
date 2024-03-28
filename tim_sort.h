#include "list.h"

typedef int
    __attribute__((nonnull(2, 3))) (*list_cmp_func_t)(void *priv,
                                                      const struct list_head *,
                                                      const struct list_head *);

void timsort(void *priv, struct list_head *head, list_cmp_func_t cmp);
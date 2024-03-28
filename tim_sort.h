#include "list.h"
#include "queue.h"
typedef int
    __attribute__((nonnull(2, 3))) (*list_cmp_func_t)(void *priv,
                                                      struct list_head *,
                                                      struct list_head *);

void timsort(void *priv, struct list_head *head, list_cmp_func_t cmp);

#ifndef CLZ
/* clang-only */
#ifndef __has_builtin
#define __has_builtin(x) 0
#endif
#if __has_builtin(__builtin_clzll) || \
    (defined(__GNUC__) &&             \
     ((__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || (__GNUC__ > 3)))
#define CLZ __builtin_clzll
#else

static int clzll(uint64_t);

/* adapted from Hacker's Delight */
static int clzll(uint64_t x)
{
    int n;

    if (x == 0) {
        return 64;
    }

    n = 0;

    if (x <= 0x00000000FFFFFFFFL) {
        n = n + 32;
        x = x << 32;
    }

    if (x <= 0x0000FFFFFFFFFFFFL) {
        n = n + 16;
        x = x << 16;
    }

    if (x <= 0x00FFFFFFFFFFFFFFL) {
        n = n + 8;
        x = x << 8;
    }

    if (x <= 0x0FFFFFFFFFFFFFFFL) {
        n = n + 4;
        x = x << 4;
    }

    if (x <= 0x3FFFFFFFFFFFFFFFL) {
        n = n + 2;
        x = x << 2;
    }

    if (x <= 0x7FFFFFFFFFFFFFFFL) {
        n = n + 1;
    }

    return n;
}

#define CLZ clzll
#endif
#endif

#ifndef MAX
#define MAX(x, y) (((x) > (y) ? (x) : (y)))
#endif

#ifndef MIN
#define MIN(x, y) (((x) < (y) ? (x) : (y)))
#endif
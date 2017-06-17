#include <stdlib.h>
#include <stdint.h>

unsigned char zm_pool[4];

void *zm_malloc(size_t size)
{
    return zm_pool;
}

void zm_free(void *ptr)
{
    return;
}

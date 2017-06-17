#include <stdlib.h>
#include <stdint.h>

#include "zmpool.h"
#include "zmpool_i.h"

unsigned char zm_pool[POOL_BLOCK_SIZE * POOL_SIZE];

void *zm_malloc(size_t size)
{
    static uint32_t used = 0;
    void *p = NULL;

    if(size == 0 || size > POOL_BLOCK_SIZE)
        return (void *)NULL;

    if(used < POOL_SIZE)
        p = (void *) &zm_pool[used++ * POOL_BLOCK_SIZE];

    return p;
}

void zm_free(void *ptr)
{
    return;
}

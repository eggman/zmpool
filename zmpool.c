#include <stdlib.h>
#include <stdint.h>

#include "zmpool.h"
#include "zmpool_i.h"

unsigned char zm_pool[POOL_BLOCK_SIZE * POOL_SIZE];

static uint32_t used = 0;
static uint8_t blocks[POOL_SIZE] = {0};

#define ZERO 0

void zm_init(void)
{
    uint32_t used = 0;

    for(uint32_t i=0; i<POOL_SIZE; i++)
    {
        blocks[i] = ZERO;
    }
}

void *zm_malloc(size_t size)
{
    void *p = NULL;

    if(   size == 0
       || size > POOL_BLOCK_SIZE
       || used >= POOL_SIZE)
        return (void *)NULL;

    for(uint32_t i=0 ; i<POOL_SIZE; i++)
    {
        if(blocks[i] == ZERO)
        {
            p = (void *) &zm_pool[i * POOL_BLOCK_SIZE];
            blocks[i] = 1;
            used++;
            break;
        }
    }

    return p;
}

void zm_free(void *ptr)
{
    uint32_t i = ((void *)ptr - (void *)zm_pool)/POOL_BLOCK_SIZE;

    if(ptr == &zm_pool[i * POOL_BLOCK_SIZE] &&
       blocks[i])
    {
        blocks[i] = ZERO;
        used--;
    }
    return;
}

uint32_t zm_stat(void)
{
     return used;
}

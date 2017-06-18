#include <stdlib.h>
#include <stdint.h>

#include "zmpool.h"
#include "zmpool_i.h"

#define ZERO 0

unsigned char zm_pool[POOL_BLOCK_SIZE * POOL_SIZE];

static uint32_t used = 0;

typedef struct zm_block {
    uint32_t block_size;
    struct zm_block *next;
} zm_block;

zm_block zm_blocks[POOL_SIZE];
zm_block *_free_block_ptr;
zm_block *_free_block_ptr_end;

void zm_init(void)
{
    uint32_t used = 0;

    for(uint32_t i=0; i<POOL_SIZE; i++)
    {
        zm_block *block = &zm_blocks[i];

        if(i != 0)
        {
	    zm_blocks[i-1].next = block;
        }

        block->block_size = 0;
    }
    zm_blocks[POOL_SIZE-1].next = 0;

    _free_block_ptr = &zm_blocks[0];
    _free_block_ptr_end = &zm_blocks[POOL_SIZE-1];
}

void *zm_malloc(size_t size)
{
    void *p = NULL;

    if(   size == 0
       || size > POOL_BLOCK_SIZE
       || used >= POOL_SIZE)
        return (void *)NULL;

    if(!_free_block_ptr)
        return (void *)NULL;

    zm_block *should_return = _free_block_ptr;
    _free_block_ptr = _free_block_ptr->next;

    if(_free_block_ptr == _free_block_ptr_end)
    {
        _free_block_ptr_end = 0;
    }

    used++;
    should_return->block_size = size;

    return (void *) &zm_pool[POOL_BLOCK_SIZE * (should_return - zm_blocks)];
}

void zm_free(void *ptr)
{
    uint64_t i;

    if( ptr < (void *) zm_pool || (void *) &zm_pool[POOL_SIZE*POOL_BLOCK_SIZE -1] < ptr)
        return;

    i = ((uint64_t) ptr - (uint64_t) zm_pool) / POOL_BLOCK_SIZE;

    if(i < POOL_SIZE &&
       zm_blocks[i].block_size)
    {
        zm_blocks[i].block_size = ZERO;
        used--;

        if(_free_block_ptr && _free_block_ptr_end)
        {
            _free_block_ptr_end->next = &zm_blocks[i];
            _free_block_ptr_end = &zm_blocks[i];
        }
        else
        {
            _free_block_ptr = _free_block_ptr_end = &zm_blocks[i];
        }
    }
    return;
}

uint32_t zm_stat(void)
{
     return used;
}

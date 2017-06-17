#include <stdio.h>
#include <stdint.h>
#include "zmpool.h"
#include "zmpool_i.h"

void is_null(void *p)
{
    if(p == NULL)
        printf("pass\n");
    else
        printf("fail\n");
}

void is_notnull(void *p)
{
    if(p != NULL)
        printf("pass\n");
    else
        printf("fail\n");
}

void is_zero(int i)
{
   if(i == 0)
        printf("pass\n");
   else
        printf("fail\n");

}

void is_one(int i)
{
   if(i == 1)
        printf("pass\n");
   else
        printf("fail\n");

}

int main(void)
{
   int *p = NULL;

   zm_init();

   p = zm_malloc(sizeof(int));
   is_notnull(p);

   *p = 1;
   is_one(*p);

   p = zm_malloc(0);
   is_null(p);

   p = zm_malloc(POOL_BLOCK_SIZE + 1);
   is_null(p);

   for(uint32_t i=1; i<POOL_SIZE; i++)
   {
      p = zm_malloc(sizeof(int));
      zm_free(p);
   }
   is_one(zm_stat());
   printf("used: %d\n",zm_stat());

   for(uint32_t i=0; i<POOL_SIZE; i++)
      p = zm_malloc(sizeof(int));

   is_null(p);
   printf("used: %d\n",zm_stat());

   zm_free(p);
   p = NULL;

   return 0;
}


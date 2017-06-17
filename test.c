#include <stdio.h>
#include <stdint.h>
#include "zmpool.h"
#include "zmpool_i.h"

int main(void)
{
   int *p = NULL;

   p = zm_malloc(sizeof(int));

   if(p != NULL)
     printf("pass\n");
   else
     printf("fail\n");

   *p = 1;

   if(*p == 1)
     printf("pass\n");
   else
     printf("fail\n");

   for(uint32_t i=0; i<POOL_SIZE; i++)
      p = zm_malloc(sizeof(int));

   if(p == NULL)
     printf("pass\n");
   else
     printf("fail\n");

   zm_free(p);
   p = NULL;

   return 0;
}


#include <stdio.h>
#include "zmpool.h"

int main(void)
{
   int *p = NULL;

   p = zm_malloc(sizeof(int));

   if(p == NULL)
     printf("pass¥n");
   else
     printf("fail¥n");

   zm_free(p);
   return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include "sar.h"

int main (int argc, char** argv)
{
  unsigned int u,v;
  
  u = 0;
  v = 0;
  while(scanf("%x %u\n", &u, &v) >= 2){
    
    printf("0x%.8x\n", shift_algebraic_right(u, v));
    u = 0;
    v = 0;
  }
	
  return 0;
}

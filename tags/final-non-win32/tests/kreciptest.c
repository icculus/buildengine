#include <stdlib.h>
#include <stdio.h>
#include "sar.h"

/*extern int _asm_krecipasm (int);*/
int reciptable[2048], fpuasm;
void init (void)
{
  int i;
  for(i=0;i<2048;i++) reciptable[i] = i;/* divscale30(2048L,i+2048);*/
}

static int krecipasm(int i1)
{
  int retval;
  __asm__ __volatile__ ("
    call _asm_krecipasm
           " : "=a" (retval) : "a" (i1)
			: "cc", "ebx", "ecx", "memory");
  return(retval);
} // krecipasm

static int ansi_c_krecip (int x)
{
  float xf;
  int z;
  int not;

  if (x & 0x80000000) /* If the highest bit is set... */
    not = 0x0FFFFFFFF;
  else
    not = 0;
  
  xf = (float)x;/* convert the int to a float */

  /* Pretend the float is an int so we can extract bits */
  x = *((int*)(&xf));
  z = x;
  
  x = x & 0x007FF000;/* Mask out: 11 << 13 */
  x = x >> 10;       /* Divide x by 1024 */
  /* X now contains: 13 high order bits of the mantissa, followed by two 0 bits */

  /* Now we perform an elaborate extraction
     of the exponent from the floating point
     numer? WTF is the subtraction for? */
  z = z - 0x03F800000;/* Subtract (127<<23) */
  z = z >> 23;

  /* z now contains the exponent divided by two?  */
  x = shift_algebraic_right(reciptable[(x>>2)], z) ^ not;
  return x;
}

static int mykrecipasm(int i1)
{
  int retval;
  retval = ansi_c_krecip(i1);
  return retval;
}

int main (int argc, char** argv)
{
  int u;

  init();
  printf("sizeof(long) = %u, sizeof(int) = %u\n",
	 sizeof(long int), sizeof(int));
 
  u = 0;
  while(scanf("%d", &u) >= 1){    
    printf("Original: %d \tMine: %d\n", 
	   krecipasm(u),mykrecipasm(u));
    u = 0;
  }
  
  return 0;
}

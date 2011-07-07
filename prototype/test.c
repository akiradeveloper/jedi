/*
 * check if C language hold any value in form of void* type.
 *
 * The result seems OK.
 * 20110707 19:07 akira
 */

#include <stdio.h>
#include <limits.h>

int main(void){
  printf("%d\n", __INT_MAX__);
  long long x = __LONG_MAX__ + 1;
  char* _x = x;
  long __x = _x;
  printf("%d\n", sizeof(_x)); // 8 bytes
  printf("%d\n", sizeof( long long int));
  printf("%d\n", sizeof( void* ));
  printf("%d\n", sizeof( char* ));
  printf("%ld\n", __x);
  return 0;
}

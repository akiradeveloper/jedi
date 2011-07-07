#include <stdio.h>

struct type {
  int n; 
  void print(void) {
    printf("n=%d\n", n);
  }
};

int main(void){
  struct type x; x.n = 777;
  x.print(void);
  return 0;
}

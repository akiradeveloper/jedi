struct type {
  int x;
};

int main(void){
  int y = (struct type).x;
  return 0;
}


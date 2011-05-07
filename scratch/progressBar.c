#include <stdio.h>

int main() {

  int i = 0;

  while(1) {
    printf("foodlydoo\n");

    printf("i is %d\r", i);
    fflush(stdout);

    printf("\033[2K");
    i++;
  }

}

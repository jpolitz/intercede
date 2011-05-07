#include <stdio.h>

int main() {

  int i = 0;

  while(1) {
    printf("i is %d\r", i);
    fflush(stdout);
    usleep(1000000);

    printf("\033[2K");
    i++;
  }

}

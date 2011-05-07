#include <stdio.h>

char* buf;

static void setBuf(char* newBuf) {
  buf = newBuf;
}

static int print_quoted_wrapper(stream, opts, is_tty, str, path) {
  printf("\033[2K");
  int ret = print_quoted(stream, opts, is_tty, str, path);
  printf("%s\r", buf);
  fflush(stdout);
  return ret;
}

static int print_status() {
  printf("\033[2K");
  printf("%s\r", buf);
  fflush(stdout);
  return 0;
}

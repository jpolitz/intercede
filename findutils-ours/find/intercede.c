#include <stdio.h>
#include <printquoted.h>

// Help came from:
// http://ramprasadk.wordpress.com/2010/06/09/c-programming-linux-color-text-output/
#define _intercede_highlight "\033[7;30m"
#define _intercede_clear "\033[0m"

char* buf;
static int dirIndex;

static void setBuf(char* newBuf) {
  buf = newBuf;
}

static int print_quoted_wrapper(FILE *stream, 
				struct quoting_options *opts, 
				boolean is_tty, 
				const char *str, 
				const char *path) {
  printf("\033[2K");
  int ret = print_quoted(stream, opts, is_tty, str, path);
  printf("%s\r", buf);
  fflush(stdout);
  return ret;
}

static int print_status() {
  printf("\033[2K");
  printf("%s%s%s\r", _intercede_highlight, buf, _intercede_clear);
  fflush(stdout);
  return 0;
}

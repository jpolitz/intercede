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
  dirIndex = 22;
}

// We measure by blocks between slashes... how accurate is this?
static int depth(char *path) {
  int len = strlen(path);
  int slashes = 0;

  for(int i = 0; i < len; i++) {
    fflush(stdout);
    if(path[i] == '/') {
      slashes++;
    }
  }

  //  printf("%d slashes\n", slashes);
  return slashes;
}

static int getIndex(char *path, int index) {
  int d = depth(path);
  if (index > (d - 1)) { return d - 1; }
  return index;
}

// Print the path with the chunk indicated by index highlighted.
// Don't highlight the bit after the last slash if index is greater than
// the number of pieces of the path --- highlight the second to last one

// print_with_highlight("/a/b/c", 0) --> "/<a>/b/c"
// print_with_highlight("/a/b/c", 1) --> "/a/<b>/c"
// print_with_highlight("/a/b/c", 55) --> "/a/<b>/c"

static int print_with_highlight(char *path, int index) {
  int d = depth(path);
  int ix = getIndex(path, index);
  int found = 0;
  int slashIndex = 0;
  int offsetFirst = 0, offsetLast = 0;
  char *pathIndex = path;
  char *restIndex = path;

  if(d < 2) {
    fflush(stdout);

    printf("%s\r", path);
    return 0;
  }

  //  printf("%s, index is %d\n", path, ix);
  fflush(stdout);

  while(ix >= found + 1) {
    pathIndex = strchr(pathIndex, '/');
    //    printf("path: %s\n", pathIndex);
    pathIndex++;
    found++;
  }

  //  printf("%s is the rest\n", pathIndex);
  fflush(stdout);

  restIndex = strchr(pathIndex, '/');

  offsetFirst = strlen(path) - strlen(pathIndex);
  offsetLast = strlen(path) - strlen(restIndex);

  //  printf("offsetFirst = %d\n", offsetFirst);
  //  printf("offsetLast = %d\n", offsetLast);

  char beforeHighlight[offsetFirst + 1];
  char highlight[offsetLast - offsetFirst + 1];
  char afterHighlight[strlen(path) - offsetLast + 1];
  beforeHighlight[offsetFirst] = '\0';
  highlight[offsetLast - offsetFirst] = '\0';
  afterHighlight[strlen(path) - offsetLast] = '\0';

  strncpy(beforeHighlight, path, offsetFirst);
  strncpy(highlight, pathIndex, offsetLast - offsetFirst);
  strncpy(afterHighlight, restIndex, strlen(path) - offsetLast);

  /*  printf("before: %s\n", beforeHighlight);
  printf("high: %s\n", highlight);
  printf("after: %s\n", afterHighlight); */

  printf("%s%s%s%s%s\r", 
	 beforeHighlight, 
	 _intercede_highlight, 
	 highlight, 
	 _intercede_clear, 
	 afterHighlight); 
}

static int print_status() {
  printf("\033[2K");
  fflush(stdout);
  print_with_highlight(buf, dirIndex);
  fflush(stdout);
  return 0;
}

static int print_quoted_wrapper(FILE *stream, 
				struct quoting_options *opts, 
				boolean is_tty, 
				const char *str, 
				const char *path) {
  printf("\033[2K");
  int ret = print_quoted(stream, opts, is_tty, str, path);
  print_status();
  return ret;
}


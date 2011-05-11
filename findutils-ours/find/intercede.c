#include <stdio.h>
#include <printquoted.h>
#include <pthread.h>
#include <termios.h>
#include <sys/ioctl.h>

// Help came from:
// http://ramprasadk.wordpress.com/2010/06/09/c-programming-linux-color-text-output/
#define _intercede_highlight "\033[7;30m"
#define _intercede_clear "\033[0m"


pthread_t event_thread;


// Buffer that points to the current pathname to print
char* buf;
// Which chunk of the pathname should be highlighted right now
int dirIndex;
int targetIndex;

static void setIndex(int newIx) {
  dirIndex = newIx;
}

static void setBuf(char* newBuf) {
  buf = newBuf;
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

static boolean poppingItUp() {
  if(targetIndex == -1) {
    return false;
  }
  if(depth(buf) > targetIndex) {
    return true;
  }
  targetIndex = -1;
  return false;
}


static int getIndex(char *path, int index) {
  int d = depth(path);
  if (index > (d - 1)) { return d - 1; }
  return index;
}

static int incrementIndex() {
  int newIx = getIndex(buf, dirIndex + 1);
  //printf("Updating ix to %d", newIx);
  fflush(stdout);
  dirIndex = newIx;
}

static int decrementIndex() {
  int newIx = dirIndex - 1;
  if (newIx < 0) {
    dirIndex = 0;
  }
  dirIndex = getIndex(buf, newIx);
}

struct termios savedOptions;

// Help from pianobar here
static void makeInputUnbuffered() {
  struct termios terminalOptions;
  tcgetattr (fileno (stdin), &terminalOptions);
  tcgetattr (fileno (stdin), &savedOptions);
  terminalOptions.c_lflag &= ~ICANON;
  terminalOptions.c_lflag &= ~ECHO;
  setvbuf (stdin, NULL, _IONBF, 1);
  tcsetattr(fileno (stdin), TCSANOW, &terminalOptions);
}

static void cleanupTerminal() {
  tcsetattr(fileno (stdin), TCSANOW, &savedOptions);
}

static void get_event(int *dirIx /* unused */) {
  fd_set set;
  char inChr;
  FD_ZERO(&set);
  FD_SET(0, &set);
  ssize_t chrs = 0;
  makeInputUnbuffered();

  printf("GetEvent called\n");
  while(1) {
    if(select(1, &set, NULL, NULL, NULL) <= 0) {
      fprintf(stderr, "Intercede: Terrible things happened waiting for input\n");
      fflush(stderr);
      break;
    }
    if((chrs = read(0, &inChr, sizeof(inChr))) <= 0) {
      //fprintf(stderr, "Intercede: Terrible things happened reading input: %d\n", chrs);
      continue;      
    }
    //printf("DirIndex: %d\n", dirIndex);
    fflush(stdout);
    if(inChr == 'l' || inChr == 'k') {
      incrementIndex();
    }
    else if(inChr == 'h' || inChr == 'j') {
      decrementIndex();
    }
    else if(inChr == 'x') {
      targetIndex = dirIndex;
    }
    //printf("got: %c\n", inChr);
    fflush(stdout);
  }
  printf("Exited loop\n");
  fflush(stdout);
}

static void init_events() {
  printf("Printing with dirIndex: %d, %d\n", &dirIndex, dirIndex);
  dirIndex = 2;
  targetIndex = -1;
  printf("Printing with dirIndex: %d, %d\n", &dirIndex, dirIndex);  
  printf("Initting events\n");
  if(pthread_create(&event_thread, NULL, &get_event, (void *)(&dirIndex)) != 0) {
    fprintf(stderr, "Intercede: couldn't create listener thread");
    exit(1);
  }
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

  /** Check the terminal size to make sure that we will get our 
      carriage return in, and not cause odd output */
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  unsigned short cols = w.ws_col;
  char outstr[cols];
  snprintf(outstr, (size_t) (cols - 1), "%s%s%s%s%s", 
           beforeHighlight, 
           _intercede_highlight, 
           highlight, 
           _intercede_clear, 
           afterHighlight);
  strcat(outstr, "\r");
  printf(outstr);
  /*
  printf("%s%s%s%s%s\r", 
	 beforeHighlight, 
	 _intercede_highlight, 
	 highlight, 
	 _intercede_clear, 
	 afterHighlight); */
  fflush(stdout);
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



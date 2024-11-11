#include <errno.h>
#include <fcntl.h> // For open() and creat()
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char *progname;

int main(int argc, char *argv[]) {
  int fd;
  struct stat stbuf;
  time_t old_time = 0;

  progname = argv[0];
  if (argc < 2) {
    fprintf(stderr, "Usage: %s filename [cmd]", progname);
    exit(EXIT_FAILURE);
  }
  if ((fd = open(argv[1], O_RDONLY)) == -1) {
    fprintf(stderr, "cant open %s", argv[1]);
    exit(EXIT_FAILURE);
  }
  fstat(fd, &stbuf); // file descriptor with open
  while (stbuf.st_mtime != old_time) {
    old_time = stbuf.st_mtime;
    sleep(15);
    fstat(fd, &stbuf);
  }

  if (argc == 2) {
    execlp("cat", "cat", argv[1], (char *)0);
    fprintf(stderr, "cant copy %s", argv[1]);
    exit(EXIT_FAILURE);
  } else {
    execvp(argv[2], &argv[2]);
    fprintf(stderr, "cant execute %s", argv[2]);
    exit(EXIT_FAILURE);
  }
  exit(0);
}

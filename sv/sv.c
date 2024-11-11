#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>    // For open() and creat()

char *progname;

static void sv(char *argv, char *dir);

int main(int argc, char *argv[]) {
  int i;
  struct stat stbuf;
  char *dir = argv[argc - 1]; // target dir is last provided arg
  progname = argv[0];
  if (argc <= 2) {
    fprintf(stderr, "Usage: %s files... dir", progname);
    exit(EXIT_FAILURE);
  }
  if (stat(dir, &stbuf) == -1) {
    fprintf(stderr, "can't access directory %s", dir);
    exit(EXIT_FAILURE);
  }
  if ((stbuf.st_mode & S_IFMT) != S_IFDIR) {
    fprintf(stderr, "%s is not a directory", dir);
    exit(EXIT_FAILURE);
  }
  for (i = 1; i < argc - 1; ++i) {
    sv(argv[i], dir);
  }
  exit(0);
}

static void sv(char *file, char *dir) {
  struct stat sti, sto;
  int fin, fout, n;
  char target[BUFSIZ], buf[BUFSIZ];
  sprintf(target, "%s/%s", dir, file);
  if (strchr(file, '/') != NULL) {
    fprintf(stderr, "%s is not a directory", dir);
    exit(EXIT_FAILURE);
  }
  if ((stat(file, &sti)) == -1) {
    fprintf(stderr, "cannot stat %s", file);
    exit(EXIT_FAILURE);
  }
  if ((stat(dir, &sto)) == -1) {
    sto.st_mtime = 0;
  }
  if (sti.st_mtime < sto.st_mtime) {
    fprintf(stderr, "%s: %s not copied \n", progname, file);
  } else if ((fin = open(file, O_RDONLY)) == -1) {
    fprintf(stderr, "cannot open %s", file);
    exit(EXIT_FAILURE);
  } else if ((fout = creat(target, sti.st_mode)) == -1) {
    fprintf(stderr, "cannot create %s", target);
    exit(EXIT_FAILURE);
  } else {
    while ((n = read(fin, buf, sizeof buf)) > 0) {
      if (write(fout, buf, n) != n) {
        fprintf(stderr, "cannot write %s", target);
        exit(EXIT_FAILURE);
      }
    }
  }
  close(fin);
  close(fout);
}

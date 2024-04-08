#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAGESIZE 22
char *progname;

FILE *efopen(char *file, char *mode) {
  FILE *fp;

  extern char *progname;

  if ((fp = fopen(file, mode)) != NULL) {
    return fp;
  }
  fprintf(stderr, "%s: can not open file %s mode %s\n", progname, file, mode);
  exit(1);
}

/* cannot improve this with optional command interrup with ! because system also
 * uses pipe input and thus interference */
char ttyin() {
  char buf[BUFSIZ];
  static FILE *tty = NULL;
  if (tty == NULL)
    tty = efopen("/dev/tty", "r");
  if (fgets(buf, BUFSIZ, tty) == NULL || buf[0] == 'q')
    exit(0);
  else
    return buf[0];
}

void print(FILE *fp, int pagesize) {
  static int lines = 0;
  char buf[BUFSIZ];
  while (fgets(buf, sizeof buf, fp) != NULL) {
    if (++lines < pagesize) {
      fputs(buf, stdout);
    } else {
      /* done */
      buf[strlen(buf) - 1] = '\0';
      fputs(buf, stdout);
      /* write everything out immediately */
      fflush(stdout);
      ttyin();
      lines = 0;
    }
  }
}

int main(int argc, char *argv[]) {
  int i, pagesize = PAGESIZE;
  FILE *fp;

  progname = argv[0];
  if (argc > 1 && argv[1][0] == '-') {
    pagesize = atoi(&argv[1][1]);
    argc--;
    argv++;
  }

  if (argc == 1)
    print(fp, pagesize);
  else
    for (i = 1; i < argc; i++) {
      fp = efopen(argv[i], "r");
      print(fp, pagesize);
      fclose(fp);
    };
}

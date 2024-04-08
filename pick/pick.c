#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void pick(char *s){
    fprintf(stderr, "%s? ", s); 
    if (ttyin() == 'y')
        printf("%s\n", s);
}

int main(int argc, char* argv[]){
    int i;
    char buf[BUFSIZ];
    progname = argv[0];
    if (argc == 2 && strcmp(argv[1], "-") == 0) /* pick - */
        while (fgets(buf, sizeof buf, stdin) != NULL) {
            buf[strlen(buf)-1] = '\0';
            pick(buf);
        }
    else
     for (i = 1; i<argc; i++) {
         pick(argv[i]);
     };
    exit(0);
}



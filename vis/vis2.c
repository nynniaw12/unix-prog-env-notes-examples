/* vis: make funny characters visible (version 3) */

#include <_ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strip = 0;

int vis(FILE *fp) {
  int c;
  while ((c = getc(fp) /*is the same as getc(stdin)*/) != EOF) {
    if (isascii(c) && (isprint(c) || c == '\n' || c == '\t' || c == ' ')) {
      putchar(c); /* is the same as putc(c, stdout) */
    } else if (!strip) {
      printf("\\%03o", c);
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int i;
  FILE *fp;
  while (argc > 1 && argv[1][0] == '-') {
    switch (argv[1][1]) {
    case 's':
      strip = 1;
      break;
    default:
      fprintf(stderr, "%s: unknown arg %s\n", argv[0], argv[1]);
      exit(1);
    }
    argc--;
    argv++;
  }
  if (argc == 1) {
    vis(stdin);
  } else {
    for (int i = 1; i < argc; i++) {
      if ((fp = fopen(argv[i], "r")) == NULL) {
        fprintf(stderr, "%s: can not open file %s\n", argv[0], argv[i]);
        exit(1);
      } else {
        vis(fp);
        fclose(fp);
      }
    }
  }
  exit(0);
}

/* vis: make funny characters visible (version 3) */

#include <_ctype.h>
#include <stdio.h>
#include <string.h>

/* argc is count of arguments */
/* argv is the array that points to the strings of flags */

int main(int argc, char* argv[]) 
{
  int c, strip = 0;
  if (argc>1 && strcmp(argv[1], "-s") == 0) {
      strip = 1;
  }
  while ((c = getchar() /*is the same as getc(stdin)*/) != EOF) {
    if (isascii(c) && (isprint(c) || c == '\n' || c == '\t' || c ==' ')) {
        putchar(c); /* is the same as putc(c, stdout) */
    } else if (!strip) {
        printf("\\%03o", c);
    }
  }
  return 0;
}

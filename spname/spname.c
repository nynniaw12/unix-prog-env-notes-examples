/* directory structure
 * struct direct {
 * ino_t d_ino;
 * char d_name[DIRSIZ];
 *};
 */
#include <string.h>
#include <sys/dir.h>
#include <sys/dirent.h>
#include <sys/fcntl.h>
#include <unistd.h>

#define EQ(s, t) (strcmp(s, t) == 0)
#define DIRSIZE DIRSIZ(dp)

const struct dirent* dp;

int spdist(char *s, char *t) {

  while (*s++ == *t) {
    if (*t++ == '\0') {
      return 0;
    }
  }
  if (*--s) {
    if (*t) {
      if (s[1] && t[1] && *s == t[1] && *t == s[1] && EQ(s + 2, t + 2)) {
        return 1;
      }
      if (EQ(s + 1, t + 1)) {
        return 2;
      }
    }
    if (EQ(s + 1, t)) {
      return 2;
    }
  }
  if (*t && EQ(s, t + 1)) {
    return 2;
  }
  return 3;
}

int mindist(char *dir, char *guess, char *best) {
  int d, nd, fd;
  const int ds = DIRSIZE;

  struct {
    ino_t ino;
    char name[ds + 1];
  } nbuf;

  nbuf.name[DIRSIZE] = '\0';

  if (dir[0] == '\0')
    dir = ".";

  d = 3;
  if ((fd = open(dir, 0)) == -1)
    return d;
  while (read(fd, (char *)&nbuf, sizeof(struct direct)) > 0) {
    if (nbuf.ino) {
      nd = spdist(nbuf.name, guess);
      if (nd <= d && nd != 3) {
        strcpy(best, nbuf.name);
        d = nd;
        if (d == 0)
          break;
      }
    }
  }
  close(fd);
  return d;
}

int spname(char *oldname, char *newname) {
  char *p, guess[DIRSIZE + 1], best[DIRSIZE + 1];
  char *new = newname, *old = oldname;
  for (;;) {
    while (*old == '/')
      *new ++ = *old++;
    *new = '\0';
    if (*old == '\0')
      return strcmp(oldname, newname) != 0;
    p = guess;
    for (; *old != '/' && *old != '\0'; old++)
      if (p < guess + DIRSIZE)
        *p++ = *old;
    *p = '\0';
    if (mindist(newname, guess, best) >= 3)
      return -1;
    for (p = best; *new = *p++;)
      new ++;
  }
}

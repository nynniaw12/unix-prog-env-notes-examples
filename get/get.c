#include <unistd.h>

int get(int fd, long pos, char *buf, int n) {
  if (lseek(fd, pos, 0)) {
    return -1;
  } else {
    return read(fd, buf, n);
  }
}

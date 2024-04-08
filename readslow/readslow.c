#include <unistd.h>
#define SIZE 512

int main() {
  char buf[SIZE];
  int n;

  for (;;) {
    while ((n = read(0, buf, sizeof buf) > 0))
      write(1, buf, n);
    sleep(10);
  }
}

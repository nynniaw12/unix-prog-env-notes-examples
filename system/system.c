#include <fcntl.h> // For open() and creat()
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sys(char *s) {
  int status, pid, w, tty;
  void (*istat)(), (*qstat)();
  extern char *progname;
  fflush(stdout); // must flush before fork
  tty = open("/dev/tty", 2);
  if (tty == -1) {
    fprintf(stderr, "%s: can't open /dev/tty\n", progname);
    return -1;
  }
  if ((pid = fork()) == 0) { // multiproc
      close(0); dup(tty); // redirects to parent
      close(1); dup(tty);
      close(2); dup(tty);
      close(tty);
      execlp("sh", "sh", "-c", s, (char*)0);
      exit(127);
  }
  close(tty);
  istat = signal(SIGINT, SIG_IGN); // ignore interrupts and retain previous handler
  qstat = signal(SIGQUIT, SIG_IGN);
  while ((w = wait(&status))!= pid &&  w != -1) // wait for process to complete
      ;
  if (w == -1){ // non-zero 
      status = -1;
  }
  signal(SIGINT, istat); // restore previous handler
  signal(SIGQUIT, qstat);
  return status;
}

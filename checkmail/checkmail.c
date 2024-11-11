#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

char *progname;
char *maildir =
    "/Users/hasanaybarsari/Desktop/github/unix-programming-env/checkmail/mail";

static char *getLogin(void);

int main(int argc, char *argv[]) {
    struct stat buf;
    char *name, *getLogin();
    int lastSize = 0;

    progname = argv[0];
    if ((name = getLogin())== NULL){
        fprintf(stderr, "can't get login name");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "user is: %s \n", name);
    if (chdir(maildir) == -1){
        fprintf(stderr, "can't cd to %s", maildir);
        exit(EXIT_FAILURE);
    }
    for (;;){
        if (stat(name, &buf)==-1){
            buf.st_size = 0;
        }
        if (buf.st_size > lastSize){
            fprintf(stderr, "\nYou have mail\007\n");
        }
        lastSize = buf.st_size;
        sleep(5);
    }
}

static char *getLogin(void) {
    struct passwd *pw;
    uid_t uid = getuid();
    
    pw = getpwuid(uid);
    if (pw == NULL) {
        return NULL;
    }
    
    return pw->pw_name;
}

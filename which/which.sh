# which cmd: which cmd in PATH is executed

opath=$PATH
PATH=/bin:/usr/bin # gets rid of commands used in this file which might
                   # also exist in the cur directory

case $# in
    0) echo 'Usage: which command' 1>&2; exit 2 # redirects to stderr
esac

for i in `echo $opath | sed 's/^:/.:/
                  s/::/:.:/g
                  s/:$/:./
                  s/:/ /g'`
do
    if test -x $i/$1
    then
        echo $i/$1
        exit 0
    fi
done
exit 1


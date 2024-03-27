# overwrite: copy stdin to stdout after eof
# final version 

opath=$PATH
PATH=/bin:/usr/bin

case $# in
0|1) echo 'Usage: overwrite file' 1>&2; exit 2
esac

file=$1; shift # shifts arguments to the left
new=/tmp/overwr1.$$ ; old=/tmp/overwr2.$$

trap `rm -f $new $old; exit 1` 1 2 15 # trap routine for cleanup

if PATH=$opath "$@" >$new # execute given command with shifted arguments $@ is like $* but uninterpreted
then
    cp $file $old
    trap `` 1 2 15 # ignore signals at this point
    cp $new $file
else
    echo "overwrite: $1 failed, $file unchanged" 1>&2
fi

rm -f $new $old

# put: install file into history

PATH=/bin:/usr/bin

case $# in
1) HIST=$1.H ;;
*) echo 'Usage: put file' 1>&2; exit 1 ;;
esac

if test ! -r $1
then
    echo "put: can not open $1" 1>&2
    exit 1
fi

trap `rm -f /tmp/put.[ab]$$ ; exit 1` 1 2 15

echo -n `Summary: `

read Summary

if get -o /tmp/put.a$$ $1 # prev version
then
    cp $1 /tmp/put.b$$
    echo "@@@ `getname` `date` $Summary" >>/tmp/put.b$$
    diff -e $1 /tmp/put.a$$ >>/tmp/put/b$$ # latest diffs
    sed -n `/^@@@/,$p` <$HIST >>/tmp/put.b$$ # old diffs
    overwrite $HIST cat /tmp/put.b$$ # put back
else
    echo "put: creating $HIST"
    cp $1 $HIST
    echo "@@@ `getname` `date` $Summary" >>$HIST
fi

rm -f /tmp/put.[ab]$$ # regex to delete both a and b files

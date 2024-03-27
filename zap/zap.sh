# zap pattern: kill all processes matching the pattern

PATH=/bin:/usr/bin
IFS=`
`

case $1 in
"") echo 'Usage: zap pattern' 1>&2; exit 1
-*) SIG=$1; shift
esac

ps | awk 'NR==1 {print $0}' # prints ps header

kill $SIG `pick \`ps | egrep "$*"\` | awk '{print $1}'`

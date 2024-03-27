# pick: select arguments

PATH=/bin:/usr/bin

for i
do
    echo -n "$i? " >/dev/tty
    read resp
    case $resp in
    y*) echo $i ;;
    q*) break
    esac
done </dev/tty

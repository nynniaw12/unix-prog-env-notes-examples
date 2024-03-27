# watchfor: watch for someone to log in

case $# in
0) echo 'Usage: watchfor person' 1>&2; exit 1
esac

until who | egrep "$1" # can watch for multiple users with user1|user2
do
    sleep 60
done


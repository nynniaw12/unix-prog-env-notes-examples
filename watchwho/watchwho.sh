# watchwho: watch who logs in and out

new=/tmp/wwho1.$$
old=/tmp/wwho2.$$

>$old # create an empty file

while : # loops forever : is a built in shell command
    who >$new
    diff $old $new
    mv $new $old
    sleep 60
done | awk `/>/ { $1 = "in:    "; print }
            /</ { $1 = "in:    "; print }`



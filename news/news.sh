# news: print news files, final version

HOME=. # debugging
cd .
IFS=`
`

for i in `ls -t * $HOME/.news_time 2>&1`
do
    IFS=` `
    case $i in
    *` not found`) ;;
    */.news_time) break ;;
    *) set X`ls -l $i` 
       echo "
$i: ($3) $5 $6 $7
"
       cat $i
    esac
done

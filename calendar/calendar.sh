# calendar: version 3 
# usage: zsh calendar.sh filename-to-calendar

(date; cat $1) |
awk '
    BEGIN { 
    x = "Jan 31 Feb 28 Mar 31 Apr 30 May 31 Jun 30 Jul 31 Aug 31 Sep 30 Oct 31 Nov 30 Dec 31 Jan 31"
    split(x, data)
        for (i = 1; i<24; i+=2) {
            days[data[i]] = data[i+1]
            nextmon[data[i]] = data[i+2]
        }
    }
    NR == 1 { 
        mon1 = $2
        day1 = $3
        mon2 = mon1
        day2 = day1 + 1
        if (day1 >= days[mon1]) {
            day2 = 1
            mon2 = nextmon[mon1]
        }
    } # set date
    NR > 1 && $1 == mon1 && $2 == day1 { printf "today; %s \n", substr($0,match($0, $3 ".*"))}
    NR > 1 && $1 == mon2 && $2 == day2 { printf "tomorrow; %s \n", substr($0,match($0, $3 ".*"))}
' 

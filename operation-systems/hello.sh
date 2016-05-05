#!/bin/sh

# cat ./log.txt | awk '{print $4}' | cut -c2-12 | sort | uniq | xargs -I {} -n 1 sh -c 'export f="{}"; printf "$f\t"; cat ./log.txt | grep $f | awk '"'"'{print $1}\'"'"' | sort | uniq -c | sort -n | wc -l' | sort -nrk2 | head | awk '{total += $2; rs[$1] = $2 } END { for (r in rs) print r, rs[r], total/rs[r]"%" }'|sort -nr -k2


awk '{print $1,$4}' log.txt|cut -d':' -f 1|tr -d '['|sort|uniq|awk '{print $2}'|sort|uniq -c|sort -nr|head|awk '{total += $1; rs[$2] = $1 } END { for (r in rs) print r, rs[r], rs[r]*100/total"%" }'|sort -nr -k2
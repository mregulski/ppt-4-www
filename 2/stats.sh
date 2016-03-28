#!/bin/zsh
# statistics generator for sorting algorithms
i=$1
output=$2.$1.$(date +%m%d%H%M%S)
time (
while (($i > 0)); do
    echo -n "\r$(tput el)size: $i"
    echo "size: $i" >> $output
    ./test.py -s $i -t random >> $output
    echo "" >> $output
    ((i-=100))
done
echo "\r$(tput el)Done. Maximum size: $1."
)

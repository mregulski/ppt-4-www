#!/bin/zsh
# statistics generator for sorting algorithms
if (($# != 3)); then
    echo "usage: ./stats.sh <test_amount> <max_size> <prefix>"
    echo "output will be placed in ./stat/<prefix>.<size>.<1..test_amount>.<timestamp> files"
    exit 1
fi
test_amount=$1
max_size=$2
prefix=$3
for i in {1..$test_amount}; do
    size=$max_size
    output=$prefix.$size.$i.$(date +%m%d%H%M%S)
    while (($size > 0)); do
        echo -n "\r$(tput el)size: $size"
        ./bin/test -s $size -t random >> $output
        echo "" >> $output
        ((size-=100))
    done
done
echo "\r$(tput el)Done. Maximum size: $2."

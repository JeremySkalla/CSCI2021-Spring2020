#!/bin/bash

# run all the algorithms in superscalar_main

echo '> date'
date

echo '> hostname'
hostname

echo '> lscpu'
lscpu

echo 

alltimes=()

# atlas
mult=9
exp=27

# csel-1250
mult=29
exp=27

algs=$(./superscalar_main |awk '/ : /{print $1}') # | head -1)
echo $algs
for a in $algs; do
    cmd="./superscalar_main $mult $exp $a"
    printf "> time $cmd\n"
    result=$(/usr/bin/time -o /dev/stdout -p $cmd)
    tm=$(echo "$result" | awk '/user/{print $2}')
    alltimes+=("$a $tm")
    printf "$result\n"
    printf "\n"
done

echo
printf "ALL TIMES:\n"
for t in "${alltimes[@]}"; do
    printf "$t\n"
done

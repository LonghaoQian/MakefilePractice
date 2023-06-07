#!/bin/bash
set -e # return on any error
if [ -z "$1" ]; then
    echo "arugment is empty..."
    exit 1
fi

if [ ! -f $1 ]; then
    echo "$1 does not exist..."
    exit 1
fi

# set display color
Green='\033[0;32m'
RED='\033[0;31m'
Blue='\033[0;34m'
Purple='\033[0;35m'
Cyan='\033[0;36m'
NC='\033[0m' # No Color

# get the line number of the following keyword
var0=$(grep  -n '**Failure' $1 | cut -d: -f1)
var1=$(grep  -n '^\[  FAILED \ ]' $1 | cut -d: -f1)

var3=()
i=0
for x in $var0
do
    # store each number separately in an array
    var3[$i]=$x
    i=$((i+1))
done

i=0
var4=()
for x in $var1
do
    # store each number separately in an array
    var4[$i]=$x
    i=$((i+1))
done

if [ ${#var4[@]} -eq 0 ];then
    echo -e "${Green} All tests pass! ${NC}"
    exit 0
fi

if [ ${#var3[@]} -ne ${#var4[@]} ];then
    echo -e "${RED} Error, the numnber of 'Failures' is ${#var3[@]}, \
however the numnber of '[  FAILED  ]' is ${#var4[@]}${NC}"
    echo "please check whether there are Failures or [ FAILED ] printed out by source code."
    echo "Lines ending with Failure:"
    for x in $var0
    do
        awk "NR == ${x}" $1
    done
    echo "Lines ending with [  FAILED  ]:"
    for x in $var1
    do
        awk "NR == ${x}" $1
    done
    exit 1
fi

# display number of failed tests
echo -e "${RED}${#var3[@]} failed tests found!${NC}"

for ((j=0; j<${#var3[@]}; j++))
do
echo -e "${RED}FAILED TEST [$j]${NC}"
line1=${var3[$j]}
line2=${var4[$j]}
awk "NR >= ${line1} && NR <= ${line2}" $1
done
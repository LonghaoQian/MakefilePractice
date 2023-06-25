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

# set display color variable
Green='\033[0;32m'
RED='\033[0;31m'
Blue='\033[0;34m'
Purple='\033[0;35m'
Cyan='\033[0;36m'
NC='\033[0m' # No Color

# checkwhether there are failed tests
var1=$(grep  -n '^\[  FAILED \]*' $1 | cut -d: -f1)

i=0
var4=()
for x in $var1
do
    # store each number separately in an array
    var4[$i]=$x
    i=$((i+1))
done

# if no failed tests found, then exit
if [ ${#var4[@]} -eq 0 ];then
    echo -e "${Green}All tests passed!${NC}"
    exit 0
fi

# get the line number of the following keyword
var0=$(grep  -n '^\[  PASSED  \]*\|^\[  FAILED \]*' $1 | cut -d: -f1)
var3=()
i=0
for x in $var0
do
    # store each number separately in an array
    var3[$i]=$x
    i=$((i+1))
    # echo $x
done

# mark the idex corresponding to failed test
idx=()
i=0
for ((j=0; j<${#var3[@]}; j++))
do
    if (( $i < ${#var4[@]} )) && (( ${var4[$i]}==${var3[$j]} ));then
        #echo $((var4[$i])) $((var3[$j]))
        idx[$i]=$j
        #echo ${idx[$i]}
        i=$((i+1))
    fi
done

# display failed message
for ((j=0; j<${#idx[@]}; j++))
do
    echo -e "${RED}FAILED TEST [$j]${NC}"
    idx1=${idx[$j]}
    if (( $idx1!=0 )); then
        line1=${var3[$idx1-1]}
    else
        line1=0
    fi
    line2=${var3[$idx1]}
    awk "NR > ${line1} && NR <= ${line2}" $1
done

# if there are failed tests, display the following info
echo -e "${RED}${#var4[@]} failed tests found!${NC}"
exit 1
# then run all tests

echo $0
echo $1

if [ -f "$1" ]; then
    echo "$1 does not exist..."
else
    echo "$1 exist..."
fi

search_block() {
    local file="$1" local leading_keyword="$2" local trailing_keyword="$3" # Use awk to find the block of text
    awk -v leading="$leading_keyword" -v trailing="$trailing_keyword" ' \
    BEGIN { block = ""; found = 0 } /leading/ { block = $0; found = 1 } found { block = block ORS $0 } \
    /trailing/ { if (found) { print block; found = 0; block = "" } } ' "$file" 
}

grep -n "$1" "[ FAILED ]"
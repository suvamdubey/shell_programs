#!/bin/sh
echo "Enter filename"
read f
test -e $f && echo $(file $f) || echo "not present"


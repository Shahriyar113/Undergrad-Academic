#!/bin/bash

count=0

rm out.txt


touch out.txt

until cat out.txt | grep wrong 

do

./Fail_Script.sh >> out.txt 2> err.txt

count=$((count + 1))

done

echo "it tooks $count runs to fail"





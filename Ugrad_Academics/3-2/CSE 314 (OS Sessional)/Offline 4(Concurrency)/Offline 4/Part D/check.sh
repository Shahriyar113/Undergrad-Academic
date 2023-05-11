#!/bin/bash


./a.out $1 $2 > temp.txt
cat temp.txt | grep arrived
cat temp.txt | grep leaving
cat temp.txt | grep haircut

rm temp.txt


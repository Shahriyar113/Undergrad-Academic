#!/bin/bash

cd files

for i in $(ls)

do

  if cat $i | head -n$1 | tail -n1 | grep -i $2
  then
  
    echo "$i should be removed"
    #rm $i
    
  fi


done

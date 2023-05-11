#!/bin/bash

#creating all the necessary files and directories
mkdir files
cd files

touch abc.txt
touch myfile1.txt
touch programv1.01
touch my_file.txt
mkdir a
mkdir b
mkdir c 
mkdir d

#here the real program starts

for i in $(ls)

do

  if [[ -f $i ]];then
  
  for ((c=0;c<=9;c++))
  
  do
    
    if echo $i | grep $c;then
    
    echo "$i should be deleted"
    rm $i
    break
    
    fi
  
  done
  
  fi


done


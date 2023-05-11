#!/bin/bash

if [[ $# -lt 1 ]];then

  echo "Usage Script1.sh"
  ls
  
  exit 1

fi


for files in $*

do
  
  if [[ -f $files ]];then
    
    if [[ -x $files ]];then
      
      echo "$files is currently executable"
      ls -l $files
      
      echo "$files's execution permission is changing"
      chmod a-x $files
      
      ls -l $files
      echo "$files is currently not executable"
    
    else
    
      ls -l $files  
      
    fi
  
  
  elif [[ -d $files ]];then
  
     echo "$files is not a regular file"  
  
  else
  
     echo "$files doesnot exist"
  fi



done


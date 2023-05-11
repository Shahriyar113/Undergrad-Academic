#!/bin/bash


Func(){

  for i in $(ls)
  
  do
    
    if [[ -d $i ]];then
    
    cd $i
    Func
      
    elif [[ -f $i ]];then
    
      if echo $i | grep cpp;then
      
      file_name=${i:0:-4} #file name theke ".cpp" kete diye baki part store korchi
      
      mv $i $file_name.c   
      
      fi
    
    
    fi
   done
   
   cd ..


}


Func

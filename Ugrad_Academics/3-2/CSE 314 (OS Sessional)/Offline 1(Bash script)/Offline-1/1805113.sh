#!/bin/bash

max_number=100
max_student=9

Scores_list=()
Students_id_list=()

Score_list_index=0
Students_id_list_index=0


if [[ $# -eq 2 ]];then
    max_number=$1
    max_student=$2
fi



#Creating output file for each student

for std_id in $(ls Submissions)
do
   #checking if the student named the file correctly or not...if not then his .sh file will not be run and his output will be conisdered as a empty file 
   
   if [[ $(ls Submissions/$std_id | wc -l) -eq 1 ]];then
      if [[ $(ls Submissions/$std_id) = $std_id.sh ]];then
   
      ./Submissions/$std_id/$std_id.sh > out$std_id.txt
  
      #listing student id's
      Students_id_list[Students_id_list_index]=$std_id  
      ((Students_id_list_index=Students_id_list_index+1))
       
      else
      #creating empty output file for incorrect file name
      touch out$std_id.txt   
     
      #listing student id's
      Students_id_list[Students_id_list_index]=$std_id 
      ((Students_id_list_index=Students_id_list_index+1))
      
      fi 
   
   else
   
   #creating empty output file for incorrect file name
     touch out$std_id.txt   
     
     #listing student id's
     Students_id_list[Students_id_list_index]=$std_id 
     ((Students_id_list_index=Students_id_list_index+1))
   
      
   fi  
  
done


Mismatch_count=0


#calculating score without copy checking

for std_id in ${Students_id_list[@]}

do
  
  #if the output file of the student is empty ,that means he named the file incorrectly....so he should get 0..that's why Mismatch_count is creating purposely bigger value so in the below score become 0
  
  if [[ $(cat out$std_id.txt | wc -l) -eq 0 ]];then #checking if the output file is empty or not
  
  ((Mismatch_count=max_number))
   
  else

     line_count=$(diff -w out$std_id.txt AcceptedOutput.txt | wc -l) 
     for ((i=1;i<=$line_count;i++))
     do

        if diff -w out$std_id.txt AcceptedOutput.txt | head -n$i | tail -n1 |grep "<";then 
        ((Mismatch_count=Mismatch_count+1))
        elif diff -w out$std_id.txt AcceptedOutput.txt | head -n$i | tail -n1 |grep ">";then
        ((Mismatch_count=Mismatch_count+1))
        fi   

     done
   fi  

#putting the students' score in the Scores_list 
((score=max_number-Mismatch_count*5))

if [[ $score -lt 0 ]];then
   score=0
fi

Scores_list[Score_list_index]=$score
((Score_list_index=Score_list_index+1))

Mismatch_count=0
#echo $score


done

#performing copy checking and updating the scores

for index1 in ${!Students_id_list[@]}

do
  
  for index2 in ${!Students_id_list[@]}

  do
    
    if [[ $index1 -gt $index2 ]];then
      
      #-Z for ignoring trailing white space and 
      #-B for ignoring Blank line 
      if diff -ZB Submissions/${Students_id_list[$index1]}/${Students_id_list[$index1]}.sh Submissions/${Students_id_list[$index2]}/${Students_id_list[$index2]}.sh;then
      
        Scores_list[index1]="-${Scores_list[$index1]}"
        Scores_list[index2]="-${Scores_list[$index2]}"
      fi  
      
    fi 

  done
  

done

#showing scores on console

#for index in ${!Scores_list[@]}
#do
 # echo "${Students_id_list[$index]} : ${Scores_list[$index]}" 
#done


curr_student_id=1805121
index=0

for (( i=1;i<=max_student;i++ ))
do
  if [[ $curr_student_id -ne ${Students_id_list[$index]}  ]];then
  
      echo "$curr_student_id : 0"
     
  else
     
      echo "${Students_id_list[$index]} : ${Scores_list[$index]}" 
      ((index=index+1))
      
  fi
  
  ((curr_student_id=curr_student_id+1))
  
done


#showing output in output.csv
echo "student_id,score" > output.csv


#for index in ${!Scores_list[@]}
#do
 # echo "${Students_id_list[$index]},${Scores_list[$index]}" >> output.csv
#done


curr_student_id=1805121
index=0


for (( i=1;i<=max_student;i++ ))
do
  if [[ $curr_student_id -ne ${Students_id_list[$index]}  ]];then
  
      echo "$curr_student_id,0" >> output.csv
     
  else
     
      echo "${Students_id_list[$index]},${Scores_list[$index]}" >> output.csv 
      ((index=index+1))
      
  fi
  
  ((curr_student_id=curr_student_id+1))
  
done



#removing all extra created txt files
for std_id in ${Students_id_list[@]}
do
  rm out$std_id.txt
done




    
  

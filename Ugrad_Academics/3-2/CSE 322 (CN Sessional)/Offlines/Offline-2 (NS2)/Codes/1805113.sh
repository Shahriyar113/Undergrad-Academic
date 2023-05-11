#!/bin/bash

baseline_area=500
baseline_nn=40
baseline_nf=20


#Throughout
#--------------------------------------------------

Bash() {

if [[ $1 -eq 1 ]];then

#Throughput vs Area_size
echo "y" > Throughput.csv
echo "x" > Areasize.csv


for ((i=250 ; i<=1250 ;i=i+250))
do
  ns 1805113.tcl $i $baseline_nn $baseline_nf
  echo $i >> Areasize.csv
  awk -f Throughput.awk trace.tr >> Throughput.csv
 
done


paste -d, Areasize.csv Throughput.csv  > Throughput_Plots/Throughput_vs_Areasize.csv
rm Throughput.csv
rm Areasize.csv  

fi



if [[ $1 -eq 2 ]];then
#Throughput vs nn
echo "y" > Throughput.csv
echo "x" > nn.csv

for ((i=20; i<=100 ;i=i+20))
do
  ns 1805113.tcl $baseline_area $i $baseline_nf
  echo $i >> nn.csv
  awk -f Throughput.awk trace.tr >> Throughput.csv
 
done

paste -d, nn.csv Throughput.csv  > Throughput_Plots/Throughput_vs_nn.csv
rm Throughput.csv
rm nn.csv  

fi


if [[ $1 -eq 3 ]];then

#Throughput vs nf
echo "y" > Throughput.csv
echo "x" > nf.csv


for ((i=10; i<=50 ;i=i+10))
do
  ns 1805113.tcl $baseline_area $baseline_nf $i
  echo $i >> nf.csv
  awk -f Throughput.awk trace.tr >> Throughput.csv
 
done

paste -d, nf.csv Throughput.csv  > Throughput_Plots/Throughput_vs_nf.csv
rm Throughput.csv
rm nf.csv  

fi
#Delay
#--------------------------------------------------


if [[ $1 -eq 4 ]];then
#Delay vs Area_size
echo "y" > Delay.csv
echo "x" > Areasize.csv

for ((i=250 ; i<=1250 ;i=i+250))
do
  ns 1805113.tcl $i $baseline_nn $baseline_nf
  echo $i >> Areasize.csv
  awk -f Delay.awk trace.tr >> Delay.csv
 
done

paste -d, Areasize.csv Delay.csv  > Delay_Plots/Delay_vs_Areasize.csv
rm Delay.csv
rm Areasize.csv  


fi
#echo "end"
#echo ""

if [[ $1 -eq 5 ]];then

#Delay vs nn
echo "y" > Delay.csv
echo "x" > nn.csv

for ((i=20; i<=100 ;i=i+20))
do
  ns 1805113.tcl $baseline_area $i $baseline_nf
  echo $i >> nn.csv
  awk -f Delay.awk trace.tr >> Delay.csv
 
done

paste -d, nn.csv Delay.csv  > Delay_Plots/Delay_vs_nn.csv
rm Delay.csv
rm nn.csv  

fi



if [[ $1 -eq 6 ]];then

#Delay vs nf
echo "y" > Delay.csv
echo "x" > nf.csv

for ((i=10; i<=50 ;i=i+10))
do
  ns 1805113.tcl $baseline_area $baseline_nf $i
  echo $i >> nf.csv
  awk -f Delay.awk trace.tr >> Delay.csv
 
done

paste -d, nf.csv Delay.csv  > Delay_Plots/Delay_vs_nf.csv
rm Delay.csv
rm nf.csv  


fi

#Deliver_Ratio
#----------------------------------------------------




if [[ $1 -eq 7 ]];then
#Deliver_Ratio vs Area_size
echo "y" > Deliver_Ratio.csv
echo "x" > Areasize.csv

for ((i=250 ; i<=1250 ;i=i+250))
do
  ns 1805113.tcl $i $baseline_nn $baseline_nf
  echo $i >> Areasize.csv
  awk -f Deliver_Ratio.awk trace.tr >> Deliver_Ratio.csv
 
done

paste -d, Areasize.csv Deliver_Ratio.csv  > Deliver_Ratio_Plots/Deliver_ratio_vs_Areasize.csv
rm Deliver_Ratio.csv
rm Areasize.csv 

fi

#echo "end"
#echo ""

if [[ $1 -eq 8 ]];then

#Deliver_Ratio vs nn
echo "y" > Deliver_Ratio.csv
echo "x" > nn.csv

for ((i=20; i<=100 ;i=i+20))
do
  ns 1805113.tcl $baseline_area $i $baseline_nf
  echo $i >> nn.csv
  awk -f Deliver_Ratio.awk trace.tr >> Deliver_Ratio.csv
 
done

paste -d, nn.csv Deliver_Ratio.csv  > Deliver_Ratio_Plots/Deliver_ratio_vs_nn.csv
rm Deliver_Ratio.csv
rm nn.csv 

fi


if [[ $1 -eq 9 ]];then
#Deliver_Ratio vs nf
echo "y" > Deliver_Ratio.csv
echo "x" > nf.csv

for ((i=10; i<=50 ;i=i+10))
do
  ns 1805113.tcl $baseline_area $baseline_nf $i
  echo $i >> nf.csv
  awk -f Deliver_Ratio.awk trace.tr >> Deliver_Ratio.csv
 
done

paste -d, nf.csv Deliver_Ratio.csv  > Deliver_Ratio_Plots/Deliver_ratio_vs_nf.csv
rm Deliver_Ratio.csv
rm nf.csv 

fi
#Drop_Ratio
#----------------------------------------------------

if [[ $1 -eq 10 ]];then
#Drop_Ratio vs Area_size
echo "y" > Drop_Ratio.csv
echo "x" > Areasize.csv

for ((i=250 ; i<=1250 ;i=i+250))
do
  ns 1805113.tcl $i $baseline_nn $baseline_nf
  echo $i >> Areasize.csv
  awk -f Drop_Ratio.awk trace.tr >> Drop_Ratio.csv
 
done

paste -d, Areasize.csv Drop_Ratio.csv  > Drop_Ratio_Plots/Drop_Ratio_vs_Areasize.csv
rm Drop_Ratio.csv
rm Areasize.csv 

fi
#echo "end"
#echo ""

if [[ $1 -eq 11 ]];then
#Drop_Ratio vs nn
echo "y" > Drop_Ratio.csv
echo "x" > nn.csv

for ((i=20; i<=100 ;i=i+20))
do
  ns 1805113.tcl $baseline_area $i $baseline_nf
  echo $i >> nn.csv
  awk -f Drop_Ratio.awk trace.tr >> Drop_Ratio.csv
 
done

paste -d, nn.csv Drop_Ratio.csv  > Drop_Ratio_Plots/Drop_Ratio_vs_nn.csv
rm Drop_Ratio.csv
rm nn.csv 

fi


if [[ $1 -eq 12 ]];then
#Drop_Ratio vs nf
echo "y" > Drop_Ratio.csv
echo "x" > nf.csv

for ((i=10; i<=50 ;i=i+10))
do
  ns 1805113.tcl $baseline_area $baseline_nf $i
  echo $i >> nf.csv
  awk -f Drop_Ratio.awk trace.tr >> Drop_Ratio.csv
 
done

paste -d, nf.csv Drop_Ratio.csv  > Drop_Ratio_Plots/Drop_Ratio_vs_nf.csv
rm Drop_Ratio.csv
rm nf.csv 

fi

}


#Global Scope of the script
for ((c=1 ; c<=12 ;c=c+1))
do
  echo "$c th Plot data processing started"
  Bash $c
  echo "$c th Plot data processing finished" 
 
done














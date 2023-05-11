import matplotlib.pyplot as plt
import numpy as np
import math
import pandas as pd

def f(x):
    p=140000/(140000 -2100*x)
    return (2000*math.log(p))-9.8*x



#n -> subinterval
#a -> lower_limit
#b -> upper limit


# 1 Trapezoid rule is applied for 1 sub intervals (2 points needed (upper limit and lower limit )
# so 'n' Trapezoid rule have to be applied for n sub intervals
# and there will be total "n+1" points in the intervals

def Trapezoid(n,a,b):
    h=(b-a)/n
    total_area = 0;
    for i in range(n):
        A=a+i*h;
        B=a+(i+1)*h
        
        total_area = total_area + 0.5*(f(A) + f(B))*h
        
    return total_area


#n -> number of observation 
def Trapezoid_Relarive_errors(n):
    Error_List =['-----']
    Result_list=[];
    Iteration=[]
    
    for i in range(1,n+1):
        Result_list.append(Trapezoid(i, 8, 30))
        Iteration.append(i)
    
    for i in range(1,n):
        Current_error = abs(Result_list[i]-Result_list[i-1])*100/Result_list[i]
        Error_List.append(Current_error)
        

    d={'Result' : pd.Series(Result_list , index=Iteration),
       'Errors' : pd.Series(Error_List , index=Iteration)}
       
    
    df=pd.DataFrame(d)
    print(df)

#Results will be observed for 5 diiferent values and their relative errors 


        
    
# 1 Simpson's 1/3rd rule is applied for 2 sub intervals (3 points needed (upper limit,lower limit,mid point) )
# so 'n' time Simpson's 1/3rd rule have to be applied for 2n sub intervals
# and there will be total "2n+1" points in the intervals
 

#here n --> number of simpson's 1/3rd rule will be applied  
#So total sub interval = 2n 

def Simpsons_one_third(n,a,b):
    
    h=(b-a)/(2*n)
    
    Total_Result = 0
    
    for i in range(0,2*n,2):
        A = a + i*h  #lower limit of current sub interval
        B = a + (i+2)*h #upper limit of current sub interval
        Mid = (A+B)/2  #mid of current sub interval
        
        
        # A0,A1,A2 are the coefficient of currently fitting polynomials
        
        A0=(A**2*f(B) + A*B*f(B) - 4*A*B*f(Mid) + A*B*f(A) + B**2*f(A))/(A-B)**2
       
        
        A1= -(A*f(A) - 4*A*f(Mid) + 3*A*f(B) + 3*B*f(A) - 4*B*f(Mid) + B*f(B))/(A-B)**2
      
       
        A2 = (2*(f(A) - 2*f(Mid) +f(B)))/(A-B)**2
       
        
        Current_Area = A0*(B-A) + A1*(B**2-A**2)/2 + A2*(B**3-A**3)/3
        
        Total_Result = Total_Result + Current_Area
        
    return Total_Result
        
        
#n -> number of observation 
def Simpsons_one_third_Relarive_errors(n):
    
    Error_List =['-----']
    Result_list=[];
    Iteration=[]
    
    for i in range(1,n+1):
        Result_list.append(Simpsons_one_third(i, 8, 30))
        Iteration.append(i)
    
    for i in range(1,n):
        Current_error = abs(Result_list[i]-Result_list[i-1])*100/Result_list[i]
        Error_List.append(Current_error)
        

    d={'Result' : pd.Series(Result_list , index=Iteration),
       'Errors' : pd.Series(Error_List , index=Iteration)}
       
    
    df=pd.DataFrame(d)
    print(df)     
        
        
    
print("Trapezoid Rule")
print("---------------")
print()       
Trapezoid_Relarive_errors(5)
    
print()
print() 


print("Sympson's 1/3rd Rule")
print("---------------------")
Simpsons_one_third_Relarive_errors(5)



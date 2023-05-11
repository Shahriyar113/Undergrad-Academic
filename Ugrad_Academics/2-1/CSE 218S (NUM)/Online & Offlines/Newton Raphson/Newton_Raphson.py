# -*- coding: utf-8 -*-
"""
Created on Fri May 28 06:55:32 2021

@author: ASUS
"""

import matplotlib.pyplot as plt
import numpy as np
import math
import pandas as pd

x_coordinates = np.linspace(-100,400,100)
y_coordinates=[]



def f(x):
    
    return (40*x**1.5-875*x+35000)

# d_f(x) means f'(x)

'''
def d_f(x):
    return 3*x**2 - 0.33*x
'''

#Numerical Differentiation
def d_f(x):
    del_x=0.001
    
    return (f(x+del_x)-f(x-del_x))/(2*del_x)  #central difference approximation

    



for i in range(len(x_coordinates)):
    
        y_coordinates.append(f(x_coordinates[i]))
        
        '''
        if(abs(y_coordinates[i]-y_coordinates[i-1]) > 50):
            y_coordinates[i-1]=np.nan
            x_coordinates[i-1]=np.nan
        '''
        
        

y_coordinates=np.array(y_coordinates)

plt.grid(True)

plt.plot(x_coordinates ,y_coordinates)

def Num_Of_Significant_Digit(err):
    return 2-math.log10(err/0.5)
    


def Newton_Raphson_Method(X,r_a_error,max_iteration):
   
    X_old=X
    
    for i in range(max_iteration):
            X_new = X_old - f(X_old)/d_f(X_old)
            
            err=abs((X_old - X_new)*100/X_new)
            if err < r_a_error:
                return X_new
            X_old=X_new
            
            
    return X_old


def Newton_Raphson_Method_table(X,r_a_error,max_iteration):
    
    X_list=[]
    Iteration=[1]
    err_list=['-----']
    significant_digit_list=['-----']
   
    X_old=X
    X_list.append(X_old)
    
    for i in range(max_iteration):
            Iteration.append(i+2)
            X_new = X_old - f(X_old)/d_f(X_old)
            
            err=abs((X_old - X_new)*100/X_new)
            significant_digit_list.append(int(Num_Of_Significant_Digit(err)))
            err_list.append(err)
            if err < r_a_error:
                return X_new
            X_old=X_new
            X_list.append(X_old)
            
    
    d={'X': pd.Series(X_list, index=Iteration),
       'Error%' : pd.Series(err_list, index=Iteration),
       'Significant Digit' : pd.Series(significant_digit_list, index=Iteration)}
    
    df=pd.DataFrame(d)
    print(df)
            
            
print("Root: ",Newton_Raphson_Method(350,0,3))

Newton_Raphson_Method_table(350,0,3)
        
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

import numpy as np
import matplotlib.pyplot as plt
import numpy as np
import math
import pandas as pd
from sympy import *


X_for_ab =     [10,14,15,18,20,22,25,27,30]

P_for_ab =     [60,55,52,47,46,44,43,42,40]

X_for_bc =     [30,31,35,37,40]

P_for_bc =     [40,35,30,25,20]

"""
Mass =     [1011,1255,1347,1101,1203,1245,1378,1315,1475,1547,1689]

Velocity = [1000,1500,2000,2500,3000,3500,4000,4500,5000,5500,6000] 



Given_X=25

Ordering = {}



for i in range(len(Time)):
    Ordering[i]=abs(Time[i] - Given_X)

                    
#print(Ordering)

Ordering=dict(sorted(Ordering.items(), key = 
             lambda dic:(dic[1], dic[0])))

Ordered_Index=list(Ordering.keys());


Ordered_Time=[]

Ordered_Mass=[]

Ordered_Velocity=[]

for i in range(len(Time)):
    Ordered_Time.append(Time[Ordered_Index[i]])
    Ordered_Mass.append(Mass[Ordered_Index[i]])
    Ordered_Velocity.append(Velocity[Ordered_Index[i]])


#Ordering Complete
"""

x = Symbol('x')


def function_value_ab(X0):
    
        return P_for_ab[X_for_ab.index(X0)]
    
def function_value_bc(X0):
    
        return P_for_bc[X_for_bc.index(X0)]
    
    
 ##flag 0 ==> Mass-time interpolation
 ##flag 1 ==> Velocity-time interpolation

    
def ab_Lagrangerian_Interpolation(n,X):
    
    X_list=[22,25,27,30]
    
    
    
    Iteration=n+1
    
    Y=0
    Product_Res = 1
    
    for i in range(Iteration):
        
        Product_Res = function_value_ab(X_list[i])
        for j in range(Iteration):
            if i==j:
                continue
            Product_Res = Product_Res * (X-X_list[j])/(X_list[i]-X_list[j])
        
        Y = Y + Product_Res
        Product_Res=1
    
    return Y

def bc_Lagrangerian_Interpolation(n,X):
    
    X_list=[30,31,35,37]
    
    
    
    Iteration=n+1
    
    Y=0
    Product_Res = 1
    
    for i in range(Iteration):
        
        Product_Res = function_value_bc(X_list[i])
        for j in range(Iteration):
            if i==j:
                continue
            Product_Res = Product_Res * (X-X_list[j])/(X_list[i]-X_list[j])
        
        Y = Y + Product_Res
        Product_Res=1
    
    return Y



def ab_relative_errors(): 
    Ans=[]
    Errors=['------']
    
   
    Iteration=[]
    
    for i in range(3):
        Iteration.append(i+1)
        Ans.append(ab_Lagrangerian_Interpolation(i+1,28))

    
    for i in range(len(Ans)-1):
        
        err = abs((Ans[i+1]-Ans[i])*100)/Ans[i+1]
        Errors.append(err)
        
    d={'Y' : pd.Series(Ans, index=Iteration),
       'Error' : pd.Series(Errors, index=Iteration)
       }
    print("ab")
    df=pd.DataFrame(d)
    print(df)
    print()

     
def bc_relative_errors(): 
    Ans=[]
    Errors=['------']
    
    Iteration=[]
    
    for i in range(3):
        Iteration.append(i+1)
        Ans.append(bc_Lagrangerian_Interpolation(i+1,32))
    
    for i in range(len(Ans)-1):
        
        err = abs((Ans[i+1]-Ans[i])*100)/Ans[i+1]
        Errors.append(err)
        
    d={'Y' : pd.Series(Ans, index=Iteration),
       'Error' : pd.Series(Errors, index=Iteration)
       }
    print("bc")

    df=pd.DataFrame(d)
    print(df)




    
def ab_Plotting():
    x_coordinates=np.array(X_for_ab)
    y_coordinates=np.array(P_for_ab)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,color="red")
    
    X_s=[22,25,27,28,30]
    Y_s=[44,43,42,41.4,40]
    plt.plot(X_s ,Y_s,"ro",color="red")
    
 
def bc_Plotting():
    x_coordinates=np.array(X_for_bc)
    y_coordinates=np.array(P_for_bc)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,color="blue")
    
    X_s=[31,32,35,37,40]
    Y_s=[35,35,30,25,20]
    plt.plot(X_s ,Y_s,"ro",color="blue")
    


def get_work_ab(V):
    f = ab_Lagrangerian_Interpolation(3, x)
    f_prime = integrate(f)
   
    f_prime = lambdify(x, f_prime)
    return f_prime(V)

def get_work_bc(V):
    f = bc_Lagrangerian_Interpolation(3, x)
    f_prime = integrate(f)
   
    f_prime = lambdify(x, f_prime)
    return f_prime(V)



ab_Plotting()
bc_Plotting()

print("Pressure at 28: ",ab_Lagrangerian_Interpolation(3, 28))
print("Pressure at 32: ",bc_Lagrangerian_Interpolation(3, 32))

    

# 0 for mass,1 for velocity


ab_relative_errors()


bc_relative_errors()

print()

print("work :" , (get_work_ab(30)-get_work_ab(25))+(get_work_bc(35)-get_work_bc(30)))

    
    

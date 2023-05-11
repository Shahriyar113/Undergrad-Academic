import numpy as np
import matplotlib.pyplot as plt
import numpy as np
import math
import pandas as pd




"""
X_Input=input().split()

for i in range(len(X_Input)):
        X_Values[i]=int(X_Input)
        
Y_Input=input().split()

for i in range(len(Y_Input)):
        Y_Values[i]=int(Y_Input)
        
"""


X_Values =[0,10,15,20,22.5,30]
Y_Values =[0,227.04,362.78,517.35,602.97,901.67]
Given_X=16


#Ordering the given points (X_Values and Y_Values) such that the closer
#points of Given_X can be found easily from Ordered_X and Ordered_Y

#And thus if we need linear interpolation we can use n=1 and two interpolating
#point will be (Ordered_X[0],Ordered_Y[0]) and (Ordered_X[1],Ordered_Y[1])

#Similarly if we need Two order(Quadratic) interpolation we can use n=2 and three interpolating
#point will be (Ordered_X[0],Ordered_Y[0]) , (Ordered_X[1],Ordered_Y[1]),(Ordered_X[2],Ordered_Y[2])

Ordering = {}



for i in range(len(X_Values)):
    Ordering[i]=abs(X_Values[i] - Given_X)

                    
#print(Ordering)

Ordering=dict(sorted(Ordering.items(), key = 
             lambda dic:(dic[1], dic[0])))

Ordered_Index=list(Ordering.keys());


Ordered_X=[]

Ordered_Y=[]


for i in range(len(X_Values)):
    Ordered_X.append(X_Values[Ordered_Index[i]])
    Ordered_Y.append(Y_Values[Ordered_Index[i]])


#Ordering complete



def function_value_1(X0):
    return Y_Values[X_Values.index(X0)]
     
def function_value_2(X1,X0):
    Y= (function_value_1(X1) - function_value_1(X0))/(X1-X0)
    return Y
    
def function_value_3(X2,X1,X0):
    Y= (function_value_2(X2,X1) - function_value_2(X1,X0))/(X2-X0)
    return Y
    
def function_value_4(X3,X2,X1,X0):
    Y= (function_value_3(X3,X2,X1) - function_value_3(X2,X1,X0))/(X3-X0)
    return Y

def function_value_5(X4,X3,X2,X1,X0):
    Y= (function_value_4(X4,X3,X2,X1) - function_value_4(X3,X2,X1,X0))/(X4-X0)
    return Y

    
   

"""
def b0():
    return function_value(0)

def b1():
    return (function_value(1)-function_value(0)) / ()
"""   

#for linear interpolation n=1
#for two order n=2
#for three order n=3
#----


# X is the value for which Y=f(x) have to calculate


def Newton_Interpolation(n,X):
    
    X_list=Ordered_X
    
    #Y_list=Ordered_Y
    
    
    Iteration = n+1
    
    b=[]
    
    b.append(function_value_1(X_list[0])) 
    
    b.append(function_value_2(X_list[1],X_list[0]))
    
    b.append(function_value_3(X_list[2], X_list[1], X_list[0]))
    
    b.append(function_value_4(X_list[3], X_list[2], X_list[1], X_list[0])) 
    
    b.append(function_value_5(X_list[4],X_list[3], X_list[2], X_list[1], X_list[0])) 
    
    Product_Res=1
    Y=b[0]  # total sum
    
    for i in range(1,Iteration):
        
        Product_Res = b[i]
        
        for j in range(i):
            Product_Res = Product_Res * (X-X_list[j])
        
        Y = Y + Product_Res
        Product_Res = 1
        
    return Y
        
    
    
def relative_errors(): 
    Ans=[]
    Errors=['------']
    
    Ans.append(Newton_Interpolation(1,16)) #linear 
    Ans.append(Newton_Interpolation(2,16))
    Ans.append(Newton_Interpolation(3,16))
    Ans.append(Newton_Interpolation(4,16)) #fourh order
    
    Iteration=[1,2,3,4]
    
    for i in range(len(Ans)-1):
        
        err = abs((Ans[i+1]-Ans[i])*100)/Ans[i+1]
        Errors.append(err)
        
    d={'Y' : pd.Series(Ans, index=Iteration),
       'Error' : pd.Series(Errors, index=Iteration)
       }
    
    df=pd.DataFrame(d)
    print(df)
  


def Graph_Plotting():
    
    x_coordinates=np.array(X_Values)
    y_coordinates=np.array(Y_Values)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates)
    
    X_s=[10,15,20]
    Y_s=[227.04,362.78,517.35]
    plt.plot(X_s ,Y_s,"ro")
    




relative_errors()
Graph_Plotting()

    
    
    
    
    
    
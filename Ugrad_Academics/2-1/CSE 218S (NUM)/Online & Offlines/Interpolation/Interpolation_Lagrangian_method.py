import numpy as np
import matplotlib.pyplot as plt
import numpy as np
import math
import pandas as pd

X_Values =[0,10,15,20,22.5,30]
Y_Values =[0,227.04,362.78,517.35,602.97,901.67]
Given_X = 16

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
    

#Ordering Complete

def function_value(X0):
    return Y_Values[X_Values.index(X0)]


#for linear interpolation n=1
#for two order n=2
#for three order n=3
#----


# X is the value for which Y=f(x) have to calculate

def Lagrangerian_Interpolation(n,X):
    
    X_list=Ordered_X
    
    #Y_list=Ordered_Y
    
    
    Iteration=n+1
    
    Y=0
    Product_Res = 1
    
    for i in range(Iteration):
        
        Product_Res = function_value(X_list[i])
        for j in range(Iteration):
            if i==j:
                continue
            Product_Res = Product_Res * (X-X_list[j])/(X_list[i]-X_list[j])
        
        Y = Y + Product_Res
        Product_Res=1
    
    return Y


def relative_errors(): 
    Ans=[]
    Errors=['------']
    
    Ans.append(Lagrangerian_Interpolation(1, 16)) #linear
    Ans.append(Lagrangerian_Interpolation(2, 16)) #two order
    Ans.append(Lagrangerian_Interpolation(3, 16))
    Ans.append(Lagrangerian_Interpolation(4, 16))
    Ans.append(Lagrangerian_Interpolation(5, 16)) #fivth order

    
    Iteration=[1,2,3,4,5]
    
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


    
    
    
           
            


import matplotlib.pyplot as plt
import numpy as np
import math
import pandas as pd



file = open ("Data.txt","r")

X=[]
Y=[]

for line in file.readlines():
    l = line.split()
    X.append(float(l[0]))
    Y.append(float(l[1]))
    

n = len(X)


def Data_Points_Plotting_For_Linear_Regression():
    
    x_coordinates=np.array(X)
    y_coordinates=np.array(Y)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,"ro")
    
   

def Linear_Regression():
    Sum_of_XiYi=0
    Sum_of_Xi=0
    Sum_of_Yi=0
    Sum_of_Xi_square=0
    
    for i in range(n):
        Sum_of_XiYi = Sum_of_XiYi + (1/X[i]**2)*(1/Y[i])
        Sum_of_Xi = Sum_of_Xi + 1/X[i]**2
        Sum_of_Yi = Sum_of_Yi + 1/Y[i]
        Sum_of_Xi_square = Sum_of_Xi_square + 1/(X[i]**4)
        
    
    a1=(n*Sum_of_XiYi - Sum_of_Xi*Sum_of_Yi)/(n*Sum_of_Xi_square - Sum_of_Xi**2)
    
    a0=(Sum_of_Xi_square*Sum_of_Yi - Sum_of_Xi*Sum_of_XiYi)/(n*Sum_of_Xi_square - Sum_of_Xi**2)
    
    
    a = 1/a0
    b = a*a1
    
    return a,b


a,b = Linear_Regression()

print(a," ",b)


def func(x):
    return (a*x*x)/(b+x*x)

def plotting():
    
    y_coordinates=[]
    
    Upper_bound = max(X)
    
    Lower_bound = min(X)
    
    x_coordinates = np.linspace(Lower_bound ,Upper_bound ,100)  


    for i in range(len(x_coordinates)):
        
        y_coordinates.append(func(x_coordinates[i]))
    
    y_coordinates=np.array(y_coordinates)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,color="blue")



Data_Points_Plotting_For_Linear_Regression()
plotting()





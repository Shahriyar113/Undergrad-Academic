import matplotlib.pyplot as plt
import numpy as np
import math
import pandas as pd



Power_X=[1,2,3,4,5]
Power_Y=[0.5,1.7,3.4,5.7,8.4]

n=5

#Power Model


def Data_Points_Plotting_For_Power_Model_Regression():
    
    x_coordinates=np.array(Power_X)
    y_coordinates=np.array(Power_Y)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,"ro")

def Transformed_Power_Model_Regression():
    
    Sum_of_XiYi=0
    Sum_of_Xi=0
    Sum_of_Yi=0
    Sum_of_Xi_square=0
    
    for i in range(n):
        Sum_of_XiYi = Sum_of_XiYi + math.log10(Power_X[i]) *math.log10(Power_Y[i])
        Sum_of_Xi = Sum_of_Xi +  math.log10(Power_X[i])
        Sum_of_Yi = Sum_of_Yi + math.log10(Power_Y[i])
        Sum_of_Xi_square = Sum_of_Xi_square +  math.log10(Power_X[i])**2
        
    
    a1=(n*Sum_of_XiYi - Sum_of_Xi*Sum_of_Yi)/(n*Sum_of_Xi_square - Sum_of_Xi**2)
    
    a0=(Sum_of_Xi_square*Sum_of_Yi - Sum_of_Xi*Sum_of_XiYi)/(n*Sum_of_Xi_square - Sum_of_Xi**2)
    
    
    a = 10**a0
    b = a1
    
    return a,b



a,b = Transformed_Power_Model_Regression()
print(a," ",b)
    
def Transformed_Power_Function(x):
    
    return a*(x**b)



def Transformed_Power_Model_Regression_Curve_plotting():
    
    
    y_coordinates=[]
    
    Upper_bound = max(Power_X)
    
    Lower_bound = min(Power_Y)
    
    x_coordinates = np.linspace(Lower_bound ,Upper_bound ,100)  


    for i in range(len(x_coordinates)):
        
        y_coordinates.append(Transformed_Power_Function(x_coordinates[i]))
    
    y_coordinates=np.array(y_coordinates)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,color="blue")
            

Data_Points_Plotting_For_Power_Model_Regression()
Transformed_Power_Model_Regression_Curve_plotting()

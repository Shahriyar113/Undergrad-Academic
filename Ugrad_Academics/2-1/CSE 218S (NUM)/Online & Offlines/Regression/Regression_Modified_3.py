import matplotlib.pyplot as plt
import numpy as np
import math
import pandas as pd

#Generally given data point theke Regression process a curve fit korar step gulo:
    
    #1. Given data point gulor plot dekhe identify kora j kon function ba model use korbo
    #   (Kokhono function ba model deyai thake jate point gulo fit korate hobe)
    #2. Theoritically constant gulor (e.g. a0,a1 for linear,a,b for exponential) expression generate korte hobe
    #3. then expression gulor maddhome given data points gulo use kore constant gulo value ber korte hobe
    #4. constant gulor maddhome fit kora function (it is called predicted function) build korte hobe
    #5. Then oi function use kore curve plot korte hobe



#(edit)

X =[0,0.183,0.36,0.5324,0.702,0.867,1.0244,1.1774,1.329,1.479,1.5,1.56]

Y =[0,306,612,917,1223,1529,1835,2140,2446,2752,2767,2896]



Exp_X = [0,1,3,5,7,9]
Exp_Y = [1,0.891,0.708,0.562,0.447,0.355]

Pol_X = [80,40,-40,-120,-200,-280,-340]
Pol_Y = [6.47E-6 ,6.24E-6 ,5.72E-6 ,5.09E-6, 4.30E-6, 3.33E-6 ,2.45E-6] 

#/(edit)


#edit
n=6  #n = total data points

#edit
Linear = False
Exponential = True
Polynomial=False
#/edit



#let the linear function is y=a0 + a1*x



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
        Sum_of_XiYi = Sum_of_XiYi + X[i]*Y[i]
        Sum_of_Xi = Sum_of_Xi + X[i]
        Sum_of_Yi = Sum_of_Yi + Y[i]
        Sum_of_Xi_square = Sum_of_Xi_square + X[i]**2
        
    
    a1=(n*Sum_of_XiYi - Sum_of_Xi*Sum_of_Yi)/(n*Sum_of_Xi_square - Sum_of_Xi**2)
    
    a0=(Sum_of_Xi_square*Sum_of_Yi - Sum_of_Xi*Sum_of_XiYi)/(n*Sum_of_Xi_square - Sum_of_Xi**2)
    
    return a0,a1


def Linear_regression_Passing_Origin():
    Sum_of_XiYi=0
   
    Sum_of_Xi_square=0
    
    for i in range(n):
        Sum_of_XiYi = Sum_of_XiYi + X[i]*Y[i]
        Sum_of_Xi_square = Sum_of_Xi_square + X[i]**2
        
    
    a1=Sum_of_XiYi/Sum_of_Xi_square
    
    return a1


if Linear == True:
    a0,a1 = Linear_Regression()
    
def Linear_Function(x):
    return a0 + a1*x


            
def Linear_Regression_Curve_Plotting():
    
    
    
    y_coordinates=[]
    
    Upper_bound = max(X)
    
    Lower_bound = min(X)
    
    x_coordinates = np.linspace(Lower_bound ,Upper_bound ,100)  


    for i in range(len(x_coordinates)):
        
        y_coordinates.append(Linear_Function(x_coordinates[i]))
    
    y_coordinates=np.array(y_coordinates)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,color="blue")
    

if Linear == True:
    a1 = Linear_regression_Passing_Origin()    

    
    
def Linear_Function_Passing_Origin(x):
    
    return a1*x
    

def Linear_regression_Passing_Origin_Curve_plotting():
    
    
    y_coordinates=[]
    
    Upper_bound = max(X)
    
    Lower_bound = min(X)
    
    x_coordinates = np.linspace(Lower_bound ,Upper_bound ,100)  


    for i in range(len(x_coordinates)):
        
        y_coordinates.append(Linear_Function_Passing_Origin(x_coordinates[i]))
    
    y_coordinates=np.array(y_coordinates)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,color="blue")
    

# Exponential Regression


def Data_Points_Plotting_For_Exponential_Regression():
    
    x_coordinates=np.array(Exp_X)
    y_coordinates=np.array(Exp_Y)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,"ro")
    

# bisection function for determining "b"

def f(b):
    Sum_of_XiYi_exp = 0
    Sum_of_Yi_exp = 0
    Sum_of_exp = 0
    Sum_of_Xi_exp =0
    
    Function_Value = 0
    
    for i in range(n):
        Sum_of_XiYi_exp = Sum_of_XiYi_exp + Exp_X[i]*Exp_Y[i]*math.exp(b*Exp_X[i])
        Sum_of_Yi_exp = Sum_of_Yi_exp + Exp_Y[i]*math.exp(b*Exp_X[i])
        Sum_of_exp = Sum_of_exp + math.exp(2*b*Exp_X[i])
        Sum_of_Xi_exp = Sum_of_Xi_exp + Exp_X[i]*math.exp(2*b*Exp_X[i])
        
        Function_Value = Sum_of_XiYi_exp - (Sum_of_Yi_exp/Sum_of_exp)*Sum_of_Xi_exp
        
    return Function_Value
    
        
def plotting_For_Bisection():
    x_coordinates = np.linspace(-1.5,5,100)  #edit
    
    y_coordinates=[]
    
    for i in range(len(x_coordinates)):
        y_coordinates.append(f(x_coordinates[i]))
        
    y_coordinates=np.array(y_coordinates)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates)



def Bisection(xL,xU,r_a_error,maxIteration):
    xM=(xL+xU)/2
    xM_old=(xL+xU)/2
    for i in range(maxIteration):
        xM=(xL+xU)/2;
        xM_new=xM
       
        
        if f(xL)*f(xM)==0:
            return xM
        
        if f(xL)*f(xM)<0:
            xL=xL
            xU=xM
            
        else:
            xL=xM
            xU=xU
            
        if i>0:
            if abs((xM_old-xM_new)*100/xM_new) < r_a_error:
                return xM_new
            xM_old=xM_new
    
    return xM

      
  
    #let the curve is y = a*math.exp(b*x)

def Exponential_Regression():
    
    b = Bisection(-2, 4.5, 0.005, 30) # edit
    
    Sum_of_Yi_exp = 0
    Sum_of_exp = 0
    
    for i in range(n):
        
        Sum_of_Yi_exp = Sum_of_Yi_exp + Exp_Y[i]*math.exp(b*Exp_X[i])
        Sum_of_exp = Sum_of_exp + math.exp(2*b*Exp_X[i])
        
    
    a = Sum_of_Yi_exp/Sum_of_exp
    
    return a,b

if Exponential == True:
    a,b = Exponential_Regression()


def Exponential_Function(x):
    
   
    
    return a*math.exp(b*x)

def Exponential_Regression_Curve_plotting():
    
    
    y_coordinates=[]
    
    Upper_bound = max(Exp_X)
    
    Lower_bound = min(Exp_X)
    
    x_coordinates = np.linspace(Lower_bound ,Upper_bound ,100)  


    for i in range(len(x_coordinates)):
        
        y_coordinates.append(Exponential_Function(x_coordinates[i]))
    
    y_coordinates=np.array(y_coordinates)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,color="blue")
        


# let y = ae^(bx) is equivalent to z = a0 + a1*x 
# where a=e^a0 , b=a1 and z=ln(y)     
# So basically it is a linear regression 
   
def Transformed_Exponential_Regression():
    
    Sum_of_XiYi=0
    Sum_of_Xi=0
    Sum_of_Yi=0
    Sum_of_Xi_square=0
    
    for i in range(n):
        Sum_of_XiYi = Sum_of_XiYi + Exp_X[i]*math.log(Exp_Y[i])
        Sum_of_Xi = Sum_of_Xi + Exp_X[i]
        Sum_of_Yi = Sum_of_Yi + math.log(Exp_Y[i])
        Sum_of_Xi_square = Sum_of_Xi_square + Exp_X[i]**2
        
    
    a1=(n*Sum_of_XiYi - Sum_of_Xi*Sum_of_Yi)/(n*Sum_of_Xi_square - Sum_of_Xi**2)
    
    a0=(Sum_of_Xi_square*Sum_of_Yi - Sum_of_Xi*Sum_of_XiYi)/(n*Sum_of_Xi_square - Sum_of_Xi**2)
    
    
    a = math.exp(a0)
    b = a1
    
    return a,b
    
if Exponential == True:
    a,b = Transformed_Exponential_Regression()

    
def Transformed_Exponential_Function(x):
    
    
    
    return a*math.exp(b*x)

def Transformed_Exponential_Regression_Curve_plotting():
    
    
    y_coordinates=[]
    
    Upper_bound = max(Exp_X)
    
    Lower_bound = min(Exp_X)
    
    x_coordinates = np.linspace(Lower_bound ,Upper_bound ,100)  


    for i in range(len(x_coordinates)):
        
        y_coordinates.append(Transformed_Exponential_Function(x_coordinates[i]))
    
    y_coordinates=np.array(y_coordinates)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,color="blue")
            
    
#Polynomial Regression



def Data_Points_Plotting_For_Polynomial_Regression():
    
    x_coordinates=np.array(Pol_X)
    y_coordinates=np.array(Pol_Y)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,"ro")
    
    
def Gaussian_Elimination(A,B,size):  # n ==> size of the matrices
    
    
    
     for i in range(size):
        for j in range(i+1,size):
            #for 1st iteration
            
            #taking the 1st row
             Row_initial=A[i , : ] #taking the 1st row (the refernce row)
             
             #multiply each coefficient of 1st row with a21/a11(for me A[1,0]/A[0,0])
             Row_initial=[(A[j,i]/A[i,i]) * Row_initial[k] for k in range(len(Row_initial))]
             
             #updating the B matrix parallelly
             B[j,0]=B[j,0]-(B[i,0] * (A[j,i]/A[i,i]))
             
             #taking the 2nd row 
             Row_final=A[j , : ]
             
             #Then subtructing the modifying 1st row(Row_initial) from
             #2nd row and updating the 2nd row
             
             
             #after this the 1st coefficient of 2nd row become "0"
             A[j, : ] = [Row_final[k] - Row_initial[k] for k in range(len(Row_initial))]
             
          
     #Backward substitution 
     X=np.zeros((size,1))
     
     #determining the Xn
     #rounding each solutions upto 4 decimal points
     X[size-1,0]=B[size-1,0] /A[size-1,size-1]
    
     
    
     # as range() is end exclusive.that's why "-1" is used for stop
     #because in this case for outer loop the last iteration
     #index should be zero
     #iterating index
     sum=0.0
     for i in range(size-2,-1,-1):  # as range is end exclusive
         for j in range(i+1,size):
             
             sum=sum+ A[i,j] * X[j]
    
          
    #rounding each solutions upto 4 decimal points
    #determining other solutions

         X[i,0]=(B[i,0]-sum)/A[i,i]
         sum=0.0
         
    
     return X
     
         
        
         
    

# m --> the order of fitting polynomial 

def Polynomial_Regression(m):
    A=np.zeros((m+1,m+1))
    B=np.zeros((m+1,1))
    
    
    for i in range(m+1):
        for j in range(m+1):
            
             for k in range(n):
                    A[i,j] = A[i,j] + Pol_X[k]**(i+j)      
           
        

    
    for c in range(m+1):
        for p in range(n):
            B[c,0] = B[c,0] + (Pol_X[p]**c) * (Pol_Y[p])
           
                
            
    a = Gaussian_Elimination(A, B, m+1)
    return a
                

#here "y = a0 + a1*x + a2*x^2 + ...... an * x^n" is determining


if Polynomial == True:
    degree_of_polynomial = 3
    a = Polynomial_Regression(degree_of_polynomial)


def polynomial_Function(x):
    
    
    # here 2 degree polynomial is used for regression
    Function_Value = 0
    
    for i in range(degree_of_polynomial+1):
        Function_Value = Function_Value + a[i,0]*(x**i)
        
    return Function_Value
    
    
  
def Polynomial_Regression_Curve_Plotting():
    
    y_coordinates=[]
    
    Upper_bound = max(Pol_X)
    
    Lower_bound = min(Pol_X)
    
    x_coordinates = np.linspace(Lower_bound ,Upper_bound ,100)  


    for i in range(len(x_coordinates)):
        
        y_coordinates.append(polynomial_Function(x_coordinates[i]))
    
    y_coordinates=np.array(y_coordinates)
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,color="blue")
            

Data_Points_Plotting_For_Exponential_Regression()
Exponential_Regression_Curve_plotting()
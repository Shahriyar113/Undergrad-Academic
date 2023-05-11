import matplotlib.pyplot as plt
import numpy as np
import math
import pandas as pd


x_coordinates = np.linspace(1,10,100)
y_coordinates=[]



def f(x):
    
    return ((math.pi*x**2*(9-x))/3)-4



for i in range(len(x_coordinates)):
        """
        if(x_coordinates[i]==1):
        x_coordinates[i]=np.nan
        y_coordinates.append(np.nan)
        """
        
        y_coordinates.append(f(x_coordinates[i]))
        if(abs(y_coordinates[i]-y_coordinates[i-1]) > 50):
            y_coordinates[i-1]=np.nan
            x_coordinates[i-1]=np.nan
        

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

print("root: ",Bisection(8, 10, 0.5, 20))
            
def Print_Table(xL,xU,r_a_error,maxIteration):
    Iteration=[]
    xL_List=[]
    xU_List=[]
    xM_List=[]
    error_List=['-----']
    fx_List=[]
    
    
    xM=(xL+xU)/2
    xM_old=(xL+xU)/2
    for i in range(maxIteration):
        Iteration.append(i+1)
        xL_List.append(xL)
        xU_List.append(xU)
        
        xM=(xL+xU)/2;
        xM_new=xM
        
        xM_List.append(xM)
        fx_List.append(f(xM))
       
        
        if f(xL)*f(xM)==0:
            break
        
        if f(xL)*f(xM)<0:
            xL=xL
            xU=xM
            
        else:
            xL=xM
            xU=xU
            
        if i>0:
            current_error=abs(((xM_old-xM_new)/xM_new)*100)
            error_List.append(current_error)
           
            xM_old=xM_new
            
    d={'xL' : pd.Series(xL_List, index=Iteration),
       'xU' : pd.Series(xU_List, index=Iteration),
       'xM' : pd.Series(xM_List, index=Iteration),
       'Error%' : pd.Series(error_List, index=Iteration),
       'f(xM)' : pd.Series(fx_List, index=Iteration)}
    
    df=pd.DataFrame(d)
    print(df)
    
print() 
Print_Table(8, 10, 0.5, 20)
                  
                
               
            

       
    
    


 import numpy as np

n = int(input())
A=np.zeros((n,n))
B=np.zeros((n,1))

#taking inputs

for i in range(n):
    l=input().split()  #taking multiple integer input at a time
    for j in range(n):
        A[i,j]=float(l[j])
        

for i in range(n):
    x=float(input())
    for j in range(1):
        B[i,j]=x
    
        
#Given eqn gulo te leading 0 thakle first a A and B matrix ta k modify 
#kore nite hobe...then Gaussian elimination appply korte hobe

# Monified A matrix = Final_A
# Modified B matrix = Final_B

def Modify(A,B):
    Final_A=np.zeros((n,n))
    Final_B=np.zeros((n,1))

    Leading_Zero_Dict={}
    for i in range(n):
      Leading_Zero_Dict[i]=0


    for i in range(n):
      for j in range(n):
        if A[i,j]==0:
            Leading_Zero_Dict[i]=Leading_Zero_Dict[i]+1;
        else:
            break
        
    Leading_Zero_Dict=dict(sorted(Leading_Zero_Dict.items(), key = 
             lambda dic:(dic[1], dic[0])))

    Leading_Zero_Index=list(Leading_Zero_Dict.keys());



    for i in range(n):
      Final_A[i:] = A[Leading_Zero_Index[i],: ]
      Final_B[i:] = B[Leading_Zero_Index[i],: ]
 
    
    return Final_A,Final_B
    


    

     


def Gaussian_Elimination(A,B,d):
    
    
    #Forward Elimination
    
    #here the inner loop making the 1st co-efficient of every
    #equation(row) "0"
    
    #and the outer loop continue the same process again and
    #again and so the later rows have more 0 co-efficient
    
    #for 1st outer loop iteration 1st row is the reference row(equation)
    #for each inner loop iteration
    #that's why it is not changed

    
    #similarly for 2nd outer loop iteration 2nd row is the reference row
    #for each inner loop iteration and so on
    #For this reason to fix the reference row the inner loop starts
    #from i+1
    
     for i in range(n):
        for j in range(i+1,n):
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
             
             
             
             
             if d:
                 print("A")
                 print(A)
                 print()
                 print()
                 print()
                 print("B")
                 print(B)
                 print()
                 print()
    
        #prottek outer loop iteration er age A r B k modify kora uchit
        #karon inner loop iteration er por A matrix er vetore leading zero
        #create hote pare
        
        A,B=Modify(A, B)
      
                 
     #Backward substitution 
     X=np.zeros((n,1))
     
     #determining the Xn
     #rounding each solutions upto 4 decimal points
     X[n-1,0]=round(B[n-1,0] /A[n-1,n-1],4)
     
    
     # as range() is end exclusive.that's why "-1" is used for stop
     #because in this case for outer loop the last iteration
     #index should be zero
     #iterating index
     sum=0.0
     for i in range(n-2,-1,-1):  # as range is end exclusive
         for j in range(i+1,n):
             
             sum=sum+ A[i,j] * X[j]
          
    #rounding each solutions upto 4 decimal points
    #determining other solutions

         X[i,0]=(B[i,0]-sum)/A[i,i]
         X[i,0]=round(X[i,0],4)
         sum=0.0
         
     print("Solutions:")
     print()
     print(X)
     
    
             
                 
                 
print()
print()     

A,B=Modify(A, B)
Gaussian_Elimination(A,B,True)       



  
         
             
             
             
             
            
    


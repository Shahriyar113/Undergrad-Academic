import matplotlib.pyplot as plt
import numpy as np
import math
import pandas as pd

def f(x):
    return 2000*math.log(14E4/(14E4-2100*x)) - 9.8*x

def forward_d_f(x):
    del_x=2
    
    return (f(x+del_x)-f(x))/del_x  #forward difference approximation

def backward_d_f(x):
    del_x=2
    
    return (f(x)-f(x-del_x))/del_x  #backward difference approximation

def central_d_f(x):
    del_x=2
    
    return (f(x+del_x)-f(x-del_x))/(2*del_x)  #central difference approximation


print(forward_d_f(16))
print(backward_d_f(16))
print(central_d_f(16))


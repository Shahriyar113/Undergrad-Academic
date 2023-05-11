import numpy as np
import matplotlib.pyplot as plt
import math
import pandas as pd
import sys

csv_file1_path = sys.argv[1]
csv_file2_path = sys.argv[2]
title = sys.argv[3]
X_label = sys.argv[4]
Y_label = sys.argv[5]
#plot_title = sys_argv[5]


df1=pd.read_csv(csv_file1_path)
df2=pd.read_csv(csv_file2_path)

x= df1["x"]
y1= df1["y"]
y2= df2["y"]



fig, ax = plt.subplots(figsize=(8, 6))

    
def Existing_Implementation_Plotting():
    x_coordinates=x
    y_coordinates=y1
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,color="red",label="Existing")
    
    
    
 
def Modified_Implementation_Plotting():
    x_coordinates=x
    y_coordinates=y2
    
    plt.grid(True)

    plt.plot(x_coordinates ,y_coordinates,color="blue",label="Modified")
    
    


Existing_Implementation_Plotting()
Modified_Implementation_Plotting()

plt.title(title)
plt.xlabel(X_label)
plt.ylabel(Y_label)

plt.legend(loc='upper right')

saving_file_path = "All_Graphs/"+title+".png"
plt.savefig(saving_file_path)
    
    

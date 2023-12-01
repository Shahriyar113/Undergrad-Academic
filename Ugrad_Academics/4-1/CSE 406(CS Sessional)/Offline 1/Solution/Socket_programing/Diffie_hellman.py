import random
import math

#Miller Rabin Primality test
def power(x, y, p):
     
    res = 1
     
    x = x % p;
    while (y > 0):
        if (y & 1):
            res = (res * x) % p
 
        # y must be even now
        y = y>>1 # y = y/2
        x = (x * x) % p
     
    return res;

def Miller_primality_test(n,d,r):
    a = random.randint(2,n-2)
    x = power(a, d, n);
    if (x==1 or x==n-1):
        return True
    
    for i in range(r):
        x = (x*x) % n
        if(x==1):
            return False
        if(x == n-1):
            return True
        
    return False    

def is_Prime(n):
    if(n<=1):
        return False
    if(n==2 or n==3):
        return True
    if(n==4):
        return False
    r=0
    d = n-1

    while(d % 2 == 0):
        d //= 2 #floor division
        r = r+1
    num_of_iteration = 100
    for i in range(num_of_iteration): # higher "num of iteration",higher accuracy
        if(Miller_primality_test(n,d,r)== False):
            return False

    return True        

#print(is_Prime(52,100))


#will return a prime of at least "k" bit
def Find_Modulus_P(k):
    #Finding "p" which is at least 128 bit long
    #We want to find a p such that p and (p-1)/2 both are prime..because if (p-1)/2 is prime than the prime factor of p-1 will be 2
    # and (p-1)/2 ..so finding "g" will be easy and efficient
    p = int(math.pow(2,k))

    while(True):
       #print(p)
        print
        if (is_Prime(p) and is_Prime((p-1)//2)):
            return p
        else:
            p = p + 1

#will return a prime of at least "k" bit

def Find_primitive_root(p):
    #here we are sure that the prime factors of p-1 are 2 and (p-1)/2
    p1=2
    p2=(p-1)//2

    min = 1
    max = p-1

    while(True):
        g = random.randint(min,max)
        if(power(g,p1,p) != 1 and power(g,p2,p) != 1):
            return g

#will return a of at least "k" bit long

def get_a_prime(k):

    p = int(math.pow(2,k))

    min = p 
    max = 2*p

    while(True):
        if(is_Prime(p)):
            return p
        else:
            p = random.randint(min,max)




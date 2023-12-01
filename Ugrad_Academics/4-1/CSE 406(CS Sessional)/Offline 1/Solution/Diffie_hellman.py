import random
import math
import time

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


#size of key
k = 128


start_time_for_p = time.time()
p = Find_Modulus_P(k) #public modulus
end_time_for_p = time.time()

start_time_for_g = time.time()
g = Find_primitive_root(p) #public base
end_time_for_g = time.time()

start_time_for_a_or_b = time.time()
a=  get_a_prime(k//2) # sender private key
end_time_for_a_or_b = time.time()

b=  get_a_prime(k//2) #reciever private key

start_time_for_A_or_B = time.time()
A = power(g,a,p) #sender will compute this and will send it to reciever
end_time_for_A_or_B = time.time()
B = power(g,b,p) ##reciever will compute this and will send it to sender

#A and B are public
start_time_for_shared_key = time.time()

sender_secret_key = power(B,a,p) #sender will compute this
reciever_secret_key = power(A,b,p) #reciever will compute this

end_time_for_shared_key = time.time()


print('Sender end secret key: ',sender_secret_key)
print('Reciever end secret key: ',sender_secret_key)

print(len(hex(sender_secret_key)[2:]))

if(sender_secret_key == reciever_secret_key):
    print("Verification successful")
else:
    print('Error! both end secret keys are not same ')

print()
#showing execution time:
print('Execution time for k =',k)
print('Computation time of p: ',end_time_for_p-start_time_for_p,' seconds')
print('Computation time of g: ',end_time_for_g-start_time_for_g,' seconds')
print('Computation time of a or b: ',end_time_for_a_or_b-start_time_for_a_or_b,' seconds')
print('Computation time of A or B: ',end_time_for_A_or_B-start_time_for_A_or_B,' seconds')
print('Computation time of shared key: ',(end_time_for_shared_key-start_time_for_shared_key),' seconds')






# if(is_verified(p,g,a,b)):
#     print("Verification Successful")
# else:
#     print("Error! Both secret keys are not same")





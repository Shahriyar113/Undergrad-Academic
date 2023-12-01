import socket
import AES
import Diffie_hellman

bob_socket = socket.socket()
bob_socket.bind(('localhost',5113))

#Bob will listen for one client
bob_socket.listen(1)

print('Bob is waiting for connection')

bob_socket,address = bob_socket.accept()
print('Bob connected with Alice')

#Bob is generating his private key
size_of_key = 128
b = Diffie_hellman.get_a_prime(size_of_key/2)

print()
#Bob is recieving p,g,A from Alice
p = int(bob_socket.recv(1024).decode()) # recv() function return 'byte' type...converting byte to string using 'decode()'
bob_socket.send(bytes(' ','utf-8')) # just for ensuring send and recieve sequential
g = int(bob_socket.recv(1024).decode())
bob_socket.send(bytes(' ','utf-8'))
A = int(bob_socket.recv(1024).decode())
bob_socket.send(bytes(' ','utf-8'))

print('Bob recieved p = ',p)
print('Bob recieved g = ',g)
print('Bob recieved A = ',A)

bob_socket.recv(1024)
#Bob is generating B and sending it to Alice
B = Diffie_hellman.power(g,b,p)
bob_socket.send(bytes(str(B),'utf-8'))
print('Bob sent B = ',B)

#Now Bob will generate his secret key
key = Diffie_hellman.power(A,b,p) 
print('Secret key: ',key)

#coverting 'Secret key to hex code'
key_hex_code = AES.secret_key_2_hex_code(key)

#generaing all round keys
keys = AES.Generate_all_round_keys(key_hex_code)


#Bob is recieving encrypted cipher text from Alice
#-------------------------------------------------
#recieving plain_text_size from Alice(#for handling the case when the plaintext is encrypted after adding dummy characters )
plain_text_size = int(bob_socket.recv(1024).decode())


decryted_message = ''
while True:
    recieved_text = bob_socket.recv(1024).decode()
    if(recieved_text == 'end'):
        break
    else:
        recieved_cipher_text = recieved_text
        decrypted_block,decrypted_hex_code = AES.decrypt(recieved_cipher_text,keys)
        decryted_message = decryted_message + decrypted_block
        bob_socket.send(bytes(' ','utf-8')) # just for ensuring send and recieve sequential

Final_decrypted_message = decryted_message[0:plain_text_size] #truncating the dummy characters
print()       
print('Bob recieved the message: ',Final_decrypted_message)
     


bob_socket.close()


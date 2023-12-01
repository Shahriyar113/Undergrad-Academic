import socket
import AES
import Diffie_hellman



alice_socket = socket.socket()

#Alice will listen for one client
alice_socket.connect(('localhost',5113))
print('Alice is connected with Bob')

#Agreement with key 
#----------------------

#Alice is generating her private key
size_of_key = 128
a = Diffie_hellman.get_a_prime(size_of_key/2)

#Alice is generating p,g and A
size_of_key = 128
p = Diffie_hellman.Find_Modulus_P(size_of_key)
g = Diffie_hellman.Find_primitive_root(p)
A = Diffie_hellman.power(g,a,p)

#Alice is sending p,g and A to Bob

alice_socket.send(bytes(str(p),'utf-8'))
alice_socket.recv(1024) # just for ensuring send and recieve sequential
alice_socket.send(bytes(str(g),'utf-8'))
alice_socket.recv(1024)
alice_socket.send(bytes(str(A),'utf-8'))
alice_socket.recv(1024)

print('Alice sent p = ',p)
print('Alice sent g = ',g)
print('Alice sent A = ',A)

alice_socket.send(bytes(' ','utf-8'))
#Alice is recieving 'B' from Bob
B = int(alice_socket.recv(1024).decode()) 
print('Alice recieved B= ',B)


#Now Bob will generate his secret key
key = Diffie_hellman.power(B,a,p) 
print('Secret key: ',key)


#coverting 'Secret key to hex code'
key_hex_code = AES.secret_key_2_hex_code(key)

#generaing all round keys
keys = AES.Generate_all_round_keys(key_hex_code)

#Alice is sending a message
#------------------------------
print()
message_to_be_sent = 'Can They Do This Again '
plain_text_size = len(message_to_be_sent)
print('Alice is sending: ',message_to_be_sent)


#sending plain_text_size to Bob(#for handling the case when the plaintext is encrypted after adding dummy characters )
alice_socket.send(bytes(str(plain_text_size),'utf-8'))


blocks = AES.get_plain_text_blocks(message_to_be_sent)

for block in blocks:
    block_hex_code = AES.text_2_hex_code(block)
    cipher_text = AES.encrypt(block_hex_code,keys)
    alice_socket.send(bytes(str(cipher_text),'utf-8'))
    alice_socket.recv(1024) #just for ensuring send and recieve sequential

alice_socket.send(bytes('end','utf-8'))


alice_socket.close()








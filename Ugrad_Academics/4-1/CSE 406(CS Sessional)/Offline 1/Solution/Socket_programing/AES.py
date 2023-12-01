from BitVector import *
import numpy as np
import math

block_size_in_bit = 128 #always fixed
block_size = int(block_size_in_bit/8) #num of characters in a block

key_size_in_bits = 128 # can be varied(for bonus part)
key_length = int(key_size_in_bits/8) #num of characters in key 
w = [] #list of all words
total_round = 10   

Sbox = (
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16,
)

InvSbox = (
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D,
)

Mixer = [
    [BitVector(hexstring="02"), BitVector(hexstring="03"), BitVector(hexstring="01"), BitVector(hexstring="01")],
    [BitVector(hexstring="01"), BitVector(hexstring="02"), BitVector(hexstring="03"), BitVector(hexstring="01")],
    [BitVector(hexstring="01"), BitVector(hexstring="01"), BitVector(hexstring="02"), BitVector(hexstring="03")],
    [BitVector(hexstring="03"), BitVector(hexstring="01"), BitVector(hexstring="01"), BitVector(hexstring="02")]
]

InvMixer = [
    [BitVector(hexstring="0E"), BitVector(hexstring="0B"), BitVector(hexstring="0D"), BitVector(hexstring="09")],
    [BitVector(hexstring="09"), BitVector(hexstring="0E"), BitVector(hexstring="0B"), BitVector(hexstring="0D")],
    [BitVector(hexstring="0D"), BitVector(hexstring="09"), BitVector(hexstring="0E"), BitVector(hexstring="0B")],
    [BitVector(hexstring="0B"), BitVector(hexstring="0D"), BitVector(hexstring="09"), BitVector(hexstring="0E")]
]

#round constants for 10 rounds(0 to 10)
round_constants = [('00','00','00','00'),
                   ('01','00','00','00'),
                   ('02','00','00','00'),
                   ('04','00','00','00'),
                   ('08','00','00','00'),
                   ('10','00','00','00'),
                   ('20','00','00','00'),
                   ('40','00','00','00'),
                   ('80','00','00','00'),
                   ('1B','00','00','00'),                  
                   ('36','00','00','00')
                   ]

Fixed_matrix = np.array([['02','03','01','01'],
                         ['01','02','03','01'],
                         ['01','01','02','03'],
                         ['03','01','01','02']]
                        )


#function for performing XOR between two words(tuple) of same length and return the resultant word
def XOR(word1,word2): # XOR between 2 words
    result=[]
    for i in range(len(word1)):
        new_byte = int(word1[i],16) ^ int(word2[i],16)
        result.append(hex(new_byte)[2:])
    return tuple(result)

#examole of byte string = 'B7' where B and & are hex digit
def XOR_between_two_byteString(byteString1,byteString2):
    resultant_byte = int(byteString1,16) ^ int(byteString2,16)
    byte_string = hex(resultant_byte)[2:]
    if (len(byte_string) == 1):  #if any byte string is "8" then this should be convert into "08"
        byte_string = '0' + byte_string
    return byte_string    

def XOR_between_two_matrix(matrix1,matrix2):
    matrix_size = matrix1.shape[0]
    Resultant_matrix = np.zeros((matrix_size,matrix_size),dtype=object) # initializing a matrix of strings 
    for i in range(matrix_size):
        for j in range(matrix_size):
            Resultant_matrix[i,j] = XOR_between_two_byteString(matrix1[i,j],matrix2[i,j])
    return Resultant_matrix

def byte_string_2_SBox_entry(byte_string):
    index = int(byte_string,16)
    Sbox_decimal_value = Sbox[index] #here Sbox[index] will return a "decimal value"
    Sbox_hex_value = hex(Sbox_decimal_value)
    Sbox_hex_value_string = str(Sbox_hex_value)[2:]
    return Sbox_hex_value_string

def byte_string_2_inverse_SBox_entry(byte_string):
    index = int(byte_string,16)
    invSbox_decimal_value = InvSbox[index] #here Sbox[index] will return a "decimal value"
    invSbox_hex_value = hex(invSbox_decimal_value)
    invSbox_hex_value_string = str(invSbox_hex_value)[2:]
    return invSbox_hex_value_string


def generate_key_from_words(list_of_words):
   key=''
   for word in list_of_words:
        for byte_string in word:
            if (len(byte_string) == 1):
                byte_string = '0'+byte_string #if any byte string is "8" then this should be convert into "08"
            key = key +' '+byte_string
   return key.lstrip()

def print_key_of_all_round(keys):
    for i in range(len(keys)):
        print('round ',i,': ',keys[i])


#input: list of words of previous key , round_no ...Output: list_of_words_for_next_key , next_key
def generate_next_key(list_of_words_of_prev_key,round_no):
   
   #performing circular byte left shift of w[3]
   last_word = list_of_words_of_prev_key[3]
   left_shifted_tuple = last_word[1:] + last_word[:1]

   #performing byte substitution from Sbox
   substituted_tuple=[]

   for byte_string in left_shifted_tuple:
     Sbox_hex_value_string = byte_string_2_SBox_entry(byte_string)
     substituted_tuple.append(Sbox_hex_value_string)
 
   substituted_tuple = tuple(substituted_tuple)


  
   #Adding round constant 

   g_w3 = XOR(substituted_tuple,round_constants[round_no]);

   
   #here new_w1,new_w2,new_w3,new_w4 are the 4 keys of next round key
   new_w0 = XOR(list_of_words_of_prev_key[0],g_w3)
   w.append(new_w0);

   new_w1 = XOR(list_of_words_of_prev_key[1],new_w0)
   w.append(new_w1);

   new_w2 = XOR(list_of_words_of_prev_key[2],new_w1)
   w.append(new_w2);

   new_w3 = XOR(list_of_words_of_prev_key[3],new_w2)
   w.append(new_w3); 

   list_of_next_key_words = []
   list_of_next_key_words.append(new_w0)
   list_of_next_key_words.append(new_w1)
   list_of_next_key_words.append(new_w2)
   list_of_next_key_words.append(new_w3)
          

    
   next_key = generate_key_from_words(list_of_next_key_words)
   return list_of_next_key_words,next_key 

#input : a text ,output : hex_code of that text

def text_2_hex_code(text):
    text_hex_code = ''

    for character in text:
        character_hex_code = hex(ord(character)) #ord() converts an character to its ascii integer
        byte_string = character_hex_code[2:]
        if (len(byte_string) == 1):  #if any byte_string is "8" then this should be convert into "08"
             byte_string = '0' + byte_string
        text_hex_code = text_hex_code +' '+ byte_string

    text_hex_code = text_hex_code.lstrip() #trancatting leading space
    return text_hex_code

def hex_code_2_text(hex_code):
    list_of_bytes_of_hex_code = hex_code.split(' ') 
    text = ''
    for byte_string in list_of_bytes_of_hex_code: #each byte string correspond to character
        ascii_value = int(byte_string,16)
        text = text+chr(ascii_value)
    return text    




def hex_code_2_state_matrix(hex_code):
    list_of_bytes_in_hex_code = hex_code.split()
    matrix_size = int(len(list_of_bytes_in_hex_code)/4)
    state_matrix = np.zeros((matrix_size,matrix_size),dtype=object) # initializing a matrix of strings

    index = 0
    for i in range(matrix_size):
        for j in range(matrix_size):
            state_matrix[j,i] = list_of_bytes_in_hex_code[index]
            index = index + 1  

    return state_matrix    

def state_matrix_2_hex_code(state_matrix):
    matrix_size = state_matrix.shape[0]

    hex_code =''
    for i in range(matrix_size):
        for j in range(matrix_size):
           hex_code = hex_code + ' ' + state_matrix[j,i]

    return hex_code.lstrip()    

def hex_code_2_round_key_matrix(round_key_hex_code):
    list_of_bytes_in_roundkey_hex_code = round_key_hex_code.split()
    matrix_size = int(len(list_of_bytes_in_roundkey_hex_code)/4)
    Round_key_matrix = np.zeros((matrix_size,matrix_size),dtype=object) # initializing a matrix of strings

    index = 0
    for i in range(matrix_size):
        for j in range(matrix_size):
            Round_key_matrix[j,i] = list_of_bytes_in_roundkey_hex_code[index]
            index = index + 1  

    return Round_key_matrix   

#input : state matrix of a round ,output : substituted byte matrix of that round
def Substitute_bytes(matrix):
    matrix_size = matrix.shape[0]
    substited_byte_matrix = np.zeros((matrix_size,matrix_size),dtype=object) # initializing a matrix of strings 
   
    for i in range(matrix_size):
        for j in range(matrix_size):
            substited_byte_matrix[i,j] = byte_string_2_SBox_entry(matrix[i,j])
    return substited_byte_matrix

def Inverse_substitute_bytes(row_shifted_matrix):
    matrix_size = row_shifted_matrix.shape[0]
    inverse_substituted_byte_matrix = np.zeros((matrix_size,matrix_size),dtype=object) # initializing a matrix of strings 
   
    for i in range(matrix_size):
        for j in range(matrix_size):
            inverse_substituted_byte_matrix[i,j] = byte_string_2_inverse_SBox_entry(row_shifted_matrix[i,j])
    return inverse_substituted_byte_matrix


def Shift_rows(Substituted_byte_matrix):
    matrix_size = Substituted_byte_matrix.shape[0]

    for i in range(matrix_size):
        list_of_row_elements = Substituted_byte_matrix[i].tolist()
        left_shifted_list_of_row_elements = list_of_row_elements[i:] + list_of_row_elements[:i] # circular left shifting by i byte
        Substituted_byte_matrix[i] = np.array(left_shifted_list_of_row_elements)        
    return Substituted_byte_matrix

def Inverse_Shift_rows(state_matrix):
    matrix_size = state_matrix.shape[0]

    for i in range(matrix_size):
        list_of_row_elements = state_matrix[i].tolist()
        left_shifted_list_of_row_elements = list_of_row_elements[-i:] + list_of_row_elements[:-i] # circular right shifting by i byte
        state_matrix[i] = np.array(left_shifted_list_of_row_elements)        
    return state_matrix



def BitVector_multiplication(bv1,bv2):
    AES_modulus = BitVector(bitstring='100011011')
    result = bv1.gf_multiply_modular(bv2, AES_modulus, 8)
    return result

#input : a matrix of byte string and a 2D array of bitvector ,output : a matrix of byte string(after performing bitvector matrix multiplication) 
def Mix_Column_multiplication(Mixer,row_shifted_matrix):
    matrix_size = row_shifted_matrix.shape[0]
    resultant_matrix = np.zeros((matrix_size,matrix_size),dtype=object) # initializing a matrix of strings 

    for i in range(matrix_size):
        for j in range(matrix_size):
            resultant_matrix[i,j] = '00'
            for k in range(matrix_size):
                bv1 = Mixer[i][k]
                bv2 = BitVector(hexstring=row_shifted_matrix[k,j]) #coverting byte string to BitVector
                result_bv = BitVector_multiplication(bv1,bv2)
                result_bytestring = result_bv.get_bitvector_in_hex() #coverting BitVector to byte_string
                resultant_matrix[i,j] = XOR_between_two_byteString(resultant_matrix[i,j],result_bytestring)
    return resultant_matrix


#input : a matrix of byte string and a 2D array of bitvector ,output : a matrix of byte string(after performing bitvector matrix multiplication) 
def Inverse_Mix_Column_multiplication(invMixer,state_matrix):
    matrix_size = state_matrix.shape[0]
    resultant_matrix = np.zeros((matrix_size,matrix_size),dtype=object) # initializing a matrix of strings 

    for i in range(matrix_size):
        for j in range(matrix_size):
            resultant_matrix[i,j] = '00'
            for k in range(matrix_size):
                bv1 = invMixer[i][k]
                bv2 = BitVector(hexstring=state_matrix[k,j]) #coverting byte string to BitVector
                result_bv = BitVector_multiplication(bv1,bv2)
                result_bytestring = result_bv.get_bitvector_in_hex() #coverting BitVector to byte_string
                resultant_matrix[i,j] = XOR_between_two_byteString(resultant_matrix[i,j],result_bytestring)
    return resultant_matrix


#input: hex code of key of first round
#output : list of all keys of all round
def Generate_all_round_keys(key_hex_code):
    keys=[]  #list of keys of all rounds....keys[0] means "key of round 0"
    keys.append(key_hex_code)

    #Finding w[0],w[1],w[2],w[3] from key of round 0
    #------------------------------------------------
    num_of_word_at_each_round = 4 ; #always num_of_word_at_each_round will be 4
    list_of_bytes_in_key_code = key_hex_code.split(' ')
    word_length = int(len(list_of_bytes_in_key_code)/num_of_word_at_each_round) # word_length = the number of byte/byte_string in one word 



    for i in range(num_of_word_at_each_round):
        a_word = tuple(list_of_bytes_in_key_code[word_length*i : word_length*(i+1)])
        w.append(a_word)
    # now "w" has w[0],w[1],w[2],w[3]

    #We have words of key for round 0..Now using the key_words of round 0 we will find the key words of round 1
    #  and then we will generate the key of round 1

    #Similarly,using the key_words of round 0 we will find the key words of round 1
    #  and then we will generate the key of round 1 and so on


    #Finding all other round keys (round 1 to 10)
    #--------------------------------------------------

    previous_round_key_words = w

    for round_no in range(1,total_round+1):
        next_round_words,next_key = generate_next_key(previous_round_key_words,round_no)
        previous_round_key_words = next_round_words
        keys.append(next_key) 


    return keys


#input : plaintext_hex_code and keys of all round
#output : cipher text(hex code)
#this method will encrypt a single block of plain text
def encrypt(plain_text_hex_code,keys):

    #Performing round 0(In this round, input = state_marix_round_0 and round_key_no_0_matrix...and output = state_matrix_round_2 )
    #----------------------------------------------------------------------------------------------------------------------------


    #Finding state matrix of round 0
    state_matrix_round_0 = hex_code_2_state_matrix(plain_text_hex_code)
    #print(state_matrix_round_0)

    #Finding Round key no 0  matrix
    Round_key_no_0_matrix = hex_code_2_round_key_matrix(keys[0])

    #finding state_matrix of round 1(Add round key)
    current_state_matrix = XOR_between_two_matrix(state_matrix_round_0,Round_key_no_0_matrix)
    #print('AES output after round  0 : ',state_matrix_2_hex_code(current_state_matrix))


    #print(Round_key_no_0_matrix)

    #In each round i, input = state_marix_round_i and round_key_no_i_matrix...and output = state_matrix_round_(i+1) )


    #Performing round 1 to 10 
    #-------------------------

    for round_no in range(1,11): #iterating from i=1 to i=10
        #Substitute bytes
        substituted_byte_matrix = Substitute_bytes(current_state_matrix)
        #Shift row
        row_shifted_matrix = Shift_rows(substituted_byte_matrix)
        #Mix columns
        if(round_no != total_round): #as there is no "Mix column" in round 10
            mixed_column_matrix = Mix_Column_multiplication(Mixer,row_shifted_matrix)
        else:
            mixed_column_matrix = row_shifted_matrix

        #Add_round_key
        Round_key_matrix = hex_code_2_round_key_matrix(keys[round_no])
        current_state_matrix = XOR_between_two_matrix(mixed_column_matrix,Round_key_matrix)
        
    # print('AES output after round ',round_no,': ',state_matrix_2_hex_code(current_state_matrix))



    #Finding cipher key after the end of encryption process 
    #-------------------------------------
    cipher_text = state_matrix_2_hex_code(current_state_matrix)

    return cipher_text




#input : cipher_text(hex code) and keys of all round
#output : plain text
def decrypt(cipher_text_hex_code,keys):

    keys = keys[::-1] #reversing the list "keys" because the key of round 10 for encryption is the key of round 0 in decryption

    #Performing round 0(In this round, input = state_marix_round_0 and round_key_no_0_matrix...and output = state_matrix_round_2 )
    #-----------------------------------------------------------------------------------------------------------------------------

    #Finding state matrix of round 0
    state_matrix_round_0 = hex_code_2_state_matrix(cipher_text_hex_code)
    #print(state_matrix_round_0)

    #Finding Round key no 0  matrix
    Round_key_no_0_matrix = hex_code_2_round_key_matrix(keys[0])

    #finding state_matrix of round 1(Add round key)
    current_state_matrix = XOR_between_two_matrix(state_matrix_round_0,Round_key_no_0_matrix)
    #print('AES output after round  0 : ',state_matrix_2_hex_code(current_state_matrix))


    #print(Round_key_no_0_matrix)

    #In each round i, input = state_marix_round_i and round_key_no_i_matrix...and output = state_matrix_round_(i+1) )


    #Performing round 1 to 10 
    #-------------------------

    for round_no in range(1,11): #iterating from i=1 to i=10
        
        #inverse Shift row
        row_shifted_matrix = Inverse_Shift_rows(current_state_matrix)
        #Substitute bytes
        inverse_substituted_bytes = Inverse_substitute_bytes(row_shifted_matrix)

        #Add_round_key
        Round_key_matrix = hex_code_2_round_key_matrix(keys[round_no])
        state_matrix_before_mixing = XOR_between_two_matrix(inverse_substituted_bytes,Round_key_matrix)
       
        #Mix columns
        if(round_no != total_round): #as there is no "Mix column" in round 10
            current_state_matrix = Inverse_Mix_Column_multiplication(InvMixer,state_matrix_before_mixing)
        else:
            current_state_matrix = state_matrix_before_mixing

        
        
    # print('AES output after round ',round_no,': ',state_matrix_2_hex_code(current_state_matrix))



    #Finding cipher key after the end of encryption process 
    #-------------------------------------
    decrypted_plain_text_hex_code = state_matrix_2_hex_code(current_state_matrix)
    decrypted_plain_text = hex_code_2_text(decrypted_plain_text_hex_code)

    return decrypted_plain_text,decrypted_plain_text_hex_code


#this function will convert the "secret_key" integer into space separated hex code(this function is only for socket programming)
def secret_key_2_hex_code(secret_key):
   
    secret_key_hex_str = hex(secret_key)[2:]
    length = len(secret_key_hex_str) 
    num_of_iteration = math.ceil(length/2)
    key_hex_code = ''
    for i in range(num_of_iteration):
        if(2*(i+1) ==  length+1): #handling the situation when the secret key hex code length is 31(because expevted length is 32)
            key_hex_code = key_hex_code + ' 0'+secret_key_hex_str[2*i:]
        else:
            key_hex_code = key_hex_code + ' ' +secret_key_hex_str[2*i:2*(i+1)]
     
    return key_hex_code.lstrip()



#handling plain text size
#------------------------

def get_plain_text_blocks(plain_text): 

    num_of_blocks = math.ceil(len(plain_text)/block_size)
    num_of_dummy_characters =  block_size*num_of_blocks - len(plain_text)  

    plain_text_blocks = [] #list of string..each string is a block

    for i in range(num_of_blocks):
        if(i != num_of_blocks-1):
            plain_text_blocks.append(plain_text[block_size*i:block_size*(i+1)]) #iterating block by block of plain text
        else:
            if(num_of_dummy_characters == 0 ): #if the last block is filled
                plain_text_blocks.append(plain_text[block_size*i:block_size*(i+1)])
            else:
                #if the last block is not filled then fill the block with dummy characters
                last_block = plain_text[block_size*i:len(plain_text)]
                #adding dummy characters
                for i in range(1,num_of_dummy_characters+1):
                    last_block = last_block + chr(i)

                plain_text_blocks.append(last_block)

    return plain_text_blocks







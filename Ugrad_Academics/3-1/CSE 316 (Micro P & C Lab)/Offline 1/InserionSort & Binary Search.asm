.MODEL SMALL
.STACK 100H

 
.DATA   

N DW ? ;Total inputed integer


ARR DW ? 

TOTAL_INTEGERS DW "TOTAL INTEGERS: $"
PRINT_INTEGERS DW "PRINT INTEGERS ONE BY ONE: $"   
END_MSG DW "END$"  
SORTED_ARRAY DW "SORTED ARRAY: $"  
FOUND_MSG DW "FOUND AT INDEX: $"
NOT_FOUND_MSG DW "NOT FOUND$" 
SEARCH_MSG DW "SEARCH A NUMBER: $"

NEGATIVE_FLAG DB 0 

TEMP DW ? 
TEMP_2 DW ?
TEMP_3 DW ?  
DIGIT_COUNT DW ? 
BACKUP_CX DW ?
 



I DW 1
J DW 0
ITEM DW ?
OUTER_LOOP_ITERATION DW ?  


;for binary search    

SEARCHED_ELEMENT DW ? 
LOW DW 0
HIGH DW ?
MID DW ?






.CODE

MAIN PROC
    
    MOV AX,@DATA
    MOV DS,AX 
    
    MOV AH,9
    LEA DX,TOTAL_INTEGERS
    INT 21H
    
    
    
    
    CALL INTEGER_INPUT   
    
    MOV AX,TEMP
    MOV N,AX 
    
    
    ;end the program if N<=0 
    MOV AX,N
    CMP AX,0
    JLE END_M 
    
      
    
    
    ;new line
    MOV AH, 2
    MOV DL, 10
    INT 21H
    MOV DL, 13
    INT 21H
    
    ;new line
    MOV AH, 2
    MOV DL, 10
    INT 21H
    MOV DL, 13
    INT 21H   
    
    
    MOV AH,9
    LEA DX,PRINT_INTEGERS
    INT 21H  
    
     ;new line
    MOV AH, 2
    MOV DL, 10
    INT 21H
    MOV DL, 13
    INT 21H 
    
    
    ;Loading the address of array
    LEA SI,ARR
    
            
            
            
    MOV CX,N
   
    
    
    TAKING_N_INTEGER_INPUT_LOOP:
     
    CALL INTEGER_INPUT
    MOV AX,TEMP 
    MOV [SI],AX
    INC SI 
    INC SI 
    
    ;new line
    MOV AH, 2
    MOV DL, 10
    INT 21H
    MOV DL, 13
    INT 21H 
    
    
    LOOP TAKING_N_INTEGER_INPUT_LOOP  
    
    ;new line
    MOV AH, 2
    MOV DL, 10
    INT 21H
    MOV DL, 13
    INT 21H 
    
    
    
    
    
    ;;sorting begin 
    
    
    
   
    
    
    MOV AX,N 
     
    ;if the array has only one element,then no need to sort 
    CMP AX,1
    JE DISPLAYING_SORTED_ARRAY 
    
    MOV OUTER_LOOP_ITERATION,AX
    DEC OUTER_LOOP_ITERATION
    
    MOV CX, OUTER_LOOP_ITERATION
    
    OUTER_LOOP: 
    
    LEA SI,ARR   
    
    ;ITEM = ARR[i]
    
    MOV AX,I 
    MOV BX,2
    MUL BX
    
    ADD SI,AX
    
    MOV BX,[SI] 
    MOV ITEM,BX  
    
    ;J = I-1
    MOV AX,I
    DEC AX
    MOV J,AX
    
    
    INNER_LOOP: 
    
    MOV AX,J  
    
    ;;checking J>=0
    CMP AX,0
    JNGE OUTER_LOOP_AGAIN 
    
    
    
    
    MOV BX,2
    MUL BX   
   
    
    LEA SI,ARR ;;back to 0th position of array
    ADD SI,AX
    MOV AX,[SI]
    MOV BX ,ITEM
    
    ;checking A[J] > ITEM
    CMP AX,BX
    JNG OUTER_LOOP_AGAIN
    
    
    ;inner loop condition satisfied   
    
    LEA SI,ARR
    MOV AX,J 
    
     
    MOV BX,2
    MUL BX   
    
    ;A[J+1] = A[J]
    ADD SI,AX 
    
    MOV BX,[SI]
    MOV [SI+2],BX  
    
    ;J=J-1
    SUB J,1
    
    JMP INNER_LOOP
    
    
    
     
    
    OUTER_LOOP_AGAIN:  
    
    
    ;A[J+1] = ITEM
    LEA SI,ARR
    MOV AX,J 
    
     
    MOV BX,2
    MUL BX   
    
    ADD SI,AX
    
    MOV BX,ITEM
    MOV [SI+2],BX
    
    
    
    INC I
    
    LOOP OUTER_LOOP
    
    
    
    
    ;End of Sorting
    
    
     
    
    ;DISPLAYING SORTED ARRAY  
    
    DISPLAYING_SORTED_ARRAY:
    
    MOV AH,9
    LEA DX,SORTED_ARRAY
    INT 21H
    
    
    
             
    MOV CX,N
   
    LEA SI,ARR
    
    DISPLAY:
    
   
    
    MOV AH,2
    MOV BX,[SI]
    
    CMP BX,0
    JNL IF_NON_NEGATIVE
    
    
    
    IF_NEGATIVE: 
     
    NEG BX
      
    MOV DL,'-'
    INT 21H
     
    
    
    IF_NON_NEGATIVE:
     
    
   
    INC SI 
    INC SI 
    
    
    MOV TEMP_3,BX
    CALL DISPLAY_INTEGER 
    
      
    ;space
    MOV AH, 2
    MOV DL, 32
    INT 21H 
     
   
    
    
    LOOP DISPLAY  
    
    ;End of displaying SORTED ARRAY  
    
    
    
    
    ;STARTING_BINARY_SEARCH
    
    INPUT_FOR_SEARCHING: 
    
    ;Reseting LOW,HIGH and MID to "0" for each search
    
    MOV LOW,0
    MOV HIGH,0
    MOV MID,0
    
    
    
    ;new line
    MOV AH, 2
    MOV DL, 10
    INT 21H
    MOV DL, 13
    INT 21H   
    
     ;new line
    MOV AH, 2
    MOV DL, 10
    INT 21H
    MOV DL, 13
    INT 21H  
    
    MOV AH,9
    LEA DX,SEARCH_MSG
    INT 21H
    
     
    ;taking integer input for searching 
    CALL INTEGER_INPUT
    MOV AX,TEMP
    MOV SEARCHED_ELEMENT,AX 
   
    
    
    
    ;LOW = 0
    ;HIGH = N-1 
    MOV AX,N
    DEC AX
    
    
    MOV HIGH,AX
    
   
    
    
    
    
    
    SEARCHING_LOOP: 
    
    ;WHILE (HIGH >= LOW) 
    MOV AX,HIGH
    MOV BX,LOW
    
    
    CMP AX,BX
    JNGE NOT_FOUND_RESULT 
      
    
    LEA SI,ARR
    
    
    
    
    ;MID = (LOW + HIGH)/2 
    MOV DX,0
    MOV AX,LOW
    ADD AX,HIGH
    MOV BX,2
    DIV BX
    MOV MID,AX
    
    ;will need to access [SI + MID * 2] no address to find A[MID]
    
    MOV AX,MID 
    MOV BX,2
    MUL BX
    ADD SI,AX
    
    ;IF ARR[MID] == SEARCHED_ELEMENT
    
    MOV BX,SEARCHED_ELEMENT
    
    CMP BX,[SI]   ;HERE [SI] = ARR[MID]
    
    JE FOUND_RESULT   
    
    
    ;IF   SEARCHED_ELEMENT >  ARR[MID]
    
    CMP BX,[SI]  ; 
    
    JG GO_TO_RIGHT_HALF   
    
     
    ;IF   SEARCHED_ELEMENT <  ARR[MID]
    
    JMP  GO_TO_LEFT_HALF
    
    
    GO_TO_RIGHT_HALF: 
    
    ;LOW = MID + 1
    
    MOV CX,MID
    ADD CX,1
    MOV LOW,CX
    
    JMP SEARCHING_LOOP
    
    
    
    GO_TO_LEFT_HALF: 
    
    ;HIGH = MID - 1  
    
    MOV CX,HIGH
    SUB CX,1
    MOV HIGH,CX
    
    
    JMP SEARCHING_LOOP
      
    
    
    FOUND_RESULT: 
    
    ;new line
    MOV AH, 2
    MOV DL, 10
    INT 21H
    MOV DL, 13
    INT 21H  
    
    MOV AH,9
    LEA DX,FOUND_MSG
    INT 21H
    
    MOV AH,2
    MOV DX,MID
    ADD DX,1
    
    MOV TEMP_3,DX
    CALL DISPLAY_INTEGER ;will display the index if found
    
      
    JMP INPUT_FOR_SEARCHING:
    
    
    
     
    NOT_FOUND_RESULT:   
    
    ;new line
    MOV AH, 2
    MOV DL, 10
    INT 21H
    MOV DL, 13
    INT 21H  
    
    MOV AH,9
    LEA DX,NOT_FOUND_MSG
    INT 21H
    JMP INPUT_FOR_SEARCHING:
    
    
    ;END OF BINARY SEARCH
     
    
    
    
    
    
    
    
    
    
    
    
    
    END_M:
    
    ;new line
    MOV AH, 2
    MOV DL, 10
    INT 21H
    MOV DL, 13
    INT 21H   
    
     ;new line
    MOV AH, 2
    MOV DL, 10
    INT 21H
    MOV DL, 13
    INT 21H   
     
    ;showing "END"
    MOV AH,9
    LEA DX,END_MSG
    INT 21H 
    
    MOV AH,4CH
    INT 21H
    
    MAIN ENDP 
    
    
    
    
    



INTEGER_INPUT PROC
    
    MOV AX,@DATA
    MOV DS,AX  
    
    ; fast BX = 0
    XOR BX, BX
    
    INPUT_LOOP:
    ; char input 
    MOV AH, 1
    INT 21H
    
    
    ; if \n stop taking input
    
    CMP AL, 10
    JE END_INPUT_LOOP
    CMP AL, 13
    JE END_INPUT_LOOP
    
    ;checking if the number is negative
    
    CMP AL,'-'
    JE NEG_INPUT
    JMP PROCEED 
    
    NEG_INPUT:
    
    ADD NEGATIVE_FLAG,1 
    JMP INPUT_LOOP
    
    PROCEED:
    ; fast char to digit
    ; also clears AH  
    
    
    AND AX, 000FH
    
    ; save AX 
    MOV TEMP_2, AX
    
    ; BX = BX * 10 + AX
    MOV AX, 10
    MUL BX
    ADD AX, TEMP_2
    MOV BX, AX
    JMP INPUT_LOOP
    
    END_INPUT_LOOP:
    
    
    ;if Negative integer input, then negating the number
    MOV AL,NEGATIVE_FLAG
    CMP AL,0
    JE POSITIVE_INT
    JMP NEGATIVE_INT  
    
    POSITIVE_INT:
    
    MOV TEMP, BX
    JMP END 
    
    NEGATIVE_INT: 
    
    NEG BX
    MOV TEMP, BX 
    
    SUB NEGATIVE_FLAG,1
    
    END:
    
    
    
   
    
    RET
    INTEGER_INPUT ENDP

    


DISPLAY_INTEGER PROC
    
    MOV AX,@DATA
    MOV DS,AX 
    
    MOV AX,TEMP_3   
    MOV BX,TEMP_3
    
    ;if the integer is "0" then no need to break
    CMP BX,0
    JE PRINT_ZERO 
    
    ;if the integer is non zero 
    JMP INTEGER_BREAKING_LOOP  
    
    
    PRINT_ZERO:
    MOV AH,2
    MOV DL,48
    INT 21H
    RET
    
    
    
    INTEGER_BREAKING_LOOP:
    
    CMP AX,0
    JE END_INTEGER_BREAKING 
    
    MOV DX,0
    MOV BX,10
    DIV BX
    PUSH DX 
    INC DIGIT_COUNT
    
    JMP INTEGER_BREAKING_LOOP 
         
    
    END_INTEGER_BREAKING: 
    
    MOV BACKUP_CX , CX
    
    MOV CX,DIGIT_COUNT
    
    
    
    PRINT_INTEGER_LOOP:
    
    POP DX
    ADD DX,48 ;for printing the digit
    MOV AH,2
    INT 21H
    
    LOOP PRINT_INTEGER_LOOP 
    
     
     
    MOV CX,BACKUP_CX 
    
    ;Reseting DIGIT_COUNT = 0  
    MOV AX,DIGIT_COUNT 
    
    XOR AX,AX ;making AX = 0 
    MOV DIGIT_COUNT,AX 
    
    
    
    
    
    
    RET
    DISPLAY_INTEGER ENDP



     
END MAIN
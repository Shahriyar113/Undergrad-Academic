.MODEL small
.STACK 100h
.DATA
	print_var dw ?
	digit_count dw ?
	backup_cx dw ?
	ret_temp dw ?
	a_1_1 dw ?
	b_1_1 dw ?
	c_1_1 dw 3 dup(?)
	t0 dw ?
	t1 dw ?
	t2 dw ?
	t3 dw ?
	t4 dw ?
	t5 dw ?
	t6 dw ?
.CODE
print PROC
	push ax
	push bx
	push cx
	push dx
	mov ax, print_var
	mov bx, print_var
	cmp ax, 0
	jl negative
	jmp non_negative
negative:
	neg ax
	push ax
	mov ah, 2
	mov dl, '-'
	int 21h
	pop ax
	jmp integer_breaking_loop
non_negative:
	cmp bx, 0
	je print_zero
	jmp integer_breaking_loop
print_zero:
	mov ah, 2
	mov dl, 48
	int 21h
	mov ah, 2
	mov dl, 10
	int 21h
	mov dl, 13
	int 21h
	pop dx
	pop cx
	pop bx
	pop ax
	ret
integer_breaking_loop:
	cmp ax, 0
	je end_integer_breaking
	mov dx, 0
	mov bx, 10
	div bx
	push dx
	inc digit_count
	jmp integer_breaking_loop
end_integer_breaking:
	mov backup_cx, cx
	mov cx, digit_count
	print_integer_loop:
	pop dx
	add dx, 48
	mov ah, 2
	int 21h
	loop print_integer_loop
	mov cx, backup_cx
	mov ax, digit_count
	xor ax, ax
	mov digit_count, ax
	mov ah, 2
	mov dl, 10
	int 21h
	mov dl, 13
	int 21h
	pop dx
	pop cx
	pop bx
	pop ax
	ret
print endp
main PROC
	mov ax, @data
	mov ds, ax
	mov ax, 2
	add ax, 3
	mov t0, ax
	mov ax, 1
	mov bx, t0
	mul bx
	mov t1, ax
	mov ax, t1
	mov bx, 3
	xor dx, dx
	div bx
	mov t2, dx
	mov ax, t2
	mov a_1_1, ax
	mov ax, 1
	cmp ax, 5
	jl l0
	mov t3, 0
	jmp l1
l0:
	mov t3, 1
l1:
	mov ax, t3
	mov b_1_1, ax
	mov di, 0
	add di, di
	mov ax, 2
	mov c_1_1[di], ax
	cmp a_1_1, 0
	je l2
	cmp b_1_1, 0
	je l2
	mov t4, 1
	jmp l3
l2:
	mov t4, 0
l3:
	mov ax, t4
	cmp ax, 0
	je l4
	mov di, 0
	add di, di
	mov ax, c_1_1[di]
	mov t5, ax
	inc c_1_1[di]
	jmp l5
l4:
	mov di, 0
	add di, di
	mov ax, c_1_1[di]
	mov t6, ax
	mov di, 1
	add di, di
	mov ax, t6
	mov c_1_1[di], ax
l5:
	mov ax, a_1_1
	mov print_var, ax
	call print
	mov ax, b_1_1
	mov print_var, ax
	call print
	mov ah,4ch
	int 21h
main ENDP
END main

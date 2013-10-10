GLOBAL read

read:
armoStack:  
	push ebp
	mov ebp, esp
	
leer:
	in al, 64h
	and al, 00000001b
	cmp al, 0
	je leer
	
tomaTexto:
	in al, 060h
	and eax, 0x000000FF
	
desarmadoStack:
	mov esp, ebp
	pop ebp

	ret



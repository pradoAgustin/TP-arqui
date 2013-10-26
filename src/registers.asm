GLOBAL registers

registers:
armoStack:  
	push ebp
	mov ebp, esp
	

mov eax,ebx
desarmadoStack:
	mov esp, ebp
	pop ebp

	ret


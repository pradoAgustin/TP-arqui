GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug
GLOBAL _int_09_hand
GLOBAL outportb32
GLOBAL inportb32
GLOBAL outportb
GLOBAL inportb
GLOBAL read_flags
GLOBAL read_register_eax
GLOBAL read_register_ebx
GLOBAL read_register_ecx
GLOBAL read_register_edx
GLOBAL read_register_esi
GLOBAL read_register_edi
GLOBAL read_register_ebp
GLOBAL read_register_esp
GLOBAL read_segment_cs
GLOBAL read_segment_ss
GLOBAL read_segment_fs
GLOBAL read_segment_gs
GLOBAL read_segment_ds
GLOBAL read_segment_es
GLOBAL _opencd
EXTERN  int_08
EXTERN  int_09
EXTERN printStatus
GLOBAL  _printError
EXTERN printNum
GLOBAL _closecd
GLOBAL _infocd
GLOBAL cambiar_eax
SECTION .text


_Cli:
	cli			; limpia flag de interrupciones
	ret

_Sti:

	sti			; habilita interrupciones por flag
	ret

_mascaraPIC1:			; Escribe mascara del PIC 1
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	21h,al
        pop     ebp
        retn

_mascaraPIC2:			; Escribe mascara del PIC 2
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	0A1h,al
        pop     ebp
        retn

_read_msw:
        smsw    ax		; Obtiene la Machine Status Word
        retn


_lidt:				; Carga el IDTR
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR 
	rol	ebx,16		    	
	lidt    [ds: ebx]          ; carga IDTR
        pop     ebx
        pop     ebp
        retn


_int_08_hand:				; Handler de INT 8 ( Timer tick)
        push    ds
        push    es                      ; Se salvan los registros
        pusha                           ; Carga de DS y ES con el valor del selector
        mov     ax, 10h			; a utilizar.
        mov     ds, ax
        mov     es, ax                  
        call    int_08                 
        mov	al,20h			; Envio de EOI generico al PIC
	out	20h,al
	popa                            
        pop     es
        pop     ds
        iret
        
_int_09_hand:			    ; Handler de INT9 (Teclado)
    pushad                  ; Buckupea todos los registros.
    pushf                    ; Backupea todos los flags.
    push cs
    push ss
    push ds
    push es
    push fs
    push gs                  
    mov eax,0
    in al,060h              ; Le pido el scancode al teclado.
    ;call save_registers
    push eax

    call int_09
    pop eax
    add esp,24
    mov	al,20h			    ; Le mando el EOI generico al PIC.
    out 20h,al
    popf                    ; Restauro todos los flags.
    popad                   ; Restauro todos los registros.
    iretd
    


outportb:
    push ebp
    mov ebp, esp
    
    mov dx,word[ebp + 8]  ;en EAX pongo el primer parametro port
    mov al,byte[ebp + 12] ;en EBX pongo el segundo parametro source
    out dx, al

    mov esp, ebp
    pop ebp
    ret

read_segment_cs:
    push ebp
    mov ebp, esp

    mov eax, [esp+36];[esp+32]

    mov esp, ebp
    pop ebp
    ret

read_segment_ss:
    push ebp
    mov ebp, esp

    mov eax, [esp+32];[esp+28]

    mov esp, ebp
    pop ebp
    ret

read_segment_ds:
    push ebp
    mov ebp, esp

    mov eax, [esp +28];[esp+24]

    mov esp, ebp
    pop ebp
    ret

read_segment_es:
    push ebp
    mov ebp, esp

    mov eax, [esp+24];[esp+20]

    mov esp, ebp
    pop ebp
    ret

read_segment_fs:
    push ebp
    mov ebp, esp

    mov eax, [esp+20];[esp+16]

    mov esp, ebp
    pop ebp
    ret

read_segment_gs:
    push ebp
    mov ebp, esp

    mov eax, [esp+16];[esp+12]

    mov esp, ebp
    pop ebp
    ret



read_flags:
    push ebp
    mov ebp, esp

    mov eax, [esp+40];[esp+36]

    mov esp, ebp
    pop ebp
    ret

read_register_edi:
    push ebp
    mov ebp, esp

    mov eax, [esp+44];[esp+40]

    mov esp, ebp
    pop ebp
    ret

read_register_esi:
    push ebp
    mov ebp, esp

    mov eax, [esp+48];[esp+44]

    mov esp, ebp
    pop ebp
    ret

read_register_ebp:
    push ebp
    mov ebp, esp

    mov eax, [esp +52];[esp+48]

    mov esp, ebp
    pop ebp
    ret

read_register_esp:
    push ebp
    mov ebp, esp

    mov eax, [esp+56];[esp+52]

    mov esp, ebp
    pop ebp
    ret

read_register_ebx:
    push ebp
    mov ebp, esp

    mov eax, [esp +60];[esp+56]

    mov esp, ebp
    pop ebp
    ret

read_register_edx:
    push ebp
    mov ebp, esp

    mov eax, [esp+64];[esp+60]

    mov esp, ebp
    pop ebp
    ret

read_register_ecx:
    push ebp
    mov ebp, esp

    mov eax, [esp+68];[esp+64]

    mov esp, ebp
    pop ebp
    ret

read_register_eax:
    push ebp
    mov ebp, esp

    mov eax, [esp+72]

    mov esp, ebp
    pop ebp
    ret

cambiar_eax:
mov eax, ebx


inportb:
    push ebp
    mov ebp, esp
    
    mov eax, 0
    mov dx, word[ebp + 8]  ;en EAX pongo el primer parametro port
    in al, dx
    
    mov esp,ebp
    pop ebp
    ret
    
outportb32:
    push ebp
    mov ebp, esp
    
    mov dx,word[ebp + 8]    ;en EAX pongo el primer parametro port
    mov eax,dword[ebp + 12] ;en EBX pongo el segundo parametro source
    out dx, eax

    mov esp, ebp
    pop ebp
    ret

inportb32:
    push ebp
    mov ebp, esp
    
    mov eax, 0
    mov dx, word[ebp + 8]  ;en EAX pongo el primer parametro port
    in eax, dx
    
    mov esp,ebp
    pop ebp
    ret
_outl:
    push ebp 
    mov ebp, esp
    mov dx, word[ebp+8] 
    mov eax, dword[ebp+12] 
    out dx, eax 
    mov esp, ebp 
    pop ebp 
    ret 
    
_inl: 
	push ebp 
	mov ebp, esp 
	xor eax, eax 
	mov dx, word[ebp+8] 
	in eax, dx 
	mov esp, ebp 
	pop ebp 
	ret

; Debug para el BOCHS, detiene la ejecució; Para continuar colocar en el BOCHSDBG: set $eax=0
;


_debug:
        push    bp
        mov     bp, sp
        push	ax
vuelve:	mov     ax, 1
        cmp	ax, 0
	jne	vuelve
	pop	ax
	pop     bp
        retn

;save_registers:
 ;   mov si,0
;loop:
;    mov eax, [esi+si]
;    mov [buffer+si], eax
;    mov si, esi+4
;    cmp si, 68
;    jne loop
;    ret

;section .bss
;    buffer resb 64
   ;///////////////////////////////////////////////////////////////////////////////////////////////////////

_opencd:

call _pollBSY

mov ax, 00h 
mov dx, 0x1F6 
out dx, ax ; al puerto 1f6 mando un cero

mov dx, 0x1F1
mov ax, 0 
out dx, ax ; al puerto 1f1 mando un cero

;call _pollDRDY

mov dx, 0x1F7 
mov ax, 0xA0 
out dx, ax ; al puerto 1f7 mando el A0

; puede pasar q tarde un cacho 

mov ebx, 65000
loop9: 
dec ebx
cmp ebx, 0
jne loop9

call _pollBSY 
call _pollDRQ

mov dx, 0x1F0 
mov al, 0x1E 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

call _pollBSY 
call _pollDRDY

mov dx, 0x1F7 
mov ax, 0xA0 
out dx, ax

call _pollBSY 
call _pollDRQ

mov dx, 0x1f0
mov al, 1Bh 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 2 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

;mov eax, 0
;mov dx, 0x1f7
;in eax, dx
;push eax
;call printStatus
;pop eax

call _pollBSY
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;pollDRDY no hace falta
;;pollbsy es fijarse si busy no esta en 1
;;polldrq es fijarse que drq este en 1
;;0x1E  y todo cero es para habilitar la lectora
;;para cerrar la lectora no hace falta 0x1E
;; solo hace falta 0x1B
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_pollBSY:
MOV DX, 1F7h 
LOOP1:
IN AL, DX 
AND AL, 0x80
JNE LOOP1
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_pollDRDY:
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_pollDRQ:
MOV DX, 1F7h 
LOOP4:
IN AL, DX
AND AL,0x08 
JE LOOP4
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


_printError:
mov dx, 0x1F1
mov ax, 0
in al, dx
push eax
call printNum
pop eax
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_closecd:

call _pollBSY

mov ax, 00h 
mov dx, 0x1F6 
out dx, ax ; al puerto 1f6 mando un cero

mov dx, 0x1F1
mov ax, 0 
out dx, ax ; al puerto 1f1 mando un cero

;call _pollDRDY

mov dx, 0x1F7 
mov ax, 0xA0 
out dx, ax ; al puerto 1f7 mando el A0

; puede pasar q tarde un cacho 

mov ebx, 65000
loop97: 
dec ebx
cmp ebx, 0
jne loop97

call _pollBSY 
call _pollDRQ

mov dx, 0x1F0 

mov al, 0x1E 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

call _pollBSY 
call _pollDRDY

mov dx, 0x1F7 

mov ax, 0xA0 
out dx, ax

call _pollBSY 
call _pollDRQ

mov dx, 0x1f0
mov al, 1Bh 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 3 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov eax, 0
mov dx, 0x1f7
in eax, dx
push eax
call printStatus
pop eax


call _pollBSY
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_infocd:

call _pollBSY

mov ax, 00h 
mov dx, 0x1F6 
out dx, ax ; al puerto 1f6 mando un cero

mov dx, 0x1F1
mov ax, 0 
out dx, ax ; al puerto 1f1 mando un cero

;call _pollDRDY
mov dx, 0x1F7 
mov ax, 0xA0 
out dx, ax ; al puerto 1f7 mando el A0

; puede pasar q tarde un cacho 
mov ebx, 65000
loop982: 
dec ebx
cmp ebx, 0
jne loop982

call _pollBSY 
call _pollDRQ

mov dx, 0x1F0 

mov al, 0xA8
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

call _pollBSY 
call _pollDRDY

mov dx, 0x1F7 
mov ax, 0xA0 
out dx, ax

call _pollBSY 
call _pollDRQ

mov dx, 0x1f0
mov al, 0x25
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov al, 0 
out dx, al

mov eax, 0
mov dx, 0x1f7

in eax, dx
push eax
call printStatus
pop eax

call _pollBSY
ret


;A medium is any media inserted in the ATAPI Drive, like a CD or a DVD. By using the 'SCSI Read Capacity' command, ;you can read the last LBA of the medium, then you calculate the medium's capacity using this relationship:

;Capacity = (Last LBA + 1) * Block Size;

;Last LBA and Block Size are returned after processing the command. Almost all CDs and DVDs use blocks with size of ;2KB each.

;Processing this command goes in the following algorithm:

   ; Selecting the Drive [Master/Slave].
   ; Waiting 400ns for select to complete.
   ; Setting FEATURES Register to 0 [PIO Mode].
   ; Setting LBA1 and LBA2 Registers to 0x0008 [Number of Bytes will be returned].
   ; Sending Packet Command, then Polling.
   ; Sending the ATAPI Packet, then polling.
   ; If there isn't an error, reading 4 Words [8 bytes] from the DATA Register. 


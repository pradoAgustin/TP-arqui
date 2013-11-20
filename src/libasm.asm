GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand, _int_09_hand
;GLOBAL _int_80_hand
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug
GLOBAL outportb
GLOBAL read_register_eax, read_register_ebx, read_register_ecx, read_register_edx, read_register_esi
GLOBAL read_register_edi, read_register_ebp, read_register_esp, read_segment_cs, read_segment_ss
GLOBAL read_segment_fs, read_segment_gs, read_segment_ds, read_segment_es, read_flags
GLOBAL _delay
GLOBAL _iniciar_contador
GLOBAL _contar_caracteres
GLOBAL _initialize_cursor
GLOBAL _cuenta_super_complicada
EXTERN  int_08, int_09
;EXTERN int_80
EXTERN printStatus
GLOBAL  _printError
EXTERN printNum
GLOBAL  _opencd, _closecd, _infoCD
EXTERN printCapacity
EXTERN printReady
EXTERN printRegister
EXTERN printbusy
GLOBAL _inc_b
GLOBAL _reiniciar_registros

SECTION .bss
    registers resb 70
    buffer resb 8
    array resb 8


SECTION .text


_Cli:
    cli         ; limpia flag de interrupciones
    ret

_Sti:

    sti         ; habilita interrupciones por flag
    ret

_mascaraPIC1:           ; Escribe mascara del PIC 1
    push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out 21h,al
        pop     ebp
        retn

_mascaraPIC2:           ; Escribe mascara del PIC 2
    push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out 0A1h,al
        pop     ebp
        retn

_read_msw:
        smsw    ax      ; Obtiene la Machine Status Word
        retn


_lidt:              ; Carga el IDTR
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR 
    rol ebx,16              
    lidt    [ds: ebx]          ; carga IDTR
        pop     ebx
        pop     ebp
        retn


_int_08_hand:               ; Handler de INT 8 ( Timer tick)
        push    ds
        push    es                      ; Se salvan los registros
        pusha                           ; Carga de DS y ES con el valor del selector
        mov     ax, 10h         ; a utilizar.
        mov     ds, ax
        mov     es, ax                  
        call    int_08                 
        mov al,20h          ; Envio de EOI generico al PIC
    out 20h,al
    popa                            
        pop     es
        pop     ds
        iret
        
_int_09_hand:               ; Handler de INT9 (Teclado) 
    pushad                  ; Buckupea todos los registros.
    push ss
    push ds
    push es
    push fs
    push gs                  
    call _store_registers
    xor eax,eax
    in al,060h              ; Le pido el scancode al teclado.
    push eax

    call int_09
    pop eax
    add esp,20
    mov al,20h              ; Le mando el EOI generico al PIC.
    out 20h,al
    popad                   ; Restauro todos los registros.
    iretd

;_int_80_hand:
 ;   push ebp
 ;   mov ebp, esp
  ;  push edi
  ;  push esi
  ;  push edx
  ;  push ecx
  ;  push ebx
  ;  push eax
  ;  call int_80
  ;  pop eax
  ;  pop ebx
  ;  pop ecx
  ;  pop edx
  ;  pop esi
  ;  pop edi
  ;  mov esp, ebp
  ;  pop ebp
  ;  iret


outportb:
    push ebp
    mov ebp, esp
    
    mov dx,word[ebp + 8]  ;en EAX pongo el primer parametro port
    mov al,byte[ebp + 12] ;en EBX pongo el segundo parametro source
    out dx, al

    mov esp, ebp
    pop ebp
    ret

_update_cursor:
    add ebx,1
    cmp ebx,1000
    je reset
    ret
reset:
    mov ebx,0
    ret

_initialize_cursor:
    mov ebx,0
    ret

_store_registers:
    mov edx,0
    mov ebx,esp
loop:
    add ebx,4
    mov ecx,[ebx]
    mov [registers+edx],ecx
    add edx,4
    cmp edx,60
    jne loop
    ret

read_segment_cs:
    
    xor eax,eax
    mov ax, [registers+56]
    ret

read_segment_ss:
    xor eax,eax
    mov ax, [registers+16]
    ret

read_segment_ds:

    xor eax,eax
    mov ax, [registers+12]
    ret

read_segment_es:

    xor eax,eax
    mov ax, [registers+8]
    ret

read_segment_fs:

    xor eax,eax
    mov ax, [registers+4]
    ret

read_segment_gs:
    
    xor eax,eax
    mov ax, [registers]
    ret

read_register_edi:
    
    mov eax, [registers+32]
    ret

;read_flags:
    
    ;mov eax, [registers+64]
    ;ret
 
read_register_esi:
   
    mov eax, [registers+28]
    ret

read_register_ebp:

    mov eax, [registers+20]
    ret

read_register_esp:
 
    mov eax, [registers+24]
    ret

read_register_ebx:

    mov eax, [registers+36]
    ret

read_register_edx:
 
    mov eax, [registers+40]
    ret

read_register_ecx:
   
    mov eax, [registers+44]
    ret

read_register_eax:
   
    mov eax, [registers+48]
    ret
_iniciar_contador:
    mov ebx,0
    ret
_inc_b:
    inc ebx
    ret
_contar_caracteres:
    add ecx,1
    ret

_reiniciar_registros:
    xor eax,eax
    mov ebx,0
    mov ecx,1
    mov edx,2
    ret
_cuenta_super_complicada:
    inc eax
    inc ebx
    inc ecx
    inc edx
    ret

_delay:
    mov eax, 0
loopbis:
    add eax,1
    cmp eax, 500000
    jne loopbis
    mov eax,0
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
        push    ax
vuelve: mov     ax, 1
        cmp ax, 0
    jne vuelve
    pop ax
    pop     bp
        retn


_opencd:

    call isBSY

    mov dx, 0x1f6
    mov al, 10h
    out dx, al 

    mov dx, 0x1f1
    mov al, 0
    out dx, al 

    MOV DX, 3F6h
    MOV AL, 00001010b
    OUT DX, AL

    mov dx, 0x1f7
    mov al, 0xA0
    out dx, al 

    call isBSY
    call isDRQ

    mov dx, 0x1f0
    mov ax, 0x1E
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    call isBSY

    mov dx, 0x1f7
    mov al, 0xA0
    out dx, al

    call isBSY
    call isDRQ

    mov dx, 0x1f0
    mov ax, 1Bh
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 2
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    call isBSY
    ret

isBSY:
    MOV DX, 1F7h 
LOOP1:
    IN AL, DX 
    AND AL, 0x80
    jne LOOP1
    ret
isDRQ:
    MOV DX, 1F7h 
LOOP4:
    IN AL, DX
    AND AL,0x08 
    JE LOOP4
    ret

_printError:
mov dx, 0x1f1
mov ax, 0
in al, dx
push eax
call printNum
pop eax
ret

_closecd:

 call isBSY

    mov dx, 0x1f6
    mov al, 10h
    out dx, al 

    mov dx, 0x1f7
    mov al, 0xA0 ;ATAPI COMMAND
    out dx, al 

    call isBSY
    call isDRQ

    mov dx, 0x1f0
    mov ax, 1Bh
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 3
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    call isBSY
    ret

_infoCD:

    call isBSY

    mov dx, 0x1f6
    mov al, 10h
    out dx, al 

    mov dx, 0x1F4
    mov al, 0x08
    out dx, al

    mov dx, 0x1F5
    mov al, 0x08
    out dx, al

    mov dx, 0x1f7
    mov al, 0xA0 ;ATAPI COMMAND
    out dx, al 

    call isBSY
    call isDRQ

    mov dx, 0x1f0

    mov ax, 0x25
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    mov ax, 0
    out dx, ax

    call isBSY
    call printbusy
    ;call isDRQ                                  
    
    mov dx, 1f0h

    mov ebx, 0
    in ax, dx
    mov [buffer + ebx], ax
    
    add ebx, 2
    in ax, dx
    mov [buffer + ebx], ax

    add ebx, 2
    in ax, dx
    mov [buffer + ebx], ax

    add ebx, 2
    in ax, dx
    mov [buffer + ebx], ax

    mov eax, [buffer]
    mov ebx, [buffer + 4]
    add eax,ebx
    push ebx
    push eax
    call printCapacity
    add esp,8

    ret


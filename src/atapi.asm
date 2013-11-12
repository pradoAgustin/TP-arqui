GLOBAL  _opencd, _closecd, _infoCD
EXTERN printNum
EXTERN printCapacity
EXTERN printReady
EXTERN printRegister
EXTERN printbusy


_opencd:

     call isBSY

    mov dx, 0x1f6
    mov al, 10h
    out dx, al 

    mov dx, 0x1f1
    mov al, 0
    out dx, al 

MOV DX, 3F6h ;Device Control register
MOV AL, 00001010b ;nIEN is the second bit from the right here
OUT DX, AL ;nIEN is now one!

    mov dx, 0x1f7
    mov al, 0xA0 ;ATAPI COMMAND
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
    call isDRDY

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


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;pollbsy es fijarse si busy no esta en 1
;;isDRQ es fijarse que drq este en 1
;;0x1E  y todo cero es para habilitar la lectora
;;para cerrar la lectora no hace falta 0x1E
;; solo hace falta 0x1B
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
isBSY:
MOV DX, 1F7h 
LOOP1:
IN AL, DX 
AND AL, 0x80
JNE LOOP1
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
isDRDY:
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
isDRQ:
MOV DX, 1F7h 
LOOP4:
IN AL, DX
AND AL,0x08 
JE LOOP4
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


_printError:
mov dx, 0x1f1
mov ax, 0
in al, dx
push eax
call printNum
pop eax
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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

SECTION .bss

buffer resb 8



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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


section .bss
    array resb 8

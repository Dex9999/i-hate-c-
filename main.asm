[org 0x7c00]
bits 16

jmp main
;
; Print a string
;   - bx: address of string
;
puts:
    mov al, [bx]
    cmp al, 0
    je exit
    mov ah, 0x0e        ; display character in tty mode
    int 0x10                 ;   - read from al
    inc bx
    jmp puts
exit:
    ret
;
; Read a string into `buffer`
;
readstr:
    mov bx, buffer
    jmp readchar

    readchar:
        mov ah, 0
        int 0x16
        cmp al, 0x0D        ; check for carriage return
        je storestr
        push ax
        inc bx
        jmp readchar
    storestr:
        dec bx
        pop ax
        mov [bx], al
        cmp bx, buffer
        jle exit
        jmp storestr
main:
    call readstr
    mov bx, buffer
    call puts

    jmp main

str: db "hello world", 0 ; not used in this program
buffer: times 64 db 0

times 510-($-$$) db 0
db 0x55, 0xAA

; compile on linux comp
;nasm -f bin main.asm -o main.bin
;qemu-system-x86_64 main.bin
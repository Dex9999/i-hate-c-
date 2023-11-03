bits 64

; assembly comment syntax
; this is all written in intel syntax because better

; r stands for really big (real)
; mov means move
; mov rdi, 8 means move the value 8 into the 64 bit register, referred to as rdi (mem address?)
; mov rdi, rsi = move the val of rsi into rdi

; memory operations
; mov rdi, qword ptr [rsi]
; means treat rsi value as a pointer, remove 8 bytes from memory and put in rdi
; val from memory into register
; mov qword ptr [rsi], rdi
; opposite, put val from register into memory
; [blah] is a memory address

; standard in = 0 ?
; standard out = 1 ?
; standard err = 2 ?

; syscall table! https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/

;exposes symbol called _start to the linker so it knows where code starts
global  _start

section .text
    _start:  
      mov rdi, 8
      mov rsi, rdi
      ; now both rdi and rsi == 8
      
      ; setup for syscall, use handy table!

      ; print!
      ; %rax	System call	%rdi	%rsi	%rdx
      ; 1,	sys_write,	unsigned int fd,	const char *buf,	size_t count
      ;mov rax, 1
      ;mov rdi, 1 ; fd = file descriptor, std out = 1?
      ;lea rsi, [uhohree] ; address (pointer) of our buffer with the string, lea = load effective address
      ; square brackets can be omitted because lea assumes a memory address anyway, elsewise it's how you specify mem address
      ;mov rdx, 8 ; length
      ;syscall

      mov rbx, 1

      ; Add the value of 'val' (2) to rbx
      mov rax, [val]
      add rbx, rax
      ; rbx = 1 + 3
      ; now write it by updating
      ;mov rax, 1
      ;mov rdi, 1
      ;lea rsi, [rbx]
      ;mov rdx, 1
      ;syscall
      ;why noi wokr :( 
      

      ; exit with error value rbx
      ; %rax	System call	%rdi
      ; 60	sys_exit	int error_code
      mov rax, 60
      mov rdi, rbx
      syscall


section   .data
    uhohree: db "uhohree", 10 ; unicode for newline
    val: dd 2
    ; db = define byte, 8bit data
    ; dq = define quadword, 64 bit data

; you can do without section but just dont :)

; compile on linux comp
; nasm -felf64 main.asm
; ld main.o
; ./a.out
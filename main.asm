.global  _start
.intel_syntax noprefix

    _start:  

      mov rax, 1
      mov rdi, 1
      lea rsi, [hello_world]
      mov rdx, 6
      syscall

      mov rdi, [my_int]
      add rdi, 2
      sub rdi, 4
      imul rdi, 3

      mov rax, 60      
     
      syscall


hello_world:
    .asciz "string"

my_int:      
    .int 6 

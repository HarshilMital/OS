section .data
        int_a  db  "Enter integer: ",0  ;ineger input
        str_a  db  "Enter string: ",0  ;string input
        nxtln  db  " ", 10, 0      ;new line
        str1    db  "%s", 0        ;string format
        int1    db  "%d", 0       ;integer format



section .bss
        int_inp resd  1
        str_inp resd  1


section .text
        global main
        extern printf
        extern scanf
        extern exit

main: 

        push rbp ;setup stack

        ;prints input line
        lea rdi, [int_a] 
        xor rax, rax
        call printf


        ;takes integer from the user
        lea rdi, [int1]
        lea rsi, [int_inp]
        xor rax, rax
        call scanf

        lea rdi, [str_a] 
        xor rax, rax
        call printf

        ;take string from the user
        lea rdi, [str1]
        lea rsi, [str_inp]
        xor rax, rax
        call scanf


        ;printing the value of int_inp
        lea rdi, [int1]
        mov esi, [int_inp]  
        xor rax, rax
        call printf

        ;new line
        lea rdi, [nxtln]
        xor rax, rax
        call printf


        ;printing the value of str_inp
        lea rdi, [str1]
        lea rsi, [str_inp]
        xor rax, rax
        call printf

        ;printf("\n");
        lea rdi, [nxtln]
        xor rax, rax
        call printf

        ; return
        pop rbp ;restore stack
        mov rax, 0 ;normal exit
        ret
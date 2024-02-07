section .text
    global asm_strlen

asm_strlen:
    ; Input: rdi - pointer to the input string
    ; Output: rax - length of the string

    ; Initialize the counter to 0
    xor rax, rax

    ; Check if the string is NULL (empty)
    test rdi, rdi
    jz .end

    ; Loop to iterate through the string
.loop:
    ; Check if the current character is NULL (end of the string)
    cmp byte [rdi], 0
    je .end

    ; Move to the next character
    inc rdi

    ; Increment the counter
    inc rax

    ; Continue the loop
    jmp .loop

.end:
    ret

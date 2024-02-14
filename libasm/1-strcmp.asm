section .text
global asm_strcmp

asm_strcmp:
    ; Input parameters:
    ;   rdi: pointer to the first string (s1)
    ;   rsi: pointer to the second string (s2)
    ; Output:
    ;   rax: result (0 if equal, positive if s1 > s2, negative if s1 < s2)

    ; Initialize counters
    xor rax, rax   ; rax will store the result

    ; Compare strings character by character
    cmp_loop:
        ; Load characters from strings
        mov al, [rdi]   ; load a character from s1 into al
        mov bl, [rsi]   ; load a character from s2 into bl

        ; Compare characters
        cmp al, bl
        jne end_cmp_loop  ; jump to end_cmp_loop if characters are not equal

        ; Check for null terminator
        cmp al, 0
        je  end_cmp_loop  ; jump to end_cmp_loop if null terminator is reached

        ; Move to the next characters in the strings
        inc rdi
        inc rsi
        jmp cmp_loop     ; jump back to cmp_loop

    end_cmp_loop:
        ; Calculate the result based on the characters
        sub al, bl  ; subtract the characters
        ret

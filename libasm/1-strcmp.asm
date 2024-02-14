section .text
    global asm_strcmp

asm_strcmp:
    ; Arguments:
    ;   rdi: pointeur vers la première chaîne
    ;   rsi: pointeur vers la deuxième chaîne

    ; Initialisation des registres
    xor rax, rax  ; rax: résultat
    xor rcx, rcx  ; rcx: compteur pour boucle

    ; Boucle de comparaison des caractères
    cmp_loop:
        ; Charger le caractère de la première chaîne dans al
        mov al, [rdi]
        ; Charger le caractère de la deuxième chaîne dans bl
        mov bl, [rsi]
        ; Test pour savoir si le caractère de la première chaîne est nul
        test al, bl
        jz cmp_done  ; Si le caractère de la première chaîne est nul, terminer la comparaison
        ; Comparer les caractères 
        cmp al, bl
        jne cmp_done
        ; Incrémenter les pointeurs et continuer la boucle
        inc rdi
        inc rsi
        ; Incrémenter le compteur et continuer la boucle
        inc rcx
        jmp cmp_loop

    cmp_done:
        ; Soustraire les pointeurs pour obtenir la longueur de la différence
        sub rax, rcx
        ; Retourner le résultat
        ret

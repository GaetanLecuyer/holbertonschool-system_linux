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
        mov al, [rdi + rcx]
        ; Charger le caractère de la deuxième chaîne dans bl
        mov bl, [rsi + rcx]
        ; Comparer les caractères
        cmp al, bl
        ; Si les caractères sont différents, terminer la comparaison
        jne cmp_done
        ; Si les deux caractères sont nuls, terminer la comparaison
        test al, al
        jz cmp_done
        ; Incrémenter le compteur et continuer la boucle
        inc rcx
        jmp cmp_loop

    cmp_done:
        ; Soustraire les caractères pour obtenir le résultat
        sub al, bl
        ; Retourner le résultat
        ret

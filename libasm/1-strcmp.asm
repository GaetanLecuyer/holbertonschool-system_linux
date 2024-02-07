section .text
    global asm_strcmp

asm_strcmp:
    ; Entrées : rdi - pointeur vers la première chaîne (s1)
    ;           rsi - pointeur vers la deuxième chaîne (s2)
    ; Sortie : rax - résultat entier de la comparaison des chaînes
    ;                  0 si les chaînes sont égales
    ;                  positif si s1 > s2
    ;                  négatif si s1 < s2

    ; Boucle pour parcourir les chaînes
.loop:
    ; Charger les caractères actuels de s1 et s2
    mov al, [rdi]
    mov bl, [rsi]

    ; Comparer les caractères
    cmp al, bl

    ; Si les caractères ne sont pas égaux ou si on atteint la fin de l'une des chaînes, sortir de la boucle
    jne .end
    ; Si on atteint la fin de l'une des chaînes, sortir de la boucle
    cmp al, 0
    je .end

    ; Passer au caractère suivant dans chaque chaîne
    inc rdi
    inc rsi

    ; Continuer la boucle
    jmp .loop

.end:
    ; Calculer le résultat final en fonction de la dernière comparaison
    sub al, bl

    ret

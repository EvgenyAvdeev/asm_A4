#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(char* s) {
    int flag = 0;
    char sim[] = "!@#$%^&*()-_`~/?{}[]|:;',=+\\ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ\t<>üöäß0§ÜÖÄqwertyuiopsdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    size_t len = strlen(s);
    size_t len_sim = strlen(sim);
    for (int i = 0; i < len_sim; i++) {
        for (int j = 0; j < len; j++) {
            if (sim[i] == s[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
        }
    }
    return flag;
}

void main() {
    while (1) {
        int flag;
        printf("Choise:\n1) A4.1\n2) A4.2\n");
        scanf("%d", &flag);
        switch (flag)
        {
        case 1:
        {
            short int i, Count = 0, C[17];
            signed char A[17], B[9];
            char input[2];
            
            printf("Input array A: ");
            for (i = 0; i < 16; i++) {
                scanf("%s", &input);
                if (check(input)) {
                    printf("\nWRONG STRING\n");
                    exit(1);
                }
                else {
                    A[i] = (signed char)input;
                }
                
            }
            printf("Array A before: ");
            for (i = 0; i < 16; i++) {
                printf("%d ", A[i]);
            }
            _asm
            {
                lea esi, [A]; // берём начальный адрес(смещение) массива А 
                lea edi, [B]; // берём начальный адрес(смещение) массива В
                lea ebx, [C]; // берём начальный адрес(смещение) массива С
                mov Count, 0; // Count = 0
                mov ecx, 8; // ecx = 8
            BEG:
                mov ah, [esi]; // ah = A[esi]
                inc esi; // esi = esi + 1
                mov al, [esi]; // al = A[esi]
                cmp ah, al; // сравниваем старший и младший байт
                jnl L; // Если в слове старший байт не меньше младшего переходим к метке L (числа знаковые)
                dec esi; // esi = esi - 1
                mov[ebx], esi; // в массив С поместить адрес(смещение) этого байта
                mov[edi], ah; // в массив В копируем этот байт
                mov[esi], byte ptr 0; // заменяем его нулем
                add ebx, 4; // ebx = ebx + 4
                inc edi; // edi = edi + 1
                inc esi; // esi = esi + 1
                inc Count; // Count = Count + 1
            L:
                inc esi; // esi = esi + 1
                loop BEG // ecx = ecx - 1
            }
            if (B != NULL) {
                printf("\nCount of word = %d", Count);
                printf("\nArray A after: ");
                for (i = 0; i < 16; i++) {
                    printf("%d ", A[i]);
                }
                printf("\nArray B:\n");
                for (i = 0; i < Count; i++)
                    printf("%d ", B[i]);
                printf("\nArray C:\n");
                for (i = 0; i < 2 * Count; i++)
                    printf("%p ", C[i]);
            }
            break;
        }
        case 2:
        {
            int i, Count = 0;
            short int A[17], B[9], C[17];
            int input;
            printf("Input array A: ");
            for (i = 0; i < 16; i++) {
                scanf("%d", &input);
                A[i] = (short int)input;
            }
            printf("Array A before: ");
            for (i = 0; i < 16; i++) {
                printf("%d ", A[i]);
            }
            _asm
            {
                lea esi, [A];
                lea edi, [B];
                lea ebx, [C];
                mov[Count], 0;
                mov ecx, 8;
            BEGIN:
                mov dx, [esi];
                add esi, 2;
                mov ax, [esi];
                cmp dx, ax;
                jnl LO;
                sub esi, 2;
                mov[ebx], esi;
                mov[edi], dx;
                mov[esi], word ptr 0;
                add ebx, 4;
                add edi, 2;
                add esi, 2;
                inc[Count];
            LO:
                add esi, 2;
                loop BEGIN
            }
            if (B != NULL) {
                printf("\nCount of word = %d", Count);
                printf("\nArray A after: ");
                for (i = 0; i < 16; i++) {
                    printf("%d ", A[i]);
                }
                printf("\nArray B:\n");
                for (i = 0; i < Count; i++)
                    printf("%d ", B[i]);
                printf("\nArray C:\n");
                for (i = 0; i < 2 * Count; i++)
                    printf("%p ", C[i]);
            }
            break;
        }
        default:
            break;
        }

        int choise;
        printf("\nMenu:\n1) Restart\n2) Exit  \n");
        scanf("%d", &choise);
        if (choise == 2) {
            exit(0);
        }
    }
    
    return 0;
}

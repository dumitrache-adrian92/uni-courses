%include "../utils/printf32.asm"

section .text

extern printf
global main
main:
    ; numbers are placed in these two registers
    mov eax, 400
    mov ebx, 100

    ; TODO: get maximum value. You are only allowed to use one conditional jump and push/pop instructions.
    cmp eax, ebx
    jge max
    push eax
    push ebx
    pop eax
    pop ebx
max:
    PRINTF32 `Max value is: %d\n\x0`, eax ; print maximum value

    ret

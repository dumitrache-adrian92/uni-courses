%include "../utils/printf32.asm"

%define NUM 5

section .text

extern printf
global main
main:
    mov ebp, esp

    ; TODO 1: replace every push by an equivalent sequence of commands (use direct addressing of memory. Hint: esp)
    mov ecx, NUM
push_nums:
    ; push ecx
    sub esp, 4
    mov [esp], ecx
    loop push_nums

    ; push 0
    sub esp, 4
    mov [esp], dword 0
    ; push "mere"
    sub esp, 4
    mov [esp], dword "mere"
    ;push "are "
    sub esp, 4
    mov [esp], dword "are "
    ;push "Ana "
    sub esp, 4
    mov [esp], dword "Ana "

    lea esi, [esp]
    PRINTF32 `%s\n\x0`, esi

    ; TODO 2: print the stack in "address: value" format in the range of [ESP:EBP]
    ; use PRINTF32 macro - see format above
    lea esi, [esp]
    PRINTF32 `%s\n\x0`, esi
    ; TODO 3: print the string

    ; TODO 4: print the array on the stack, element by element.

    ; restore the previous value of the EBP (Base Pointer)
    mov esp, ebp

    ; exit without errors
    xor eax, eax
    ret

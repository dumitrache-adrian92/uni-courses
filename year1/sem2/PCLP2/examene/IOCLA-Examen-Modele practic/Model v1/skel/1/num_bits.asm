%include "utils/printf32.asm"


section .data
    arr1 db 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x99, 0x88
    len1 equ $-arr1
    arr2 db 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef
    len2 equ $-arr2
    val1 dd 0xabcdef01
    val2 dd 0x62719012


section .text
global main


main:
    push ebp
    mov ebp, esp


    ; TODO a: Print if sign bit is present or not.


    ; TODO b: Prin number of bits for integer value.


    ; TODO c: Prin number of bits for array.


    ; Return 0.
    xor eax, eax
    leave
    ret

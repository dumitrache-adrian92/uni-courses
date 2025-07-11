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
extern printf

main:
    push ebp
    mov ebp, esp
    push ebx
    ; TODO a: Print if sign bit is present or not.
    xor eax, eax
    xor ebx, ebx

    mov eax, [val1]
    mov ebx, [val2]

    shr eax, 31
    shr ebx, 31

    and eax, 0b1
    and ebx, 0b1
    ; val1
    cmp eax, 0
    je no_sign_bit
    PRINTF32 `sign bit for val1\n\x0`
    jmp skip_val1
no_sign_bit:
    PRINTF32 `no sign bit for val1\n\x0`
skip_val1:
    ; val2
    cmp ebx, 0
    je no_sign_bit_2
    PRINTF32 `sign bit for val2\n\x0`
    jmp skip_val2
no_sign_bit_2:
    PRINTF32 `no sign bit for val2\n\x0`
skip_val2:

    ; TODO b: Prin number of bits for integer value.
    xor eax, eax
    xor ebx, ebx

    mov eax, [val1]
    mov ebx, [val2]

    xor edx, edx

count_bits_val1:
    test eax, 1
    jz incr
    inc edx
incr:
    shr eax, 1
    cmp eax, 0
    je print
    jmp count_bits_val1
print:
    PRINTF32 `%d\n\x0`, edx

    xor edx, edx

count_bits_val2:
    xor esi, esi
    mov esi, ebx
    and esi, 1
    cmp esi, 1
    jne bit_off_2
    inc edx
bit_off_2:
    shr ebx, 1
    cmp ebx, 0
    jne count_bits_val2
    PRINTF32 `%d\n\x0`, edx
    
    ; TODO c: Prin number of bits for array.
    xor eax, eax
    xor ebx, ebx
    xor edx, edx
    xor esi, esi

    xor ecx, ecx

array_traversal:
    mov al, BYTE[arr1 + ecx]

count_bits_arr1:
    xor esi, esi
    mov esi, eax
    and esi, 1
    cmp esi, 1
    jne bit_off_arr1
    inc edx
bit_off_arr1:
    shr eax, 1
    cmp eax, 0
    jne count_bits_arr1

    inc ecx
    cmp ecx, len1
    jne array_traversal
    PRINTF32 `%d\n\x0`, edx

    xor ecx, ecx
    xor edx, edx

array_traversal_2:
    mov al, BYTE[arr2 + ecx]

count_bits_arr2:
    xor esi, esi
    mov esi, eax
    and esi, 1
    cmp esi, 1
    jne bit_off_arr2
    inc edx
bit_off_arr2:
    shr eax, 1
    cmp eax, 0
    jne count_bits_arr2

    inc ecx
    cmp ecx, len2
    jne array_traversal_2
    PRINTF32 `%d\n\x0`, edx

    pop ebx
    ; Return 0.
    xor eax, eax
    leave
    ret

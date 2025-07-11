section .text
	global cpu_manufact_id
	global features
	global l2_cache_info

;; void cpu_manufact_id(char *id_string);
;
;  reads the manufacturer id string from cpuid and stores it in id_string
cpu_manufact_id:
	enter 	0, 0
	; prezerv registrele
	push ebx
	push edi
	push esi
	mov edi, [ebp + 8] ; id_string
	xor eax, eax ; 0 pt manufacturer id
	cpuid

	; concatenez rezultatul
	mov DWORD [edi], ebx
	add edi, 4
	mov DWORD [edi], edx
	add edi, 4
	mov DWORD [edi], ecx

	pop esi
	pop edi
	pop ebx
	leave
	ret

;; void features(int *apic, int *rdrand, int *mpx, int *svm)
;
;  checks whether apic, rdrand and mpx / svm are supported by the CPU
;  MPX should be checked only for Intel CPUs; otherwise, the mpx variable
;  should have the value -1
;  SVM should be checked only for AMD CPUs; otherwise, the svm variable
;  should have the value -1
features:
	enter 0, 0
	push ebx
	push esi
	push edi

	; apic
	mov ebx, [ebp + 8]
	mov DWORD [ebx], 1

	; apel pentru features
	xor eax, eax
	mov eax, 1
	cpuid
	; verificam daca bitul pt apic e pornit
	xor eax, eax
	mov eax, edx
	and eax, 512
	cmp eax, 512
	je APIC_end
	mov DWORD [ebx], 0
APIC_end:

	mov ebx, [ebp + 12]
	mov DWORD [ebx], 1
	; verificam daca bitul pentru RDRND e pornit
	xor eax, eax
	mov eax, ecx
	and eax, 1073741824
	cmp eax, 1073741824
	je RDRND_end
	mov DWORD [ebx], 0
RDRND_end:



	pop edi
	pop esi
	pop ebx
	leave
	ret

;; void l2_cache_info(int *line_size, int *cache_size)
;
;  reads from cpuid the cache line size, and total cache size for the current
;  cpu, and stores them in the corresponding parameters
l2_cache_info:
	enter 	0, 0

	leave
	ret

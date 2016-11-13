; Module Name: get_machine_code.asm
; Description: Gets the machine code for the given instruction
; Date: 
; Author: 

INCLUDE cmacros.inc

; C calling conventions: 
;  EBP, EBX, ESI, EDI should not be modified in a function call (non-volatile)
;  EAX, ECX, EDX can be modified (volatile)

Instruction STRUCT
	mnemonic DWORD 0
	op1 DWORD 0
	op2 DWORD 0
Instruction ENDS

;----------------------
.code
;-----------------------------------------------------
; Description: 
; Receives: 
; Returns: 
;-----------------------------------------------------
getMachineCode PROC
	; Prolog
	push	ebp
	mov		ebp, esp
	push	esi
	push	edi

	; Use esi, edi, ecx to contain the three parameters
	mov		esi, parameterA
	mov		edi, parameterB
	mov		ecx, parameterC

	; Return some fake machine code
	mov		[edi], BYTE PTR 41h
	mov		[edi+1], BYTE PTR 42h
	mov		[edi+2], BYTE PTR 43h
	mov		[edi+3], BYTE PTR 44h
	; Count
	mov		[ecx], DWORD PTR 4

	; Epilog
	pop		edi
	pop		esi
	mov		esp, ebp
	pop		ebp
	ret
getMachineCode ENDP

END
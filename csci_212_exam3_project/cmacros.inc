; Module Name: macro_usage.asm
; Description: Demonstrates the use of macros
; Date: 11/13/2016
; Author: Lem Davis

; Usual directives
.model flat,C

; Declare some standard C functions externals
extern printf:PROC
extern putchar:PROC
extern getchar:PROC
extern exit:PROC

;----------------------------------------------------
; MACROS
;-----------------------------------------------------
; Description: Prints a newline
; Receives: Nothing
; Returns: Nothing
;-----------------------------------------------------
mNewLine MACRO
	push	10					; newline character
	call	putchar
	add		esp, TYPE DWORD
ENDM

;-----------------------------------------------------
; Description: Prints a character
; Receives: A byte value
; Returns: Nothing
;-----------------------------------------------------
mPutChar MACRO bVar
	push	eax
	xor		eax, eax
	mov		al, bVar
	push	eax
	call	putchar
	add		esp, TYPE DWORD
	pop		eax
ENDM

;-----------------------------------------------------
; Description: Prints a message, waits for Enter key
; Receives: Literal string
; Returns: Nothing
;-----------------------------------------------------
mWaitMsg MACRO msg
	LOCAL string
	.data
	string BYTE msg, 0
	.code
	; Print the wait message string
	push	OFFSET string
	call	printf
	add		esp, TYPE DWORD

	; Wait for the Enter key
	call	getchar
ENDM

;-----------------------------------------------------
; Description: Replaces "\n" with cr,lf
; Receives: Pointer to string in ESI
; Returns: Updated string
;-----------------------------------------------------
mBackslashN MACRO
	LOCAL L1, L2, Next

	;; The string is scanned, "\n" is replaced with cr,lf
	;; Scanning continues until null terminating character is found
	push	esi
L1:
	cmp		BYTE PTR [esi], 0
	je		L2
	cmp		BYTE PTR [esi], '\'
	jne		Next
	cmp		BYTE PTR [esi+1], 'n'
	jne		Next
	;; OK found \n
	mov		BYTE PTR [esi], 0Ah
	mov		BYTE PTR [esi+1], 0Dh
	add		esi, 2
	jmp		L1

Next:
	inc		esi
	jmp		L1

L2:
	;; At this point, the string has been modified if "\n" was found
	pop		esi
ENDM

;-----------------------------------------------------
; Description: Shows use of LOCAL, shows how "\n" can be used
; Receives: Literal string containing one or more "\n" substrings
; Returns: Nothing
;-----------------------------------------------------
mPrintf MACRO formatStr, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10
	LOCAL string, TheExit
	.data
	string BYTE formatStr, 0
	.code
	pushad		;; Save all registers
	pushfd		;; Save flags

	;; Replace the "\n" substrings with cr,lf
	push	esi
	mov		esi, OFFSET string
	mBackslashN
	pop		esi

	;; Push up to ten parameters to use when calling printf
	;; Need to do more work on extension, check format for sign
	IFNB	<p10>
		mov		eax, p10	;; Make sure 32 bits
		push	eax
	ENDIF
	IFNB	<p9>
		mov		eax, p9	;; Make sure 32 bits
		push	eax
	ENDIF
	IFNB	<p8>
		mov		eax, p8	;; Make sure 32 bits
		push	eax
	ENDIF
	IFNB	<p7>
		mov		eax, p7	;; Make sure 32 bits
		push	eax
	ENDIF
	IFNB	<p6>
		mov		eax, p6	;; Make sure 32 bits
		push	eax
	ENDIF
	IFNB	<p5>
		mov		eax, p5	;; Make sure 32 bits
		push	eax
	ENDIF
	IFNB	<p4>
		mov		eax, p4	;; Make sure 32 bits
		push	eax
	ENDIF
	IFNB	<p3>
		mov		eax, p3	;; Make sure 32 bits
		push	eax
	ENDIF
	IFNB	<p2>
		mov		eax, p2	;; Make sure 32 bits
		push	eax
	ENDIF
	IFNB	<p1>
		mov		eax, p1	;; Make sure 32 bits
		push	eax
	ENDIF

	;; Now call printf
	push	OFFSET string
	call	printf

	;; Now restore stack based on how many parameters were pushed
	IFNB	<p10>
		add		esp, 11 * TYPE DWORD
		jmp		TheExit
	ENDIF
	IFNB	<p9>
		add		esp, 10 * TYPE DWORD
		jmp		TheExit
	ENDIF
	IFNB	<p8>
		add		esp, 9 * TYPE DWORD
		jmp		TheExit
	ENDIF
	IFNB	<p7>
		add		esp, 8 * TYPE DWORD
		jmp		TheExit
	ENDIF
	IFNB	<p6>
		add		esp, 7 * TYPE DWORD
		jmp		TheExit
	ENDIF
	IFNB	<p5>
		add		esp, 6 * TYPE DWORD
		jmp		TheExit
	ENDIF
	IFNB	<p4>
		add		esp, 5 * TYPE DWORD
		jmp		TheExit
	ENDIF
	IFNB	<p3>
		add		esp, 4 * TYPE DWORD
		jmp		TheExit
	ENDIF
	IFNB	<p2>
		add		esp, 3 * TYPE DWORD
		jmp		TheExit
	ENDIF
	IFNB	<p1>
		add		esp, 2 * TYPE DWORD
		jmp		TheExit
	ENDIF
	add		esp, 1 * TYPE DWORD

TheExit:
	popfd
	popad
ENDM

; You can use the following symbolic constants to make
; accessing parameters easier
IFNDEF paramaterA
parameterA EQU [ebp+8]
parameterB EQU [ebp+12]
parameterC EQU [ebp+16]
parameterD EQU [ebp+20]
parameterE EQU [ebp+24]
parameterF EQU [ebp+28]
parameterG EQU [ebp+32]
ENDIF
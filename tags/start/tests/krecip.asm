; ************************
; **  Start Data Block  **
; ************************
SECTION .data
extern fpuasm
extern reciptable

global _asm_krecipasm
; ************************
; **  Start Code Block  **
; ************************
SEGMENT .text

; Ignore all the 'offset's in the code AH
%idefine offset

ALIGN 16
;	"mov fpuasm, eax",\
;	"fild dword ptr fpuasm",\
;	"add eax, eax",\
;	"fstp dword ptr fpuasm",\
;	"sbb ebx, ebx",\
;	"mov eax, fpuasm",\
;	"mov ecx, eax",\
;	"and eax, 0x007ff000",\
;	"shr eax, 10",\
;	"sub ecx, 0x3f800000",\
;	"shr ecx, 23",\
;	"mov eax, dword ptr reciptable[eax]",\
;	"sar eax, cl",\
;	"xor eax, ebx",\

_asm_krecipasm:
	mov [fpuasm], eax	; Store parameter to memory
	fild dword [fpuasm]     ; Convert the 32-bit int to a fp
	add eax, eax            ; Double the int param's value
	fstp dword [fpuasm]     ; Put the 32-bit float to memory
	sbb ebx, ebx            ; Puts 0 - (carry bit) into ebx AFFECTED BY "add eax eax"!!!
	mov eax, dword [fpuasm]
	mov ecx, eax
	and eax, 007ff000h
	shr eax, 10
	sub ecx, 03f800000h
	shr ecx, 23
	mov eax, dword [reciptable + eax]
	sar eax, cl
	xor eax, ebx
	ret
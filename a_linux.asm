; // "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
; // Ken Silverman's official web site: "http://www.advsys.net/ken"
; // See the included license file "BUILDLIC.TXT" for license info.
; // This file has been modified from Ken Silverman's original release

; These two aren't needed AH
;.586P
;.8087

;include mmx.inc       ;Include this if using < WATCOM 11.0 WASM

;Warning: IN THIS FILE, ALL SEGMENTS ARE REMOVED.  THIS MEANS THAT DS:[]
;MUST BE ADDED FOR ALL SELF-MODIFIES FOR MASM TO WORK.
;
;WASM PROBLEMS:
;   1. Requires all scaled registers (*1,*2,*4,*8) to be last thing on line
;   2. Using 'DATA' is nice for self-mod. code, but WDIS only works with 'CODE'
;
;MASM PROBLEMS:
;   1. Requires DS: to be written out for self-modifying code to work
;   2. Doesn't encode short jumps automatically like WASM
;   3. Stupidly adds wait prefix to ffree's

; ************************
; **  Start Data Block  **
; ************************
SECTION .data

    ; Some C compilers insert an underscore ('_') character in front of
    ;  identifiers. In such a case, we need to redefine our references to
    ;  global indentifiers that exist in the C code.  --ryan.
%ifdef C_IDENTIFIERS_UNDERSCORED
%define asm1 _asm1
%define asm2 _asm2
%define asm3 _asm3
%define asm4 _asm4
%define fpuasm _fpuasm
%define reciptable _reciptable
%define globalx3 _globalx3
%define globaly3 _globaly3
%define ylookup _ylookup
%define vplce _vplce
%define vince _vince
%define palookupoffse _palookupoffse
%define bufplce _bufplce
%define ebpbak _ebpbak
%define espbak _espbak
%define pow2char _pow2char
%define pow2long _pow2long
%endif

extern asm1
extern asm2
extern asm3
extern asm4
extern fpuasm
extern reciptable
extern globalx3
extern globaly3
extern ylookup

extern vplce
extern vince
extern palookupoffse
extern bufplce

extern ebpbak
extern espbak

extern pow2char
extern pow2long

; These are our globally-scoped labels (i.e. functions) AH
  global _asm_krecipasm
  global _asm_sethlinesizes
  global _asm_prosethlinesizes
  global _asm_setvlinebpl
  global _asm_setpalookupaddress
  global _asm_prosetpalookupaddress
  global _asm_setuphlineasm4
  global _asm_hlineasm4
  global _asm_prohlineasm4
  global _asm_setupvlineasm
  global _asm_prosetupvlineasm
  global _asm_setupmvlineasm
  global _asm_setuptvlineasm
  global _asm_prevlineasm1
  global _asm_vlineasm1
  global _asm_mvlineasm1
  global _asm_fixtransluscence
  global _asm_settransnormal
  global _asm_settransreverse
  global _asm_tvlineasm1
  global _asm_vlineasm4
  global _asm_provlineasm4
  global _asm_mvlineasm4
  global _asm_setupspritevline
  global _asm_spritevline
  global _asm_msetupspritevline
  global _asm_mspritevline
  global _asm_tsetupspritevline
  global _asm_tspritevline
  global _asm_msethlineshift
  global _asm_mhline
  global _asm_mhlineskipmodify
  global _asm_tsethlineshift
  global _asm_thline
  global _asm_thlineskipmodify
  global _asm_setuptvlineasm2
  global _asm_tvlineasm2
  global _asm_setupslopevlin2
  global _asm_slopevlin2
  global _asm_setupslopevlin
  global _asm_slopevlin
  global _asm_setuprhlineasm4
  global _asm_rhlineasm4
  global _asm_setuprmhlineasm4
  global _asm_rmhlineasm4
  global _asm_setupqrhlineasm4
  global _asm_qrhlineasm4
  global _asm_setupdrawslab
  global _asm_drawslab
  global _asm_stretchhline
  global _asm_mmxoverlay

  global _asm_isvmwarerunning


; ************************
; **   End Data Block   **
; ************************


; ************************
; **  Start Code Block  **
; ************************
SEGMENT .text

; Ignore all the 'offset's in the code AH
%idefine offset

; Align entire code block to 16 bit boundaries
ALIGN 16

_asm_isvmwarerunning:
	mov eax,564d5868h
	mov ecx,0000000ah
	mov dx,5658h
	in  eax,dx
	cmp ebx,564d5868h
	jz  vmware_y
	xor eax,eax
	ret
vmware_y:
        mov eax,1h
        ret

 
_asm_sethlinesizes:
	mov byte [machxbits1+2], al
	mov byte [machxbits2+2], al
	mov byte [machxbits3+2], al
	neg al
	mov byte [hxsiz1+2], al
	mov byte [hxsiz2+2], al
	mov byte [hxsiz3+2], al
	mov byte [hxsiz4+2], al
	mov byte [machnegxbits1+2], al

	mov byte [hysiz1+3], bl
	mov byte [hysiz2+3], bl
	mov byte [hysiz3+3], bl
	mov byte [hysiz4+3], bl
	mov byte [hmach3a+2], bl
	mov byte [hmach3b+2], bl
	mov byte [hmach3c+2], bl
	mov byte [hmach3d+2], bl

	mov dword [hoffs1+2], ecx
	mov dword [hoffs2+2], ecx
	mov dword [hoffs3+2], ecx
	mov dword [hoffs4+2], ecx
	mov dword [hoffs5+2], ecx
	mov dword [hoffs6+2], ecx
	mov dword [hoffs7+2], ecx
	mov dword [hoffs8+2], ecx

	mov edx, -1
	mov cl, al
	sub cl, bl
	shr edx, cl
	mov dword [hmach2a+1], edx
	mov dword [hmach2b+1], edx
	mov dword [hmach2c+1], edx
	mov dword [hmach2d+1], edx
   ret

ALIGN 16
_asm_prosethlinesizes:
	mov dword [prohbuf-4], ecx
	neg eax
	mov ecx, eax
	sub eax, ebx
	mov byte [prohshru-1], al   ;bl = 32-al-bl
	mov eax, -1
	shr eax, cl
	mov ecx, ebx
	shl eax, cl
	mov dword [prohand-4], eax  ;((-1>>(-oal))<<obl)
	neg ebx
	mov byte [prohshrv-1], bl   ;bl = 32-bl
	ret

ALIGN 16	
_asm_setvlinebpl:
	mov dword [fixchain1a+2], eax
	mov dword [fixchain1b+2], eax
	mov dword [fixchain1m+2], eax
	mov dword [fixchain1t+2], eax
	mov dword [fixchain1s+2], eax
	mov dword [mfixchain1s+2], eax
	mov dword [tfixchain1s+2], eax
	mov dword [fixchain2a+2], eax
	mov dword [profixchain2a+2], eax
	mov dword [fixchain2ma+2], eax
	mov dword [fixchain2mb+2], eax
	mov dword [fixchaint2a+1], eax
	mov dword [fixchaint2b+2], eax
	mov dword [fixchaint2c+2], eax
	mov dword [fixchaint2d+2], eax
	mov dword [fixchaint2e+2], eax
    ret

ALIGN 16
_asm_setpalookupaddress:
    mov dword [pal1+2], eax
	mov dword [pal2+2], eax
	mov dword [pal3+2], eax
	mov dword [pal4+2], eax
	mov dword [pal5+2], eax
	mov dword [pal6+2], eax
	mov dword [pal7+2], eax
	mov dword [pal8+2], eax
	ret

ALIGN 16
_asm_prosetpalookupaddress:
	mov dword [prohpala-4], eax
	ret

ALIGN 16
_asm_setuphlineasm4:
machxbits3: rol eax, 6                     ;xbits
    mov dword [hmach4a+2], eax
	mov dword [hmach4b+2], eax
	mov bl, al
	mov dword [hmach4c+2], eax
	mov dword [hmach4d+2], eax
	mov dword [hmach1a+2], ebx
	mov dword [hmach1b+2], ebx
	mov dword [hmach1c+2], ebx
	mov dword [hmach1d+2], ebx
    ret

	;Non-256-stuffed ceiling&floor method with NO SHLD!:
	;yinc&0xffffff00   lea eax, [edx+88888800h]           1     1/2
	;ybits...xbits     and edx, 88000088h                 1     1/2
	;ybits             rol edx, 6                         2     1/2
	;xinc<<xbits       add esi, 88888888h                 1     1/2
	;xinc>>(32-xbits)  adc al, 88h                        1     1/2
	;bufplc            mov cl, byte [edx+88888888h]   1     1/2
	;paloffs&255       mov bl, byte [ecx+88888888h]   1     1/2

_asm_hlineasm4:
	push ebp

	lea ebp, [eax+1]

	cmp ebp, 8
	jle NEAR shorthline

	test edi, 1
	jnz short skipthe1byte

	mov eax, esi
hxsiz1: shr eax, 26
hysiz1: shld eax, edx, 6
hoffs1: mov cl, byte [eax+88888888h]
pal1: mov bl, byte [ecx+88888888h]
	sub esi, [asm1]
	sub edx, [asm2]
	mov byte [edi], bl
	dec edi
	dec ebp

skipthe1byte:
	test edi, 2
	jnz short skipthe2byte

	mov eax, esi
hxsiz2: shr eax, 26
hysiz2: shld eax, edx, 6
hoffs2: mov cl, byte [eax+88888888h]
pal2: mov bh, byte [ecx+88888888h]
	sub esi, [asm1]
	sub edx, [asm2]

	mov eax, esi
hxsiz3: shr eax, 26
hysiz3: shld eax, edx, 6
hoffs3: mov cl, byte [eax+88888888h]
pal3: mov bl, byte [ecx+88888888h]
	sub esi, [asm1]
	sub edx, [asm2]
	mov word [edi-1], bx
	sub edi, 2
	sub ebp, 2

skipthe2byte:

	mov eax, esi
machxbits1: shl esi, 6                     ;xbits
machnegxbits1: shr eax, 32-6               ;32-xbits
	mov dl, al

	inc edi

	add ebx, ebx
	mov eax, edx
	jc beginhline64

	mov eax, [asm1]
machxbits2: rol eax, 6                     ;xbits
	mov dword [hmach4a+2], eax
	mov dword [hmach4b+2], eax
	mov dword [hmach4c+2], eax
	mov dword [hmach4d+2], eax
	mov ebx, eax
	mov eax, [asm2]
	mov al, bl
	mov dword [hmach1a+2], eax
	mov dword [hmach1b+2], eax
	mov dword [hmach1c+2], eax
	mov dword [hmach1d+2], eax

	mov eax, edx
	jmp beginhline64

prebeginhline64:
	mov dword [edi], ebx
beginhline64:

hmach3a: rol eax, 6
hmach2a: and eax, 00008888h
hmach4a: sub esi, 88888888h
hmach1a: sbb edx, 88888888h
	sub edi, 4
hoffs4: mov cl, byte [eax+88888888h]
	mov eax, edx

hmach3b: rol eax, 6
hmach2b: and eax, 00008888h
hmach4b: sub esi, 88888888h
hmach1b: sbb edx, 88888888h
pal4: mov bh, byte [ecx+88888888h]
hoffs5: mov cl, byte [eax+88888888h]
	mov eax, edx

hmach3c: rol eax, 6
pal5: mov bl, byte [ecx+88888888h]
hmach2c: and eax, 00008888h
	shl ebx, 16
hmach4c: sub esi, 88888888h
hmach1c: sbb edx, 88888888h
hoffs6: mov cl, byte [eax+88888888h]

	mov eax, edx
	;(

hmach3d: rol eax, 6
hmach2d: and eax, 00008888h
hmach4d: sub esi, 88888888h
hmach1d: sbb edx, 88888888h
pal6: mov bh, byte [ecx+88888888h]
hoffs7: mov cl, byte [eax+88888888h]
	mov eax, edx
	sub ebp, 4
	nop
pal7: mov bl, byte [ecx+88888888h]
	jnc NEAR prebeginhline64
skipthe4byte:

	test ebp, 2
	jz skipdrawthe2
	rol ebx, 16
	mov word [edi+2], bx
	sub edi, 2
skipdrawthe2:
	test ebp, 1
	jz skipdrawthe1
	shr ebx, 24
	mov byte [edi+3], bl
skipdrawthe1:

	pop ebp
	ret

shorthline:
	test ebp, ebp
	jz endshorthline
begshorthline:
	mov eax, esi
hxsiz4: shr eax, 26
hysiz4: shld eax, edx, 6
hoffs8: mov cl, byte [eax+88888888h]
pal8: mov bl, byte [ecx+88888888h]
	sub esi, [asm1]
	sub edx, [asm2]
	mov byte [edi], bl
	dec edi
	dec ebp
	jnz begshorthline
endshorthline:
	pop ebp
	ret


	;eax: 00000000 00000000 00000000 temp----
	;ebx: 00000000 00000000 00000000 temp----
	;ecx: UUUUUUuu uuuuuuuu uuuuuuuu uuuuuuuu
	;edx: VVVVVVvv vvvvvvvv vvvvvvvv vvvvvvvv
	;esi: cnt----- -------- -------- --------
	;edi: vid----- -------- -------- --------
	;ebp: paloffs- -------- -------- --------
	;esp: ???????? ???????? ???????? ????????

_asm_prohlineasm4:
	push ebp

	lea ebp, [ecx+88888888h]
prohpala:
	mov ecx, esi
	lea esi, [eax+1]
	sub edi, esi

prohbeg:
	mov eax, ecx
	shr eax, 20
prohshru:
	mov ebx, edx
	shr ebx, 26
prohshrv:
	and eax, 88888888h
prohand:
	movzx eax, byte [eax+ebx+88888888h]
prohbuf:
	mov al, [eax+ebp]
	sub ecx, [asm1]
	sub edx, [asm2]
	mov [edi+esi], al
	dec esi
	jnz prohbeg

	pop ebp
	ret

ALIGN 16
_asm_setupvlineasm:
		;First 2 lines for VLINEASM1, rest for VLINEASM4
	mov byte [premach3a+2], al
	mov byte [mach3a+2], al

	push ecx
	mov byte [machvsh1+2], al      ;32-shy
	mov byte [machvsh3+2], al      ;32-shy
	mov byte [machvsh5+2], al      ;32-shy
	mov byte [machvsh6+2], al      ;32-shy
	mov ah, al
	sub ah, 16
	mov byte [machvsh8+2], ah      ;16-shy
	neg al
	mov byte [machvsh7+2], al      ;shy
	mov byte [machvsh9+2], al      ;shy
	mov byte [machvsh10+2], al     ;shy
	mov byte [machvsh11+2], al     ;shy
	mov byte [machvsh12+2], al     ;shy
	mov cl, al
	mov eax, 1
	shl eax, cl
	dec eax
	mov dword [machvsh2+2], eax    ;(1<<shy)-1
	mov dword [machvsh4+2], eax    ;(1<<shy)-1
	pop ecx
	ret

ALIGN 16
_asm_prosetupvlineasm:
		;First 2 lines for VLINEASM1, rest for VLINEASM4
	mov byte [premach3a+2], al
	mov byte [mach3a+2], al

	push ecx
	mov byte [promachvsh1+2], al      ;32-shy
	mov byte [promachvsh3+2], al      ;32-shy
	mov byte [promachvsh5+2], al      ;32-shy
	mov byte [promachvsh6+2], al      ;32-shy
	mov ah, al
	sub ah, 16
	mov byte [promachvsh8+2], ah      ;16-shy
	neg al
	mov byte [promachvsh7+2], al      ;shy
	mov byte [promachvsh9+2], al      ;shy
	mov byte [promachvsh10+2], al     ;shy
	mov byte [promachvsh11+2], al     ;shy
	mov byte [promachvsh12+2], al     ;shy
	mov cl, al
	mov eax, 1
	shl eax, cl
	dec eax
	mov dword [promachvsh2+2], eax    ;(1<<shy)-1
	mov dword [promachvsh4+2], eax    ;(1<<shy)-1
	pop ecx
	ret

ALIGN 16
_asm_setupmvlineasm:
	mov byte [maskmach3a+2], al
	mov byte [machmv13+2], al
	mov byte [machmv14+2], al
	mov byte [machmv15+2], al
	mov byte [machmv16+2], al
	ret

ALIGN 16	
_asm_setuptvlineasm:
	mov byte [transmach3a+2], al
	ret

ALIGN 16
_asm_prevlineasm1:
	test ecx, ecx
	jnz _asm_vlineasm1

	add eax, edx
premach3a: shr edx, 32
	mov dl, byte [esi+edx]
	mov cl, byte [ebx+edx]
	mov byte [edi], cl
	ret

ALIGN 16
_asm_vlineasm1:
	push ebp
	mov ebp, ebx
	inc ecx
fixchain1a: sub edi, 320
beginvline:
	mov ebx, edx
mach3a: shr ebx, 32
fixchain1b: add edi, 320
	mov bl, byte [esi+ebx]
	add edx, eax
	dec ecx
	mov bl, byte [ebp+ebx]
	mov byte [edi], bl
	jnz short beginvline
	pop ebp
	mov eax, edx
	ret

;Masked vline
ALIGN 16
_asm_mvlineasm1:
	push ebp
	mov ebp, ebx
beginmvline:
	mov ebx, edx
maskmach3a: shr ebx, 32
	mov bl, byte [esi+ebx]
	cmp bl, 255
	je short skipmask1
maskmach3c: mov bl, [ebp+ebx]
	mov byte [edi], bl
skipmask1:
	add edx, eax
fixchain1m: add edi, 320
	sub ecx, 1
	jnc short beginmvline

	pop ebp
	mov eax, edx
	ret

ALIGN 16
_asm_fixtransluscence:
	mov dword [transmach4+2], eax
	mov dword [tmach1+2], eax
	mov dword [tmach2+2], eax
	mov dword [tmach3+2], eax
	mov dword [tmach4+2], eax
	mov dword [tran2traa+2], eax
	mov dword [tran2trab+2], eax
	mov dword [tran2trac+2], eax
	mov dword [tran2trad+2], eax
    ret

ALIGN 16
_asm_settransnormal:
	mov byte [transrev0+1], 83h
	mov byte [transrev1+1], 27h
	mov byte [transrev2+1], 3fh
	mov byte [transrev3+1], 98h
	mov byte [transrev4+1], 90h
	mov byte [transrev5+1], 37h
	mov byte [transrev6+1], 90h
	mov word [transrev7+0], 0f38ah
	mov byte [transrev8+1], 90h
	mov word [transrev9+0], 0f78ah
	mov byte [transrev10+1], 0a7h
	mov byte [transrev11+1], 81h
	mov byte [transrev12+2], 9fh
	mov word [transrev13+0], 0dc88h
	mov byte [transrev14+1], 81h
	mov byte [transrev15+1], 9ah
	mov byte [transrev16+1], 0a7h
	mov byte [transrev17+1], 82h
    ret

ALIGN 16
_asm_settransreverse:
	mov byte [transrev0+1], 0a3h
	mov byte [transrev1+1], 7h
	mov byte [transrev2+1], 1fh
	mov byte [transrev3+1], 0b8h
	mov byte [transrev4+1], 0b0h
	mov byte [transrev5+1], 17h
	mov byte [transrev6+1], 0b0h
	mov word [transrev7+0], 0d38ah
	mov byte [transrev8+1], 0b0h
	mov word [transrev9+0], 0d78ah
	mov byte [transrev10+1], 87h
	mov byte [transrev11+1], 0a1h
	mov byte [transrev12+2], 87h
	mov word [transrev13+0], 0e388h
	mov byte [transrev14+1], 0a1h
	mov byte [transrev15+1], 0bah
	mov byte [transrev16+1], 87h
	mov byte [transrev17+1], 0a2h
    ret

;Masked & transluscent vline
ALIGN 16
_asm_tvlineasm1:
	push ebp
	mov ebp, eax
	xor eax, eax
	inc ecx
	mov dword [transmach3c+2], ebx
	jmp short begintvline

ALIGN 16
begintvline:
	mov ebx, edx
transmach3a: shr ebx, 32
	mov bl, byte [esi+ebx]
	cmp bl, 255
	je short skiptrans1
transrev0:
transmach3c: mov al, [ebx+88888888h]
transrev1:
	mov ah, byte [edi]
transmach4: mov al, byte [eax+88888888h]   ;transluc[eax]
	mov byte [edi], al
skiptrans1:
	add edx, ebp
fixchain1t: add edi, 320
	dec ecx
	jnz short begintvline

	pop ebp
	mov eax, edx
	ret

	;eax: -------temp1-------
	;ebx: -------temp2-------
	;ecx:  dat  dat  dat  dat
	;edx: ylo2           ylo4
	;esi: yhi1           yhi2
	;edi: ---videoplc/cnt----
	;ebp: yhi3           yhi4
	;esp:

ALIGN 16
_asm_vlineasm4:
	push ebp

	mov eax, dword [ylookup + ecx*4]
	add eax, edi
	mov dword [machvline4end+2], eax
	sub edi, eax

	mov eax, dword [bufplce]
	mov ebx, dword [bufplce + 4]
	mov ecx, dword [bufplce + 8]
	mov edx, dword [bufplce + 12]
	mov dword [machvbuf1+2], ecx
	mov dword [machvbuf2+2], edx
	mov dword [machvbuf3+2], eax
	mov dword [machvbuf4+2], ebx

	mov eax, dword [palookupoffse]
	mov ebx, dword [palookupoffse + 4]
	mov ecx, dword [palookupoffse + 8]
	mov edx, dword [palookupoffse + 12]
	mov dword [machvpal1+2], ecx
	mov dword [machvpal2+2], edx
	mov dword [machvpal3+2], eax
	mov dword [machvpal4+2], ebx

		;     ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
		;edx: ³v3lo           ³v1lo           ³
		;     ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ´
		;esi: ³v2hi  v2lo             ³   v3hi³
		;     ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´
		;ebp: ³v0hi  v0lo             ³   v1hi³
		;     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÙ

	mov ebp, dword [vince]
	mov ebx, dword [vince + 4]
	mov esi, dword [vince + 8]
	mov eax, dword [vince + 12]
	and esi, 0fffffe00h
	and ebp, 0fffffe00h
machvsh9: rol eax, 88h                 ;sh
machvsh10: rol ebx, 88h                ;sh
	mov edx, eax
	mov ecx, ebx
	shr ecx, 16
	and edx, 0ffff0000h
	add edx, ecx
	and eax, 000001ffh
	and ebx, 000001ffh
	add esi, eax
	add ebp, ebx
	;
	mov eax, edx
	and eax, 0ffff0000h
	mov dword [machvinc1+2], eax
	mov dword [machvinc2+2], esi
	mov byte [machvinc3+2], dl
	mov byte [machvinc4+2], dh
	mov dword [machvinc5+2], ebp

	mov ebp, dword [vplce]
	mov ebx, dword [vplce + 4]
	mov esi, dword [vplce + 8]
	mov eax, dword [vplce + 12]
	and esi, 0fffffe00h
	and ebp, 0fffffe00h
machvsh11: rol eax, 88h                ;sh
machvsh12: rol ebx, 88h                ;sh
	mov edx, eax
	mov ecx, ebx
	shr ecx, 16
	and edx, 0ffff0000h
	add edx, ecx
	and eax, 000001ffh
	and ebx, 000001ffh
	add esi, eax
	add ebp, ebx

	mov ecx, esi
	jmp short beginvlineasm4

ALIGN 16
	nop
	nop
	nop
beginvlineasm4:
machvsh1: shr ecx, 88h          ;32-sh
	mov ebx, esi
machvsh2: and ebx, 00000088h    ;(1<<sh)-1
machvinc1: add edx, 88880000h
machvinc2: adc esi, 88888088h
machvbuf1: mov cl, byte [ecx+88888888h]
machvbuf2: mov bl, byte [ebx+88888888h]
	mov eax, ebp
machvsh3: shr eax, 88h          ;32-sh
machvpal1: mov cl, byte [ecx+88888888h]
machvpal2: mov ch, byte [ebx+88888888h]
	mov ebx, ebp
	shl ecx, 16
machvsh4: and ebx, 00000088h    ;(1<<sh)-1
machvinc3: add dl, 88h
machvbuf3: mov al, byte [eax+88888888h]
machvinc4: adc dh, 88h
machvbuf4: mov bl, byte [ebx+88888888h]
machvinc5: adc ebp, 88888088h
machvpal3: mov cl, byte [eax+88888888h]
machvpal4: mov ch, byte [ebx+88888888h]
machvline4end: mov dword [edi+88888888h], ecx
fixchain2a: add edi, 88888888h
	mov ecx, esi
	jnc short beginvlineasm4

		;     ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
		;edx: ³v3lo           ³v1lo           ³
		;     ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ´
		;esi: ³v2hi  v2lo             ³   v3hi³
		;     ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´
		;ebp: ³v0hi  v0lo             ³   v1hi³
		;     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÙ

	mov dword [vplce + 8], esi
	mov dword [vplce], ebp
		;vplc2 = (esi<<(32-sh))+(edx>>sh)
		;vplc3 = (ebp<<(32-sh))+((edx&65535)<<(16-sh))
machvsh5: shl esi, 88h     ;32-sh
	mov eax, edx
machvsh6: shl ebp, 88h     ;32-sh
	and edx, 0000ffffh
machvsh7: shr eax, 88h     ;sh
	add esi, eax
machvsh8: shl edx, 88h     ;16-sh
	add ebp, edx
	mov dword [vplce + 12], esi
	mov dword [vplce + 4], ebp

	pop ebp
	ret

	;eax: -------temp1-------
	;ebx: -------temp2-------
	;ecx: ylo4      ---------
	;edx: ylo2      ---------
	;esi: yhi1           yhi2
	;edi: ---videoplc/cnt----
	;ebp: yhi3           yhi4
	;esp:

ALIGN 16
_asm_provlineasm4:
	push ebp

	mov eax, dword [ylookup + ecx*4]
	add eax, edi
	mov dword [promachvline4end1+2], eax
	inc eax
	mov dword [promachvline4end2+2], eax
	inc eax
	mov dword [promachvline4end3+2], eax
	inc eax
	mov dword [promachvline4end4+2], eax
	sub eax, 3
	sub edi, eax

	mov eax, dword [bufplce]
	mov ebx, dword [bufplce + 4]
	mov ecx, dword [bufplce + 8]
	mov edx, dword [bufplce + 12]
	mov dword [promachvbuf1+3], ecx
	mov dword [promachvbuf2+3], edx
	mov dword [promachvbuf3+3], eax
	mov dword [promachvbuf4+3], ebx

	mov eax, dword [palookupoffse]
	mov ebx, dword [palookupoffse + 4]
	mov ecx, dword [palookupoffse + 8]
	mov edx, dword [palookupoffse + 12]
	mov dword [promachvpal1+2], ecx
	mov dword [promachvpal2+2], edx
	mov dword [promachvpal3+2], eax
	mov dword [promachvpal4+2], ebx

		;     ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
		;edx: ³v3lo           ³v1lo           ³
		;     ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ´
		;esi: ³v2hi  v2lo             ³   v3hi³
		;     ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´
		;ebp: ³v0hi  v0lo             ³   v1hi³
		;     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÙ

	mov ebp, dword [vince]
	mov ebx, dword [vince + 4]
	mov esi, dword [vince + 8]
	mov eax, dword [vince + 12]
	and esi, 0fffffe00h
	and ebp, 0fffffe00h
promachvsh9: rol eax, 88h                 ;sh
promachvsh10: rol ebx, 88h                ;sh
	mov edx, eax
	mov ecx, ebx
	shr ecx, 16
	and edx, 0ffff0000h
	add edx, ecx
	and eax, 000001ffh
	and ebx, 000001ffh
	add esi, eax
	add ebp, ebx
	;
	mov eax, edx
	and eax, 0ffff0000h
	mov dword [promachvinc1+2], eax
	mov dword [promachvinc2+2], esi
	shl edx, 16
	mov dword [promachvinc3+2], edx
	mov dword [promachvinc5+2], ebp

	mov ebp, dword [vplce]
	mov ebx, dword [vplce + 4]
	mov esi, dword [vplce + 8]
	mov eax, dword [vplce + 12]
	and esi, 0fffffe00h
	and ebp, 0fffffe00h
promachvsh11: rol eax, 88h                ;sh
promachvsh12: rol ebx, 88h                ;sh
	mov edx, eax
	mov ecx, ebx
	shr ecx, 16
	and edx, 0ffff0000h
	add edx, ecx
	and eax, 000001ffh
	and ebx, 000001ffh
	add esi, eax
	add ebp, ebx

	mov eax, esi
	mov ecx, edx
	shl ecx, 16
	jmp short probeginvlineasm4
ALIGN 16
	nop
	nop
	nop
probeginvlineasm4:
promachvsh1: shr eax, 88h          ;32-sh
	mov ebx, esi
promachvsh2: and ebx, 00000088h    ;(1<<sh)-1
promachvinc1: add edx, 88880000h
promachvinc2: adc esi, 88888088h
promachvbuf1: movzx eax, byte [eax+88888888h]
promachvbuf2: movzx ebx, byte [ebx+88888888h]
promachvpal1: mov al, byte [eax+88888888h]
promachvline4end3: mov byte [edi+88888888h], al
	mov eax, ebp
promachvsh3: shr eax, 88h          ;32-sh
promachvpal2: mov bl, byte [ebx+88888888h]
promachvline4end4: mov byte [edi+88888888h], bl
	mov ebx, ebp
promachvsh4: and ebx, 00000088h    ;(1<<sh)-1
promachvbuf3: movzx eax, byte [eax+88888888h]
promachvinc3: add ecx, 88888888h
promachvbuf4: movzx ebx, byte [ebx+88888888h]
promachvinc5: adc ebp, 88888088h
promachvpal3: mov al, byte [eax+88888888h]
promachvline4end1: mov byte [edi+88888888h], al
promachvpal4: mov bl, byte [ebx+88888888h]
promachvline4end2: mov byte [edi+88888888h], bl
profixchain2a: add edi, 88888888h
	mov eax, esi
	jnc NEAR probeginvlineasm4

		;     ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
		;edx: ³v3lo           ³v1lo           ³
		;     ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ´
		;esi: ³v2hi  v2lo             ³   v3hi³
		;     ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´
		;ebp: ³v0hi  v0lo             ³   v1hi³
		;     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÙ

	mov dword [vplce + 8], esi
	mov dword [vplce], ebp
		;vplc2 = (esi<<(32-sh))+(edx>>sh)
		;vplc3 = (ebp<<(32-sh))+((edx&65535)<<(16-sh))
promachvsh5: shl esi, 88h     ;32-sh
	mov eax, edx
promachvsh6: shl ebp, 88h     ;32-sh
	and edx, 0000ffffh
promachvsh7: shr eax, 88h     ;sh
	add esi, eax
promachvsh8: shl edx, 88h     ;16-sh
	add ebp, edx
	mov dword [vplce + 12], esi
	mov dword [vplce + 4], ebp

	pop ebp
	ret

ALIGN 16
_asm_mvlineasm4:
	push ebp

	mov eax, dword [bufplce]
	mov ebx, dword [bufplce + 4]
	mov dword [machmv1+2], eax
	mov dword [machmv4+2], ebx
	mov eax, dword [bufplce + 8]
	mov ebx, dword [bufplce + 12]
	mov dword [machmv7+2], eax
	mov dword [machmv10+2], ebx

	mov eax, dword [palookupoffse]
	mov ebx, dword [palookupoffse + 4]
	mov dword [machmv2+2], eax
	mov dword [machmv5+2], ebx
	mov eax, dword [palookupoffse + 8]
	mov ebx, dword [palookupoffse + 12]
	mov dword [machmv8+2], eax
	mov dword [machmv11+2], ebx

	mov eax, dword [vince]        ;vince
	mov ebx, dword [vince + 4]
	xor al, al
	xor bl, bl
	mov dword [machmv3+2], eax
	mov dword [machmv6+2], ebx
	mov eax, dword [vince + 8]
	mov ebx, dword [vince + 12]
	mov dword [machmv9+2], eax
	mov dword [machmv12+2], ebx

	mov ebx, ecx
	mov ecx, dword [vplce]
	mov edx, dword [vplce + 4]
	mov esi, dword [vplce + 8]
	mov ebp, dword [vplce + 12]
	mov cl, bl
	inc cl
	inc bh
	mov byte [asm3], bh
fixchain2ma: sub edi, 320

	jmp short beginmvlineasm4
ALIGN 16
beginmvlineasm4:
	dec cl
	jz NEAR endmvlineasm4
beginmvlineasm42:
	mov eax, ebp
	mov ebx, esi
machmv16: shr eax, 32
machmv15: shr ebx, 32
machmv12: add ebp, 88888888h ;vince[3]
machmv9: add esi, 88888888h ;vince[2]
machmv10: mov al, byte [eax+88888888h] ;bufplce[3]
machmv7: mov bl, byte [ebx+88888888h] ;bufplce[2]
	cmp al, 255
	adc dl, dl
	cmp bl, 255
	adc dl, dl
machmv8: mov bl, byte [ebx+88888888h] ;palookupoffs[2]
machmv11: mov bh, byte [eax+88888888h] ;palookupoffs[3]

	mov eax, edx
machmv14: shr eax, 32
	shl ebx, 16
machmv4: mov al, byte [eax+88888888h] ;bufplce[1]
	cmp al, 255
	adc dl, dl
machmv6: add edx, 88888888h ;vince[1]
machmv5: mov bh, byte [eax+88888888h] ;palookupoffs[1]

	mov eax, ecx
machmv13: shr eax, 32
machmv3: add ecx, 88888888h ;vince[0]
machmv1: mov al, byte [eax+88888888h] ;bufplce[0]
	cmp al, 255
	adc dl, dl
machmv2: mov bl, byte [eax+88888888h] ;palookupoffs[0]

	shl dl, 4
	xor eax, eax
fixchain2mb: add edi, 320
	mov al, dl
	add eax, offset mvcase0
	jmp eax       ;16 byte cases

ALIGN 16
endmvlineasm4:
	dec byte [asm3]
	jnz NEAR beginmvlineasm42

	mov dword [vplce], ecx
	mov dword [vplce + 4], edx
	mov dword [vplce + 8], esi
	mov dword [vplce + 12], ebp
	pop ebp
	ret

	;5,7,8,8,11,13,12,14,11,13,14,14,12,14,15,7
ALIGN 16
mvcase0:
	jmp beginmvlineasm4
ALIGN 16
mvcase1:
	mov byte [edi], bl
	jmp beginmvlineasm4
ALIGN 16
mvcase2:
	mov byte [edi+1], bh
	jmp beginmvlineasm4
ALIGN 16
mvcase3:
	mov word [edi], bx
	jmp beginmvlineasm4
ALIGN 16
mvcase4:
	shr ebx, 16
	mov byte [edi+2], bl
	jmp beginmvlineasm4
ALIGN 16
mvcase5:
	mov byte [edi], bl
	shr ebx, 16
	mov byte [edi+2], bl
	jmp beginmvlineasm4
ALIGN 16
	mvcase6:
	shr ebx, 8
	mov word [edi+1], bx
	jmp beginmvlineasm4
ALIGN 16
mvcase7:
	mov word [edi], bx
	shr ebx, 16
	mov byte [edi+2], bl
	jmp beginmvlineasm4
ALIGN 16
mvcase8:
	shr ebx, 16
	mov byte [edi+3], bh
	jmp beginmvlineasm4
ALIGN 16
mvcase9:
	mov byte [edi], bl
	shr ebx, 16
	mov byte [edi+3], bh
	jmp beginmvlineasm4
ALIGN 16
mvcase10:
	mov byte [edi+1], bh
	shr ebx, 16
	mov byte [edi+3], bh
	jmp beginmvlineasm4
ALIGN 16
mvcase11:
	mov word [edi], bx
	shr ebx, 16
	mov byte [edi+3], bh
	jmp beginmvlineasm4
ALIGN 16
mvcase12:
	shr ebx, 16
	mov word [edi+2], bx
	jmp beginmvlineasm4
ALIGN 16
mvcase13:
	mov byte [edi], bl
	shr ebx, 16
	mov word [edi+2], bx
	jmp beginmvlineasm4
ALIGN 16
mvcase14:
	mov byte [edi+1], bh
	shr ebx, 16
	mov word [edi+2], bx
	jmp beginmvlineasm4
ALIGN 16
mvcase15:
	mov dword [edi], ebx
	jmp beginmvlineasm4
	
ALIGN 16

_asm_setupspritevline:
	mov dword [spal+2], eax

	mov eax, esi                      ;xinc's
	shl eax, 16
	mov dword [smach1+2], eax
	mov dword [smach4+2], eax
	mov eax, esi
	sar eax, 16
	add eax, ebx                      ;watch out with ebx - it's passed
	mov dword [smach2+2], eax
	add eax, edx
	mov dword [smach5+2], eax

	mov dword [smach3+2], ecx  ;yinc's
	ret

ALIGN 16
	;eax = 0, ebx = x, ecx = cnt, edx = y, esi = yplc, edi = p
prestartsvline:
smach1: add ebx, 88888888h              ;xincshl16
	mov al, byte [esi]
smach2: adc esi, 88888888h              ;xincshr16+yalwaysinc

startsvline:
spal: mov al, [eax+88888888h]           ;palookup
	mov byte [edi], al
fixchain1s: add edi, 320

_asm_spritevline:
smach3: add edx, 88888888h              ;dayinc
	dec ecx
	ja short prestartsvline     ;jump if (no carry (add)) and (not zero (dec))!
	jz short endsvline
smach4: add ebx, 88888888h              ;xincshl16
	mov al, byte [esi]
smach5: adc esi, 88888888h              ;xincshr16+yalwaysinc+daydime
	jmp short startsvline
endsvline:
	ret

ALIGN 16
_asm_msetupspritevline:
	mov dword [mspal+2], eax

	mov eax, esi                      ;xinc's
	shl eax, 16
	mov dword [msmach1+2], eax
	mov dword [msmach4+2], eax
	mov eax, esi
	sar eax, 16
	add eax, ebx                      ;watch out with ebx - it's passed
	mov dword [msmach2+2], eax
	add eax, edx
	mov dword [msmach5+2], eax

	mov dword [msmach3+2], ecx  ;yinc's
	ret

ALIGN 16
	;eax = 0, ebx = x, ecx = cnt, edx = y, esi = yplc, edi = p
mprestartsvline:
msmach1: add ebx, 88888888h              ;xincshl16
	mov al, byte [esi]
msmach2: adc esi, 88888888h              ;xincshr16+yalwaysinc

mstartsvline:
	cmp al, 255
	je short mskipsvline
mspal: mov al, [eax+88888888h]           ;palookup
	mov byte [edi], al
mskipsvline:
mfixchain1s: add edi, 320

_asm_mspritevline:
msmach3: add edx, 88888888h              ;dayinc
	dec ecx
	ja short mprestartsvline     ;jump if (no carry (add)) and (not zero (dec))!
	jz short mendsvline
msmach4: add ebx, 88888888h              ;xincshl16
	mov al, byte [esi]
msmach5: adc esi, 88888888h              ;xincshr16+yalwaysinc+daydime
	jmp short mstartsvline
mendsvline:
	ret

ALIGN 16
_asm_tsetupspritevline:
	mov dword [tspal+2], eax

	mov eax, esi                      ;xinc's
	shl eax, 16
	mov dword [tsmach1+2], eax
	mov dword [tsmach4+2], eax
	mov eax, esi
	sar eax, 16
	add eax, ebx                      ;watch out with ebx - it's passed
	mov dword [tsmach2+2], eax
	add eax, edx
	mov dword [tsmach5+2], eax

	mov dword [tsmach3+2], ecx  ;yinc's
	ret

ALIGN 16
_asm_tspritevline:
	;eax = 0, ebx = x, ecx = cnt, edx = y, esi = yplc, edi = p
	push ebp
	mov ebp, ebx
	xor ebx, ebx
	jmp tenterspritevline
ALIGN 16
tprestartsvline:
tsmach1: add ebp, 88888888h              ;xincshl16
	mov al, byte [esi]
tsmach2: adc esi, 88888888h              ;xincshr16+yalwaysinc

tstartsvline:
	cmp al, 255
	je short tskipsvline
transrev2:
	mov bh, byte [edi]
transrev3:
tspal: mov bl, [eax+88888888h]               ;palookup
tmach4: mov al, byte [ebx+88888888h]     ;transluc
	mov byte [edi], al
tskipsvline:
tfixchain1s: add edi, 320

tenterspritevline:
tsmach3: add edx, 88888888h              ;dayinc
	dec ecx
	ja short tprestartsvline     ;jump if (no carry (add)) and (not zero (dec))!
	jz short tendsvline
tsmach4: add ebp, 88888888h              ;xincshl16
	mov al, byte [esi]
tsmach5: adc esi, 88888888h              ;xincshr16+yalwaysinc+daydime
	jmp short tstartsvline
tendsvline:
	pop ebp
	ret

ALIGN 16
_asm_msethlineshift:
	neg al
	mov byte [msh1d+2], al
	mov byte [msh2d+3], bl
	mov byte [msh3d+2], al
	mov byte [msh4d+3], bl
	mov byte [msh5d+2], al
	mov byte [msh6d+3], bl
	ret

ALIGN 16
_asm_mhline:
	;asm1 = bxinc
	;asm2 = byinc
	;asm3 = shadeoffs
	;eax = picoffs
	;ebx = bx
	;ecx = cnt
	;edx = ?
	;esi = by
	;edi = p

	mov dword [mmach1d+2], eax
	mov dword [mmach5d+2], eax
	mov dword [mmach9d+2], eax
	mov eax, [asm3]
	mov dword [mmach2d+2], eax
	mov dword [mmach2da+2], eax
	mov dword [mmach2db+2], eax
	mov dword [mmach6d+2], eax
	mov dword [mmach10d+2], eax
	mov eax, [asm1]
	mov dword [mmach3d+2], eax
	mov dword [mmach7d+2], eax
	mov eax, [asm2]
	mov dword [mmach4d+2], eax
	mov dword [mmach8d+2], eax
	jmp short _asm_mhlineskipmodify

ALIGN 16
_asm_mhlineskipmodify:

	push ebp

	xor eax, eax
	mov ebp, ebx

	test ecx, 00010000h
	jnz short mbeghline

msh1d: shr ebx, 26
msh2d: shld ebx, esi, 6
	add ebp, [asm1]
mmach9d: mov al, byte [ebx+88888888h]    ;picoffs
	add esi, [asm2]
	cmp al, 255
	je mskip5

	mmach10d: mov cl, byte [eax+88888888h]    ;shadeoffs
	mov byte [edi], cl
mskip5:
	inc edi
	sub ecx, 65536
	jc NEAR mendhline
	jmp short mbeghline

ALIGN 16
mpreprebeghline:                                            ;1st only
	mov al, cl
mmach2d: mov al, byte [eax+88888888h]    ;shadeoffs
	mov byte [edi], al

mprebeghline:
	add edi, 2
	sub ecx, 131072
	jc NEAR mendhline
mbeghline:
mmach3d: lea ebx, [ebp+88888888h]            ;bxinc
msh3d: shr ebp, 26
msh4d: shld ebp, esi, 6
mmach4d: add esi, 88888888h                  ;byinc
mmach1d: mov cl, byte [ebp+88888888h]    ;picoffs
mmach7d: lea ebp, [ebx+88888888h]            ;bxinc

msh5d: shr ebx, 26
msh6d: shld ebx, esi, 6
mmach8d: add esi, 88888888h                  ;byinc
mmach5d: mov ch, byte [ebx+88888888h]    ;picoffs

	cmp cl, 255
	je short mskip1
	cmp ch, 255
	je short mpreprebeghline

	mov al, cl                                                  ;BOTH
mmach2da: mov bl, byte [eax+88888888h]    ;shadeoffs
	mov al, ch
mmach2db: mov bh, byte [eax+88888888h]    ;shadeoffs
	mov word [edi], bx
	add edi, 2
	sub ecx, 131072
	jnc short mbeghline
	jmp mendhline
mskip1:                                                     ;2nd only
	cmp ch, 255
	je short mprebeghline

	mov al, ch
mmach6d: mov al, byte [eax+88888888h]    ;shadeoffs
	mov byte [edi+1], al
	add edi, 2
	sub ecx, 131072
	jnc short mbeghline
mendhline:

	pop ebp
	ret

ALIGN 16
_asm_tsethlineshift:
	neg al
	mov byte [tsh1d+2], al
	mov byte [tsh2d+3], bl
	mov byte [tsh3d+2], al
	mov byte [tsh4d+3], bl
	mov byte [tsh5d+2], al
	mov byte [tsh6d+3], bl
	ret

ALIGN 16
_asm_thline:
	;asm1 = bxinc
	;asm2 = byinc
	;asm3 = shadeoffs
	;eax = picoffs
	;ebx = bx
	;ecx = cnt
	;edx = ?
	;esi = by
	;edi = p

	mov dword [tmach1d+2], eax
	mov dword [tmach5d+2], eax
	mov dword [tmach9d+2], eax
	mov eax, [asm3]
	mov dword [tmach2d+2], eax
	mov dword [tmach6d+2], eax
	mov dword [tmach10d+2], eax
	mov eax, [asm1]
	mov dword [tmach3d+2], eax
	mov dword [tmach7d+2], eax
	mov eax, [asm2]
	mov dword [tmach4d+2], eax
	mov dword [tmach8d+2], eax
	jmp _asm_thlineskipmodify

ALIGN 16
_asm_thlineskipmodify:

	push ebp

	xor eax, eax
	xor edx, edx
	mov ebp, ebx

	test ecx, 00010000h
	jnz short tbeghline

tsh1d: shr ebx, 26
tsh2d: shld ebx, esi, 6
	add ebp, [asm1]
tmach9d: mov al, byte [ebx+88888888h]    ;picoffs
	add esi, [asm2]
	cmp al, 255
	je tskip5

transrev4:
tmach10d: mov dl, byte [eax+88888888h]   ;shadeoffs
transrev5:
	mov dh, byte [edi]
tmach1: mov al, byte [edx+88888888h]     ;transluc
	mov byte [edi], al
tskip5:
	inc edi
	sub ecx, 65536
	jc NEAR tendhline
	jmp short tbeghline

ALIGN 16
tprebeghline:
	add edi, 2
	sub ecx, 131072
	jc short tendhline
tbeghline:
tmach3d: lea ebx, [ebp+88888888h]            ;bxinc
tsh3d: shr ebp, 26
tsh4d: shld ebp, esi, 6
tmach4d: add esi, 88888888h                  ;byinc
tmach1d: mov cl, byte [ebp+88888888h]    ;picoffs
tmach7d: lea ebp, [ebx+88888888h]            ;bxinc

tsh5d: shr ebx, 26
tsh6d: shld ebx, esi, 6
tmach8d: add esi, 88888888h                  ;byinc
tmach5d: mov ch, byte [ebx+88888888h]    ;picoffs

	cmp cx, 0ffffh
	je short tprebeghline

	mov bx, word [edi]

	cmp cl, 255
	je short tskip1
	mov al, cl
transrev6:
tmach2d: mov dl, byte [eax+88888888h]    ;shadeoffs
transrev7:
	mov dh, bl
tmach2: mov al, byte [edx+88888888h]     ;transluc
	mov byte [edi], al

	cmp ch, 255
	je short tskip2
tskip1:
	mov al, ch
transrev8:
tmach6d: mov dl, byte [eax+88888888h]    ;shadeoffs
transrev9:
	mov dh, bh
tmach3: mov al, byte [edx+88888888h]     ;transluc
	mov byte [edi+1], al
tskip2:

	add edi, 2
	sub ecx, 131072
	jnc tbeghline
tendhline:

	pop ebp
	ret


	;eax=shiftval, ebx=palookup1, ecx=palookup2
ALIGN 16
_asm_setuptvlineasm2:
	mov byte [tran2shra+2], al
	mov byte [tran2shrb+2], al
	mov dword [tran2pala+2], ebx
	mov dword [tran2palb+2], ecx
	mov dword [tran2palc+2], ebx
	mov dword [tran2pald+2], ecx
	ret

	;Pass:   eax=vplc2, ebx=vinc1, ecx=bufplc1, edx=bufplc2, esi=vplc1, edi=p
	;        asm1=vinc2, asm2=pend
	;Return: asm1=vplc1, asm2=vplc2
ALIGN 16
_asm_tvlineasm2:
	push ebp

	mov ebp, eax

	mov dword [tran2inca+2], ebx
	mov eax, [asm1]
	mov dword [tran2incb+2], eax

	mov dword [tran2bufa+2], ecx         ;bufplc1
	mov dword [tran2bufb+2], edx         ;bufplc2

	mov eax, [asm2]
	sub edi, eax
	mov dword [tran2edia+3], eax
	mov dword [tran2edic+2], eax
	inc eax
	mov dword [tran2edie+2], eax
fixchaint2a: sub eax, 320
	mov dword [tran2edif+2], eax
	dec eax
	mov dword [tran2edib+3], eax
	mov dword [tran2edid+2], eax

	xor ecx, ecx
	xor edx, edx
	jmp short begintvline2

		;eax 0000000000  temp  temp
		;ebx 0000000000 odat2 odat1
		;ecx 0000000000000000 ndat1
		;edx 0000000000000000 ndat2
		;esi          vplc1
		;edi videoplc--------------
		;ebp          vplc2

ALIGN 16
		;LEFT ONLY
skipdraw2:
transrev10:
tran2edic: mov ah, byte [edi+88888888h]      ;getpixel
transrev11:
tran2palc: mov al, byte [ecx+88888888h]      ;palookup1
fixchaint2d: add edi, 320
tran2trac: mov bl, byte [eax+88888888h]      ;transluc
tran2edid: mov byte [edi+88888888h-320], bl  ;drawpixel
	jnc short begintvline2
	jmp endtvline2

skipdraw1:
	cmp dl, 255
	jne short skipdraw3
fixchaint2b: add edi, 320
	jc short endtvline2

begintvline2:
	mov eax, esi
tran2shra: shr eax, 88h                      ;globalshift
	mov ebx, ebp
tran2shrb: shr ebx, 88h                      ;globalshift
tran2inca: add esi, 88888888h                ;vinc1
tran2incb: add ebp, 88888888h                ;vinc2
tran2bufa: mov cl, byte [eax+88888888h]  ;bufplc1
	cmp cl, 255
tran2bufb: mov dl, byte [ebx+88888888h]  ;bufplc2
	je short skipdraw1
	cmp dl, 255
	je short skipdraw2

	;mov ax        The transluscent reverse of both!
	;mov bl, ah
	;mov ah
	;mov bh

		;BOTH
transrev12:
tran2edia: mov bx, word [edi+88888888h]      ;getpixels
transrev13:
	mov ah, bl
transrev14:
tran2pala: mov al, byte [ecx+88888888h]      ;palookup1
transrev15:
tran2palb: mov bl, byte [edx+88888888h]      ;palookup2
fixchaint2c: add edi, 320
tran2traa: mov al, byte [eax+88888888h]      ;transluc
tran2trab: mov ah, byte [ebx+88888888h]      ;transluc
tran2edib: mov word [edi+88888888h-320], ax  ;drawpixels
	jnc short begintvline2
	jmp short endtvline2

	;RIGHT ONLY
skipdraw3:
transrev16:
tran2edie: mov ah, byte [edi+88888889h]      ;getpixel
transrev17:
tran2pald: mov al, byte [edx+88888888h]      ;palookup2
fixchaint2e: add edi, 320
tran2trad: mov bl, byte [eax+88888888h]      ;transluc
tran2edif: mov byte [edi+88888889h-320], bl  ;drawpixel
	jnc short begintvline2

endtvline2:
	mov [asm1], esi
	mov [asm2], ebp

	pop ebp
	ret


BITSOFPRECISION equ 3
BITSOFPRECISIONPOW equ 8

;Double-texture mapping with palette lookup
;eax:  ylo1------------|----dat|----dat
;ebx:  ylo2--------------------|----cnt
;ecx:  000000000000000000000000|---temp
;edx:  xhi1-xlo1---------------|---yhi1
;esi:  xhi2-xlo2---------------|---yhi2
;edi:  ------------------------videopos
;ebp:  ----------------------------temp

ALIGN 16
setupslopevlin2:
	mov dword [slop3+2], edx ;ptr
	mov dword [slop7+2], edx ;ptr
	mov dword [slop4+2], esi ;tptr
	mov dword [slop8+2], esi ;tptr
	mov byte [slop2+2], ah   ;ybits
	mov byte [slop6+2], ah   ;ybits
	mov dword [slop9+2], edi ;pinc

	mov edx, 1
	mov cl, al
	add cl, ah
	shl edx, cl
	dec edx
	mov cl, ah
	ror edx, cl

	mov dword [slop1+2], edx   ;ybits...xbits
	mov dword [slop5+2], edx   ;ybits...xbits

	ret

ALIGN 16
_asm_slopevlin2:
	push ebp
	xor ecx, ecx

slopevlin2begin:
	mov ebp, edx
slop1: and ebp, 88000088h                ;ybits...xbits
slop2: rol ebp, 6                        ;ybits
	add eax, [asm1]                        ;xinc1<<xbits
	adc edx, [asm2]                        ;(yinc1&0xffffff00)+(xinc1>>(32-xbits))
slop3: mov cl, byte [ebp+88888888h]  ;bufplc

	mov ebp, esi
slop4: mov al, byte [ecx+88888888h]  ;paloffs
slop5: and ebp, 88000088h                ;ybits...xbits
slop6: rol ebp, 6                        ;ybits
	add ebx, [asm3]                        ;xinc2<<xbits
slop7: mov cl, byte [ebp+88888888h]  ;bufplc
	adc esi, [asm4]                        ;(yinc2&0xffffff00)+(xinc2>>(32-xbits))
slop8: mov ah, byte [ecx+88888888h]  ;paloffs

	dec bl
	mov word [edi], ax
slop9: lea edi, [edi+88888888h]          ;pinc
	jnz short slopevlin2begin

	pop ebp
	mov eax, edi
	ret


ALIGN 16
_asm_setupslopevlin:
	mov dword [slopmach3+3], ebx    ;ptr
	mov dword [slopmach5+2], ecx    ;pinc
	neg ecx
	mov dword [slopmach6+2], ecx    ;-pinc

	mov edx, 1
	mov cl, al
	shl edx, cl
	dec edx
	mov cl, ah
	shl edx, cl
	mov dword [slopmach7+2], edx

	neg ah
	mov byte [slopmach2+2], ah

	sub ah, al
	mov byte [slopmach1+2], ah

	fild dword [asm1]
	fstp dword [asm2]
	ret

ALIGN 16
_asm_slopevlin:
	mov [ebpbak], ebp		; Added [] AH
	mov [espbak], esp         	; Added [] AH

	sub ecx, esp
	mov dword [slopmach4+3], ecx

	fild dword [asm3]
slopmach6: lea ebp, [eax+88888888h]
	fadd dword [asm2]

	mov [asm1], ebx			; Added [] AH
	shl ebx, 3

	mov eax, [globalx3]
	mov ecx, [globaly3]
	imul eax, ebx
	imul ecx, ebx
	add esi, eax
	add edi, ecx

	mov ebx, edx
	jmp short bigslopeloop
ALIGN 16
bigslopeloop:
	fst dword [fpuasm]

	mov eax, [fpuasm]
	add eax, eax
	sbb edx, edx
	mov ecx, eax
	shr ecx, 24
	and eax, 00ffe000h
	shr eax, 11
	sub cl, 2
	mov eax, dword [reciptable + eax]
	shr eax, cl
	xor eax, edx
	mov edx, [asm1]
	mov ecx, [globalx3]
	mov [asm1], eax			; Added [] AH
	sub eax, edx
	mov edx, [globaly3]
	imul ecx, eax
	imul eax, edx

	fadd dword [asm2]

	cmp ebx, BITSOFPRECISIONPOW
	mov [asm4], ebx			; Added [] AH
	mov cl, bl
	jl short slopeskipmin
	mov cl, BITSOFPRECISIONPOW
slopeskipmin:

;eax: yinc.............
;ebx:   0   0   0   ?
;ecx: xinc......... cnt
;edx:         ?
;esi: xplc.............
;edi: yplc.............
;ebp:     videopos

	mov ebx, esi
	mov edx, edi

beginnerslopeloop:
slopmach1: shr ebx, 20
	add esi, ecx
slopmach2: shr edx, 26
slopmach7: and ebx, 88888888h
	add edi, eax
slopmach5: add ebp, 88888888h                   ;pinc
slopmach3: mov dl, byte [ebx+edx+88888888h] ;ptr
slopmach4: mov ebx, dword [esp+88888888h]
slopmach41: 	sub esp, 4
slopmach42: 	dec cl
slopmach43: 	mov al, byte [ebx+edx] ;tptr
slopmach44: 	mov ebx, esi
slopmach45: 	mov [ebp], al
slopmach46: 	mov edx, edi
slopmach47: 	jnz short beginnerslopeloop

slopmach48: 	mov ebx, [asm4]
slopmach49: 	sub ebx, BITSOFPRECISIONPOW
slopmach4a: 	jg NEAR bigslopeloop

slopmach4b: 	ffree st0

slopmach4c: 	mov esp, [espbak]
slopmach4d: 	mov ebp, [ebpbak]
	ret


ALIGN 16
_asm_setuprhlineasm4:
	mov dword [rmach1a+2], eax
	mov dword [rmach1b+2], eax
	mov dword [rmach1c+2], eax
	mov dword [rmach1d+2], eax
	mov dword [rmach1e+2], eax

	mov dword [rmach2a+2], ebx
	mov dword [rmach2b+2], ebx
	mov dword [rmach2c+2], ebx
	mov dword [rmach2d+2], ebx
	mov dword [rmach2e+2], ebx

	mov dword [rmach3a+2], ecx
	mov dword [rmach3b+2], ecx
	mov dword [rmach3c+2], ecx
	mov dword [rmach3d+2], ecx
	mov dword [rmach3e+2], ecx

	mov dword [rmach4a+2], edx
	mov dword [rmach4b+2], edx
	mov dword [rmach4c+2], edx
	mov dword [rmach4d+2], edx
	mov dword [rmach4e+2], edx

	mov dword [rmach5a+2], esi
	mov dword [rmach5b+2], esi
	mov dword [rmach5c+2], esi
	mov dword [rmach5d+2], esi
	mov dword [rmach5e+2], esi
	ret

	;Non power of 2, non masking, with palookup method #1 (6 clock cycles)
	;eax: dat dat dat dat
	;ebx:          bufplc
	;ecx:  0          dat
	;edx:  xlo
	;esi:  ylo
	;edi:  videopos/cnt
	;ebp:  tempvar
	;esp:
ALIGN 16
_asm_rhlineasm4:
	push ebp

	cmp eax, 0
	jle NEAR endrhline

	lea ebp, [edi-4]
	sub ebp, eax
	mov dword [rmach6a+2], ebp
	add ebp, 3
	mov dword [rmach6b+2], ebp
	mov edi, eax
	test edi, 3
	jz short begrhline
	jmp short startrhline1

ALIGN 16
startrhline1:
	mov cl, byte [ebx]                      ;bufplc
rmach1e: sub edx, 88888888h                    ;xlo
	sbb ebp, ebp
rmach2e: sub esi, 88888888h                    ;ylo
rmach3e: sbb ebx, 88888888h                    ;xhi*tilesizy + yhi+ycarry
rmach4e: mov al, byte [ecx+88888888h]      ;palookup
rmach5e: and ebp, 88888888h                    ;tilesizy
rmach6b: mov byte [edi+88888888h], al      ;vidcntoffs
	sub ebx, ebp
	dec edi
	test edi, 3
	jnz short startrhline1
	test edi, edi
	jz NEAR endrhline

begrhline:
	mov cl, byte [ebx]                      ;bufplc
rmach1a: sub edx, 88888888h                    ;xlo
	sbb ebp, ebp
rmach2a: sub esi, 88888888h                    ;ylo
rmach3a: sbb ebx, 88888888h                    ;xhi*tilesizy + yhi+ycarry
rmach5a: and ebp, 88888888h                    ;tilesizy
	sub ebx, ebp

rmach1b: sub edx, 88888888h                    ;xlo
	sbb ebp, ebp
rmach4a: mov ah, byte [ecx+88888888h]      ;palookup
	mov cl, byte [ebx]                      ;bufplc
rmach2b: sub esi, 88888888h                    ;ylo
rmach3b: sbb ebx, 88888888h                    ;xhi*tilesizy + yhi+ycarry
rmach5b: and ebp, 88888888h                    ;tilesizy
rmach4b: mov al, byte [ecx+88888888h]      ;palookup
	sub ebx, ebp

	shl eax, 16

	mov cl, byte [ebx]                      ;bufplc
rmach1c: sub edx, 88888888h                    ;xlo
	sbb ebp, ebp
rmach2c: sub esi, 88888888h                    ;ylo
rmach3c: sbb ebx, 88888888h                    ;xhi*tilesizy + yhi+ycarry
rmach5c: and ebp, 88888888h                    ;tilesizy
	sub ebx, ebp

rmach1d: sub edx, 88888888h                    ;xlo
	sbb ebp, ebp
rmach4c: mov ah, byte [ecx+88888888h]      ;palookup
	mov cl, byte [ebx]                      ;bufplc
rmach2d: sub esi, 88888888h                    ;ylo
rmach3d: sbb ebx, 88888888h                    ;xhi*tilesizy + yhi+ycarry
rmach5d: and ebp, 88888888h                    ;tilesizy
rmach4d: mov al, byte [ecx+88888888h]      ;palookup
	sub ebx, ebp

rmach6a: mov dword [edi+88888888h], eax    ;vidcntoffs
	sub edi, 4
	jnz NEAR begrhline
endrhline:
	pop ebp
	ret

ALIGN 16
_asm_setuprmhlineasm4:
	mov dword [rmmach1+2], eax
	mov dword [rmmach2+2], ebx
	mov dword [rmmach3+2], ecx
	mov dword [rmmach4+2], edx
	mov dword [rmmach5+2], esi
	ret

ALIGN 16
_asm_rmhlineasm4:
	push ebp

	cmp eax, 0
	jle short endrmhline

	lea ebp, [edi-1]
	sub ebp, eax
	mov dword [rmmach6+2], ebp
	mov edi, eax
	jmp short begrmhline

ALIGN 16
begrmhline:
	mov cl, byte [ebx]                      ;bufplc
rmmach1: sub edx, 88888888h                    ;xlo
	sbb ebp, ebp
rmmach2: sub esi, 88888888h                    ;ylo
rmmach3: sbb ebx, 88888888h                    ;xhi*tilesizy + yhi+ycarry
rmmach5: and ebp, 88888888h                    ;tilesizy
	cmp cl, 255
	je short rmskip
rmmach4: mov al, byte [ecx+88888888h]      ;palookup
rmmach6: mov byte [edi+88888888h], al      ;vidcntoffs
rmskip:
	sub ebx, ebp
	dec edi
	jnz short begrmhline
endrmhline:
	pop ebp
	ret

ALIGN 16
_asm_setupqrhlineasm4:
	mov dword [qrmach2e+2], ebx
	mov dword [qrmach3e+2], ecx
	xor edi, edi
	sub edi, ecx
	mov dword [qrmach7a+2], edi
	mov dword [qrmach7b+2], edi

	add ebx, ebx
	adc ecx, ecx
	mov dword [qrmach2a+2], ebx
	mov dword [qrmach2b+2], ebx
	mov dword [qrmach3a+2], ecx
	mov dword [qrmach3b+2], ecx

	mov dword [qrmach4a+2], edx
	mov dword [qrmach4b+2], edx
	mov dword [qrmach4c+2], edx
	mov dword [qrmach4d+2], edx
	mov dword [qrmach4e+2], edx
	ret

	;Non power of 2, non masking, with palookup method (FASTER BUT NO SBB'S)
	;eax: dat dat dat dat
	;ebx:          bufplc
	;ecx:  0          dat
	;edx:  0          dat
	;esi:  ylo
	;edi:  videopos/cnt
	;ebp:  ?
	;esp:
ALIGN 16
;4 pixels in 9 cycles!  2.25 cycles/pixel
_asm_qrhlineasm4:
	push ebp

	cmp eax, 0
	jle NEAR endqrhline

	mov ebp, eax
	test ebp, 3
	jz short skipqrhline1
	jmp short startqrhline1

ALIGN 16
startqrhline1:
	mov cl, byte [ebx]                      ;bufplc
	dec edi
qrmach2e: sub esi, 88888888h                   ;ylo
	dec ebp
qrmach3e: sbb ebx, 88888888h                   ;xhi*tilesizy + yhi+ycarry
qrmach4e: mov al, byte [ecx+88888888h]     ;palookup
	mov byte [edi], al                      ;vidcntoffs
	test ebp, 3
	jnz short startqrhline1
	test ebp, ebp
	jz short endqrhline

skipqrhline1:
	mov cl, byte [ebx]                      ;bufplc
	jmp short begqrhline
ALIGN 16
begqrhline:
qrmach7a: mov dl, byte [ebx+88888888h]     ;bufplc
qrmach2a: sub esi, 88888888h                   ;ylo
qrmach3a: sbb ebx, 88888888h                   ;xhi*tilesizy + yhi+ycarry
qrmach4a: mov ah, byte [ecx+88888888h]     ;palookup
qrmach4b: mov al, byte [edx+88888888h]     ;palookup
	sub edi, 4
	shl eax, 16
	mov cl, byte [ebx]                      ;bufplc
qrmach7b: mov dl, byte [ebx+88888888h]     ;bufplc
qrmach2b: sub esi, 88888888h                   ;ylo
qrmach3b: sbb ebx, 88888888h                   ;xhi*tilesizy + yhi+ycarry
qrmach4c: mov ah, byte [ecx+88888888h]     ;palookup
qrmach4d: mov al, byte [edx+88888888h]     ;palookup
	mov cl, byte [ebx]                      ;bufplc
	mov dword [edi], eax
	sub ebp, 4
	jnz short begqrhline

endqrhline:
	pop ebp
	ret

_asm_setupdrawslab:
	mov dword [voxbpl1+2], eax
	mov dword [voxbpl2+2], eax
	mov dword [voxbpl3+2], eax
	mov dword [voxbpl4+2], eax
	mov dword [voxbpl5+2], eax
	mov dword [voxbpl6+2], eax
	mov dword [voxbpl7+2], eax
	mov dword [voxbpl8+2], eax

	mov dword [voxpal1+2], ebx
	mov dword [voxpal2+2], ebx
	mov dword [voxpal3+2], ebx
	mov dword [voxpal4+2], ebx
	mov dword [voxpal5+2], ebx
	mov dword [voxpal6+2], ebx
	mov dword [voxpal7+2], ebx
	mov dword [voxpal8+2], ebx
	ret

ALIGN 16
_asm_drawslab:
	push ebp
	cmp eax, 2
	je voxbegdraw2
	ja voxskip2
	xor eax, eax
voxbegdraw1:
	mov ebp, ebx
	shr ebp, 16
	add ebx, edx
	dec ecx
	mov al, byte [esi+ebp]
voxpal1: mov al, byte [eax+88888888h]
	mov byte [edi], al
voxbpl1: lea edi, [edi+88888888h]
	jnz voxbegdraw1
	pop ebp
	ret

voxbegdraw2:
	mov ebp, ebx
	shr ebp, 16
	add ebx, edx
	xor eax, eax
	dec ecx
	mov al, byte [esi+ebp]
voxpal2: mov al, byte [eax+88888888h]
	mov ah, al
	mov word [edi], ax
voxbpl2: lea edi, [edi+88888888h]
	jnz voxbegdraw2
	pop ebp
	ret

voxskip2:
	cmp eax, 4
	jne voxskip4
	xor eax, eax
voxbegdraw4:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal3: mov al, byte [eax+88888888h]
	mov ah, al
	shl eax, 8
	mov al, ah
	shl eax, 8
	mov al, ah
	mov dword [edi], eax
voxbpl3: add edi, 88888888h
	dec ecx
	jnz voxbegdraw4
	pop ebp
	ret

voxskip4:
	add eax, edi

	test edi, 1
	jz voxskipslab1
	cmp edi, eax
	je voxskipslab1

	push eax
	push ebx
	push ecx
	push edi
voxbegslab1:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal4: mov al, byte [eax+88888888h]
	mov byte [edi], al
voxbpl4: add edi, 88888888h
	dec ecx
	jnz voxbegslab1
	pop edi
	pop ecx
	pop ebx
	pop eax
	inc edi

voxskipslab1:
	push eax
	test edi, 2
	jz voxskipslab2
	dec eax
	cmp edi, eax
	jge voxskipslab2

	push ebx
	push ecx
	push edi
voxbegslab2:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal5: mov al, byte [eax+88888888h]
	mov ah, al
	mov word [edi], ax
voxbpl5: add edi, 88888888h
	dec ecx
	jnz voxbegslab2
	pop edi
	pop ecx
	pop ebx
	add edi, 2

voxskipslab2:
	mov eax, [esp]

	sub eax, 3
	cmp edi, eax
	jge voxskipslab3

voxprebegslab3:
	push ebx
	push ecx
	push edi
voxbegslab3:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal6: mov al, byte [eax+88888888h]
	mov ah, al
	shl eax, 8
	mov al, ah
	shl eax, 8
	mov al, ah
	mov dword [edi], eax
voxbpl6: add edi, 88888888h
	dec ecx
	jnz voxbegslab3
	pop edi
	pop ecx
	pop ebx
	add edi, 4

	mov eax, [esp]

	sub eax, 3
	cmp edi, eax
	jl voxprebegslab3

voxskipslab3:
	mov eax, [esp]

	dec eax
	cmp edi, eax
	jge voxskipslab4

	push ebx
	push ecx
	push edi
voxbegslab4:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal7: mov al, byte [eax+88888888h]
	mov ah, al
	mov word [edi], ax
voxbpl7: add edi, 88888888h
	dec ecx
	jnz voxbegslab4
	pop edi
	pop ecx
	pop ebx
	add edi, 2

voxskipslab4:
	pop eax

	cmp edi, eax
	je voxskipslab5

voxbegslab5:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal8: mov al, byte [eax+88888888h]
	mov byte [edi], al
voxbpl8: add edi, 88888888h
	dec ecx
	jnz voxbegslab5

voxskipslab5:
	pop ebp
	ret

;modify: loinc
;eax: |  dat   |  dat   |   dat  |   dat  |
;ebx: |      loplc1                       |
;ecx: |      loplc2     |  cnthi |  cntlo |
;edx: |--------|--------|--------| hiplc1 |
;esi: |--------|--------|--------| hiplc2 |
;edi: |--------|--------|--------| vidplc |
;ebp: |--------|--------|--------|  hiinc |

_asm_stretchhline:
	push ebp

	mov eax, ebx
	shl ebx, 16
	sar eax, 16
	and ecx, 0000ffffh
	or ecx, ebx

	add esi, eax
	mov eax, edx
	mov edx, esi

	mov ebp, eax
	shl eax, 16
	sar ebp, 16

	add ecx, eax
	adc esi, ebp

	add eax, eax
	adc ebp, ebp
	mov dword [loinc1+2], eax
	mov dword [loinc2+2], eax
	mov dword [loinc3+2], eax
	mov dword [loinc4+2], eax

	inc ch

	jmp begloop

begloop:
	mov al, [edx]
loinc1: sub ebx, 88888888h
	sbb edx, ebp
	mov ah, [esi]
loinc2: sub ecx, 88888888h
	sbb esi, ebp
	sub edi, 4
	shl eax, 16
loinc3: sub ebx, 88888888h
	mov al, [edx]
	sbb edx, ebp
	mov ah, [esi]
loinc4: sub ecx, 88888888h
	sbb esi, ebp
	mov [edi], eax
	dec cl
	jnz begloop
	dec ch
	jnz begloop

	pop ebp
	ret

_asm_mmxoverlay:
	pushfd                 ;Check if CPUID is available
	pop eax
	mov ebx, eax
	xor eax, 00200000h
	push eax
	popfd
	pushfd
	pop eax
	cmp eax, ebx
	je pentium
	xor eax, eax
	dw 0a20fh
	test eax, eax
	jz pentium
	mov eax, 1
	dw 0a20fh
	and eax, 00000f00h
	test edx, 00800000h    ;Check if MMX is available
	jz nommx
	cmp eax, 00000600h     ;Check if P6 Family or not
	jae pentiumii
	jmp pentiummmx
nommx:
	cmp eax, 00000600h     ;Check if P6 Family or not
	jae pentiumpro
pentium:
	ret

;ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
;³                    PENTIUM II Overlays                       ³
;ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
pentiumii:
		;Hline overlay (MMX doens't help)
	mov byte [_asm_sethlinesizes], 0xe9
	mov dword [_asm_sethlinesizes+1], (offset _asm_prosethlinesizes)-(offset _asm_sethlinesizes)-5
	mov byte [_asm_setpalookupaddress], 0xe9
	mov dword [_asm_setpalookupaddress+1], (offset _asm_prosetpalookupaddress)-(offset _asm_setpalookupaddress)-5
	mov byte [_asm_setuphlineasm4], 0xc3  ;ret (no code required)
	mov byte [_asm_hlineasm4], 0xe9
	mov dword [_asm_hlineasm4+1], (offset _asm_prohlineasm4)-(offset _asm_hlineasm4)-5

		;Vline overlay
	mov byte [_asm_setupvlineasm], 0xe9
	mov dword [_asm_setupvlineasm+1], (offset _asm_prosetupvlineasm)-(offset _asm_setupvlineasm)-5
	mov byte [_asm_vlineasm4], 0xe9
	mov dword [_asm_vlineasm4+1], (offset _asm_provlineasm4)-(offset _asm_vlineasm4)-5

	ret

;ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
;³                    PENTIUM MMX Overlays                      ³
;ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
pentiummmx:
	ret

;ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
;³                    PENTIUM PRO Overlays                      ³
;ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
pentiumpro:
		;Hline overlay (MMX doens't help)
	mov byte [_asm_sethlinesizes], 0xe9
	mov dword [_asm_sethlinesizes+1], (offset _asm_prosethlinesizes)-(offset _asm_sethlinesizes)-5
	mov byte [_asm_setpalookupaddress], 0xe9
	mov dword [_asm_setpalookupaddress+1], (offset _asm_prosetpalookupaddress)-(offset _asm_setpalookupaddress)-5
	mov byte [_asm_setuphlineasm4], 0xc3  ;ret (no code required)
	mov byte [_asm_hlineasm4], 0xe9
	mov dword [_asm_hlineasm4+1], (offset _asm_prohlineasm4)-(offset _asm_hlineasm4)-5

		;Vline overlay
	mov byte [_asm_setupvlineasm], 0xe9
	mov dword [_asm_setupvlineasm+1], (offset _asm_prosetupvlineasm)-(offset _asm_setupvlineasm)-5
	mov byte [_asm_vlineasm4], 0xe9
	mov dword [_asm_vlineasm4+1], (offset _asm_provlineasm4)-(offset _asm_vlineasm4)-5

	ret

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
	mov [fpuasm], eax
	fild dword [fpuasm]
	add eax, eax
	fstp dword [fpuasm]
	sbb ebx, ebx
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

END

; ************************
; **   End Code Block   **
; ************************


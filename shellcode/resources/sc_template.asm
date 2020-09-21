; Filename: hello-world_JmpCallPop.asm
; Author: Cameron, James
; Purpose: Demonstrate "hello wolrd" shellcode using jmp call pop technique
; Tested On: Linux ubuntu 3.11.0-15-generic #25~precise1-Ubuntu SMP Thu Jan 30 17:42:40 UTC 2014 i686 i686 i386 GNU/Linux
;            Ubuntu 12.04.4 LTS



section .text

global _start

_start:

	jmp short call_shellcode

shellcode:
	; shellcode goes here

call_shellcode:
	call shellcode

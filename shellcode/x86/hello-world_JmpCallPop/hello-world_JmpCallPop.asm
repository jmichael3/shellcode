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

	;        ssize_t write(int fd, const void *buf, size_t count);
	;        #define __NR_write                4


	xor eax, eax        ; set eax register = 0
	xor ebx, ebx        ; set ebx register = 0
	xor ecx, ecx        ; set ecx register = 0
	xor edx, edx        ; set edx register = 0
	mov al, 4           ; move write syscall into eax (lower byte to avoid null char)
	inc ebx             ; set fd equal to 1 (stdout)
	pop ecx             ; pop msg to be printed into ecx
	mov dl, 16          ; length of message to be printed
	int 0x80            ; execute syscall

	
	;        void _exit(int status);
	;        #define __NR_exit                 1
	
	xor eax, eax        ; clean out eax register
	mov al, 1           ; set al equal to 1 (exit syscall)
	dec ebx             ; set return status to 0
	int 0x80            ; execute syscall


call_shellcode:
	call shellcode
	msg: db "Hello World!!!", 0x0a, 0

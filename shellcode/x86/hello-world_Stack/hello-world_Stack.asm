; Filename: hello-world_Stack.asm
; Author: Cameron, James
; Purpose: Demonstrate "hello wolrd" shellcode using Stack technique
; Tested On: Linux ubuntu 3.11.0-15-generic #25~precise1-Ubuntu SMP Thu Jan 30 17:42:40 UTC 2014 i686 i686 i386 GNU/Linux
;            Ubuntu 12.04.4 LTS



section .text

global _start

_start:

        ;        ssize_t write(int fd, const void *buf, size_t count);
        ;        #define __NR_write                4


	xor eax, eax       ; clean out eax register
	xor ebx, ebx       ; clean out ebx register
	xor ecx, ecx       ; clean out ecx register
	xor edx, edx       ; clean out edx register

	                   ; push 'Hello World!!!\nb' onto the stack in reverse order
	push 0x620a2121    ; ba!! ( a replaced with new line 0a )
	mov byte [esp + 3], al ; replace b with null byte (terminate string)
	push 0x21646c72    ; !dlr
	push 0x6f57206f    ; oW o
	push 0x6c6c6548    ; lleH

	mov ecx, esp       ; mov hello world string into ecx
	mov dl, 16         ; mov length of string into edx
	mov al, 4          ; mov write syscall (4) into eax
	inc bl             ; set ebx to 1 for stdout
	int 0x80           ; execute syscall


        ;        void _exit(int status);
        ;        #define __NR_exit                 1


	xor eax, eax       ; clean out eax register
	mov al, 1          ; set eax to exit syscall (1)
	dec bl             ; set return value to 0
	int 0x80           ; execute syscall


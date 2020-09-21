/*

// Author: Cameron, James
// Compile With: gcc test.c -fno-stack-protector -z execstack
// Tested On: Linux ubuntu 3.11.0-15-generic #25~precise1-Ubuntu SMP Thu Jan 30 17:42:40 UTC 2014 i686 i686 i386 GNU/Linux
//            Ubuntu 12.04.4 LTS

slae@ubuntu:~/Documents/github/shellcode/hello-world_Stack$ objdump -M intel -d ./hello-world_Stack

./hello-world_Stack:     file format elf32-i386


Disassembly of section .text:

08048060 <_start>:
 8048060:       31 c0                   xor    eax,eax
 8048062:       31 db                   xor    ebx,ebx
 8048064:       31 c9                   xor    ecx,ecx
 8048066:       31 d2                   xor    edx,edx
 8048068:       68 21 21 0a 62          push   0x620a2121
 804806d:       88 44 24 03             mov    BYTE PTR [esp+0x3],al
 8048071:       68 72 6c 64 21          push   0x21646c72
 8048076:       68 6f 20 57 6f          push   0x6f57206f
 804807b:       68 48 65 6c 6c          push   0x6c6c6548
 8048080:       89 e1                   mov    ecx,esp
 8048082:       b2 10                   mov    dl,0x10
 8048084:       b0 04                   mov    al,0x4
 8048086:       fe c3                   inc    bl
 8048088:       cd 80                   int    0x80
 804808a:       31 c0                   xor    eax,eax
 804808c:       b0 01                   mov    al,0x1
 804808e:       fe cb                   dec    bl
 8048090:       cd 80                   int    0x80

*/

#include <stdio.h>
#include <string.h>

unsigned char shellcode[] = \
"\x31\xc0\x31\xdb\x31\xc9\x31\xd2\x68\x21\x21\x0a\x62\x88\x44\x24\x03\x68\x72\x6c\x64\x21\x68\x6f\x20\x57\x6f\x68\x48\x65\x6c\x6c\x89\xe1\xb2\x10\xb0\x04\xfe\xc3\xcd\x80\x31\xc0\xb0\x01\xfe\xcb\xcd\x80";

int main(){

	printf("[*]Executing shellcode of length: %d\n", strlen(shellcode));
	int (*run)() = (int(*)())shellcode;
	run();
	return 0;

}

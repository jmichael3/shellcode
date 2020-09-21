/*

// Author: Cameron, James
// Compile With: gcc test.c -fno-stack-protector -z execstack
// Tested On: Linux ubuntu 3.11.0-15-generic #25~precise1-Ubuntu SMP Thu Jan 30 17:42:40 UTC 2014 i686 i686 i386 GNU/Linux
//            Ubuntu 12.04.4 LTS

slae@ubuntu:~/Documents/github/shellcode/hello-world_JmpCallPop$ objdump -d hello-world_JmpCallPop -M intel

hello-world_JmpCallPop:     file format elf32-i386

Disassembly of section .text:

08048060 <_start>:
 8048060:       eb 17                   jmp    8048079 <call_shellcode>

08048062 <shellcode>:
 8048062:       31 c0                   xor    eax,eax
 8048064:       31 db                   xor    ebx,ebx
 8048066:       31 c9                   xor    ecx,ecx
 8048068:       31 d2                   xor    edx,edx
 804806a:       b0 04                   mov    al,0x4
 804806c:       43                      inc    ebx
 804806d:       59                      pop    ecx
 804806e:       b2 10                   mov    dl,0x10
 8048070:       cd 80                   int    0x80
 8048072:       31 c0                   xor    eax,eax
 8048074:       b0 01                   mov    al,0x1
 8048076:       4b                      dec    ebx
 8048077:       cd 80                   int    0x80

08048079 <call_shellcode>:
 8048079:       e8 e4 ff ff ff          call   8048062 <shellcode>

0804807e <msg>:
 804807e:       48                      dec    eax
 804807f:       65                      gs
 8048080:       6c                      ins    BYTE PTR es:[edi],dx
 8048081:       6c                      ins    BYTE PTR es:[edi],dx
 8048082:       6f                      outs   dx,DWORD PTR ds:[esi]
 8048083:       20 57 6f                and    BYTE PTR [edi+0x6f],dl
 8048086:       72 6c                   jb     80480f4 <_end+0x64>
 8048088:       64 21 21                and    DWORD PTR fs:[ecx],esp
 804808b:       21 0a                   and    DWORD PTR [edx],ecx
        ...

*/

#include <stdio.h>
#include <string.h>

unsigned char shellcode[] = \
"\xeb\x17\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x04\x43\x59\xb2\x10\xcd\x80\x31\xc0\xb0\x01\x4b\xcd\x80\xe8\xe4\xff\xff\xff\x48\x65\x6c\x6c\x6f\x20\x57\x6f\x72\x6c\x64\x21\x21\x21\x0a";

int main(){

	printf("[*]Executing shellcode of length: %d\n", strlen(shellcode));
	int (*run)() = (int(*)())shellcode;
	run();
	return 0;

}

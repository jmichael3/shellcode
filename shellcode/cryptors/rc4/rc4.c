// Author: Cameron, James
// Reference: https://sites.math.washington.edu/~nichifor/310_2008_Spring/Pres_RC4%20Encryption.pdf
// Compile With: gcc test.c -fno-stack-protector -z execstack
// Tested On: Linux ubuntu 3.11.0-15-generic #25~precise1-Ubuntu SMP Thu Jan 30 17:42:40 UTC 2014 i686 i686 i386 GNU/Linux
//            Ubuntu 12.04.4 LTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int xor(unsigned char* keyStreamPtr, unsigned char* shellcode, unsigned char* ciphertext){

	int i = 0;
	for (i; i < strlen(shellcode); i++)
		{
			ciphertext[i] = (keyStreamPtr[i] ^ shellcode[i]);
		}
	return 0;

}

int ksa(unsigned char* sPtr, unsigned char* key){

	int i = 0;
	int j = 0;
	unsigned char si;
	unsigned char sj;
	unsigned char K[256];

	// initialize s and k boxes
	for (i; i < 256; i++)
		{
			sPtr[i] = i;
			K[i] = key[i % strlen(key)];
		}
	i = 0;

	// main part of ksa algorithm
	for (i; i < 256; i++)
		{
			j = (j + sPtr[i] + K[i % strlen(key)]) % 256;
			si = sPtr[i];
			sj = sPtr[j];
			sPtr[i] = sj;
			sPtr[j] = si;
		}

	return 0;

}

int prga(unsigned char* sPtr, int c, unsigned char* keyStreamPtr){
	int i = 0;
	int j = 0;
	int generatingOutput = 0;
	unsigned char si;
	unsigned char sj;

	// prga
	for (generatingOutput; i < c; generatingOutput++)
		{
			i = (i + 1) % 256;
			j = (j + sPtr[i]) % 256;
			si = sPtr[i];
			sj = sPtr[j];
			sPtr[i] = sj;
			sPtr[j] = si;
			keyStreamPtr[generatingOutput] = sPtr[(sPtr[i] + sPtr[j]) % 256];
		}

	return 0;

}

int main(void){

	unsigned char* key = "Secret";
	unsigned char* shellcode = \
"\xef\xc3\x5a\xc5\xd\x73\x4a\x90\x70\xa0\x80\x2e\xaf\xc2\xb\x82\xff\x91\xe5\xf5\xe9\x4e\x4b\xba\x9d\x21\xfd\xa0\xb7\x89\xb8\xe2\x9f\x19\x2b\x5c\x41\x42\x40\x42\xa1\xcc\x8b\x30\x9c"; // hello word shellcode encrypted with rc4 using key: Secret
// hello world jmp call pop
// "\xeb\x17\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x04\x43\x59\xb2\x10\xcd\x80\x31\xc0\xb0\x01\x4b\xcd\x80\xe8\xe4\xff\xff\xff\x48\x65\x6c\x6c\x6f\x20\x57\x6f\x72\x6c\x64\x21\x21\x21\x0a";

	unsigned char sBox[256];
	unsigned char keyStream[strlen(key)];
	unsigned char ciphertext[strlen(shellcode)];

	unsigned char* sPtr = sBox;
	unsigned char* keyStreamPtr = keyStream;
	unsigned char* ciphertextPtr = ciphertext;

	ksa(sPtr, key);
	prga(sPtr, strlen(shellcode), keyStreamPtr);
	xor(keyStreamPtr, shellcode, ciphertextPtr);

	// next two lines executes the shellcode buffer (ciphertext...that should prolly be renamed)
	int (*run)() = (int(*)())ciphertext;
	run();
	
	// loop to print out encrypted / decrypted shellcode
/*
	int i = 0;
	for (i; i < strlen(shellcode); i++)
		{
			printf("\\x%x", ciphertext[i]);
		}

*/
	return 0;
}

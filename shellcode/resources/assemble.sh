#!/bin/bash

echo [*]Assembling $1.asm with nasm
nasm -f elf32 $1.asm -o $1.o

echo [*]Linking $1.o with ld
ld -N $1.o -o $1

echo [+]Done!!!

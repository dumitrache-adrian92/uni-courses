ASM = nasm
CC = gcc
CFLAGS = -Wall -m32 -Wno-implicit-function-declaration
LDFLAGS = -m32

.PHONY: all clean

all: ex1

file: ex1.o

ex1.o: ex1.asm
	$(ASM) -f elf32 -o $@ $<

clean:
	-rm -f *~
	-rm -f ex1.o ex1

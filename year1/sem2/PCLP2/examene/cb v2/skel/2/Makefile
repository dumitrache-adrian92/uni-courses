ASM = nasm
CC = gcc
CFLAGS = -Wall -m32 -Wno-implicit-function-declaration
LDFLAGS = -m32

.PHONY: all clean

all: ex2

ex2: ex2.o

ex2.o: ex2.asm
	$(ASM) -f elf32 -o $@ $<

clean:
	-rm -f *~
	-rm -f ex2.o ex2

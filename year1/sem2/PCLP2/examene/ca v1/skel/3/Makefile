ASM = nasm
ASM_FLAGS = -f elf32 -g -Fdwarf
CFLAGS = -Wall -m32 -fno-stack-protector -mpreferred-stack-boundary=2 -fno-PIC
LDFLAGS = -m32 -no-pie

.PHONY: all clean

all: object_attack

object_attack: object.o object_attack.o

object_attack.o: object_attack.c

clean:
	-rm -f *~
	-rm -f object_attack object_attack.o

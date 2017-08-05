CFLAGS = -std=gnu99 -static -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Werror -Wextra
CC = i386-elf-gcc -ggdb -c -I../include/ -I../../include/
C_SRC = console.c
default:
	cd src/ && $(CC) $(CFLAGS) $(C_SRC) && mv *.o ../
clean:
	rm console.o

C_SRC = src/kernel/kmain.c src/kernel/strings.c src/kernel/serial.c src/kernel/console.c src/kernel/descriptors_manager.c
ASSEMBLY_SRC = src/kernel/port.s
ASSEMBLY_OBJS = src/kernel/port.o
OBJS = kmain.o bootloader.o
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Werror -Wextra
CC = gcc -ggdb -c -Iinclude/
OBJECT_COPY = objcopy
NASM = nasm -f elf
LD = ld
all: compile generate_debub_info generate_iso
clean:
	rm cagaOS.iso
compile: loader drivers kernel
	$(LD) -T bootloader.ld -melf_i386 *.o -o kernel.elf
	rm *.o
generate_iso:
	mv kernel.elf iso/boot
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os   -quiet -boot-info-table -o os.iso iso
	mv os.iso cagaOS.iso
run_bochs:
	bochs -f bochsrc.txt -q
run:
	qemu-system-i386 -boot d -cdrom cagaOS.iso -m 256 -serial file:cagaOS.log
debug:
		qemu-system-i386 -s -S -boot d -cdrom cagaOS.iso -m 256 -serial file:cagaOS.log
loader:
	$(NASM) src/loader/bootloader.s
	mv src/loader/bootloader.o .
generate_debub_info:
	$(OBJECT_COPY) --only-keep-debug kernel.elf kernel.sym
	$(OBJECT_COPY) --strip-debug kernel.elf
kernel:
	$(CC) $(C_SRC) $(CFLAGS)
	$(NASM) src/kernel/memory_gdt_setup.s && mv src/kernel/memory_gdt_setup.o .
drivers:
	$(NASM) $(ASSEMBLY_SRC)
	mv $(ASSEMBLY_OBJS) .
export_assembly:
	$(CC) -Iinclude/ -masm=intel -S $(C_SRC) $(CFLAGS)

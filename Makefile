C_SRC = src/kernel/kmain.c src/kernel/console.c src/kernel/string.c src/kernel/serial.c src/kernel/descriptors_manager.c src/kernel/keyboard.c src/kernel/interruption_handler.c src/kernel/pic_manager.c src/kernel/virtual_memory_manager.c
ASSEMBLY_SRC = src/kernel/port.s
ASSEMBLY_OBJS = src/kernel/port.o
OBJS = kmain.o bootloader.o
CFLAGS = -std=gnu99 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Werror -Wextra
LIB_PATH=.
CC = /opt/local/bin/i386-elf-gcc -O0 -ggdb  -Iinclude/      -c
OBJECT_COPY = /opt/local/bin/i386-elf-objcopy
NASM = nasm -g -f elf
LD = /opt/local/bin/i386-elf-ld
QEMU= /opt/local/bin/qemu-system-i386
all: compile generate_debub_info generate_iso
clean:
	rm cagaOS.iso
	rm kernel.sym
	rm iso/boot/kernel.elf
compile: loader drivers kernel
	echo "begin to link kernel"
	$(LD) -T bootloader.ld -melf_i386  *.o -o kernel.elf
	rm *.o
generate_iso:
	mv kernel.elf iso/boot
	/usr/local/bin/mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os   -quiet -boot-info-table -o os.iso iso
	mv os.iso cagaOS.iso
run_bochs:
	bochs -f bochsrc.txt -q
run:
	$(QEMU) -boot d -cdrom cagaOS.iso -m 256 -serial file:cagaOS.log
debug:
	$(QEMU) -s -S -boot d -cdrom cagaOS.iso -m 256 -serial file:cagaOS.log
gdb:
	i386-elf-gdb -x script.gdb --tui
loader:
	$(NASM) src/loader/bootloader.s
	mv src/loader/bootloader.o .
generate_debub_info:
	$(OBJECT_COPY) --only-keep-debug kernel.elf kernel.sym
#	$(OBJECT_COPY) --strip-debug kernel.elf
kernel:
	$(CC) $(C_SRC) $(CFLAGS)
	$(NASM) src/kernel/memory_gdt_setup.s && mv src/kernel/memory_gdt_setup.o .
	$(NASM) src/kernel/string_perf.s && mv src/kernel/string_perf.o .
	$(NASM) src/kernel/mm.s && mv src/kernel/mm.o .
	$(NASM) src/kernel/interruption_handler_assembly.s && mv src/kernel/interruption_handler_assembly.o .
drivers:
	$(NASM) $(ASSEMBLY_SRC)
	mv $(ASSEMBLY_OBJS) .
export_assembly:
	$(CC) -Iinclude/ -masm=intel -S $(C_SRC) $(CFLAGS)

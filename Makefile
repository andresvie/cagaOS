C_SRC = src/kernel/kmain.c src/kernel/string.c src/kernel/serial.c src/kernel/descriptors_manager.c src/kernel/keyboard.c src/kernel/interruption_handler.c src/kernel/pic_manager.c
ASSEMBLY_SRC = src/kernel/port.s
ASSEMBLY_OBJS = src/kernel/port.o
OBJS = kmain.o bootloader.o
CFLAGS = -std=gnu99 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Werror -Wextra
LIBS=-lconsole
LIB_PATH=.
CC = i386-elf-gcc -ggdb  -DEXTERN=1 -Iinclude/ -Iconsole/include/     -c
OBJECT_COPY = i386-elf-objcopy
NASM = nasm -g -f elf
LD = i386-elf-ld
LIBRARIES=console/*.o
all: compile generate_debub_info generate_iso
clean:
	rm cagaOS.iso
compile: loader compile_console drivers kernel
	echo "begin to link kernel"
	$(LD) -T bootloader.ld -melf_i386 $(LIBRARIES) *.o -o kernel.elf
	rm *.o
	rm $(LIBRARIES)
compile_console:
	echo "compile console"
	cd console && make
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
gdb:
	i386-elf-gdb --tui
loader:
	$(NASM) src/loader/bootloader.s
	mv src/loader/bootloader.o .
generate_debub_info:
	$(OBJECT_COPY) --only-keep-debug kernel.elf kernel.sym
	$(OBJECT_COPY) --strip-debug kernel.elf
kernel:
	$(CC) $(C_SRC) $(CFLAGS)
	$(NASM) src/kernel/memory_gdt_setup.s && mv src/kernel/memory_gdt_setup.o .
	$(NASM) src/kernel/string_perf.s && mv src/kernel/string_perf.o .
	$(NASM) src/kernel/interruption_handler_assembly.s && mv src/kernel/interruption_handler_assembly.o .
drivers:
	$(NASM) $(ASSEMBLY_SRC)
	mv $(ASSEMBLY_OBJS) .
export_assembly:
	$(CC) -Iinclude/ -masm=intel -S $(C_SRC) $(CFLAGS)

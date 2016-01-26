CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

ASM_OBJ = io/asm_io.o io/asm_gdt.o io/asm_interrupt.o
IO_OBJ =  io/io.o io/serial.o io/descriptor_tables.o io/isr.o
UTIL_OBJ = util/common.o
OBJECTS = loader.o kmain.o $(ASM_OBJ) $(IO_OBJ) $(UTIL_OBJ) 

all: kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
                -b boot/grub/stage2_eltorito    \
                -no-emul-boot                   \
                -boot-load-size 4               \
                -A os                           \
                -input-charset utf8             \
                -quiet                          \
                -boot-info-table                \
                -o os.iso                       \
                iso

run: os.iso
	bochs -f bochsrc.txt -q

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

clean:
	rm -rf *.o kernel.elf os.iso
	rm -rf ./io/*.o


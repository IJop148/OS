C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

OBJ = ${C_SOURCES:.c=.o}

all:
	make os-image

display:
	echo ${C_SOURCES}
	echo '-------------------'
	echo ${HEADERS}


clean:
	del /s *.bin
	del /s *.o
	del /s *.elf

os-image: boot_sect.bin kernel.bin
	cd build
	type $^ > build/$@

boot_sect.bin: assembly/boot_sect.asm
	nasm $< -f bin -o $@

kernel.bin: assembly/kernel_entry.o ${OBJ}
	echo $(OBJ)
	ld -v -e _start -o kernel.elf -Ttext 0x1000 $^
	objcopy -O binary kernel.elf $@

# Assemble the kernel_entry.
%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

# Generic rule for compiling C code to an object file
%.o: %.c ${HEADERS}
	echo "--------------------------"
	echo ${HEADERS}
	gcc -ffreestanding -c $< -o $@ -Ikernel -Idrivers

all:
	make build/kernel_entry.o
	make build/kernel.o
	make build/kernel.bin
	make build/boot_sect.bin
	make os-image

clean:
	del /s build\*.bin
	del /s build\*.o
	del /s build\*.elf
	del /s build\*.map
	del /s build\*.img

os-image: build/boot_sect.bin build/kernel.bin
	copy /b build\boot_sect.bin+build\kernel.bin os-image

build/boot_sect.bin: assembly/boot_sect.asm
	nasm $< -f bin -o $@

build/kernel.bin: build/kernel_entry.o build/kernel.o
	ld -m i386pe -o build/kernel.elf -Ttext 0x1000 $^
	objcopy -O binary build/kernel.elf $@

build/kernel_entry.o: assembly/kernel.asm
	nasm $< -f elf -o $@

build/kernel.o: c/kernel.c
	gcc -ffreestanding -c $< -o $@

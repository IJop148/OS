; Set the origin of the program to 0x7c00
[org 0x7c00]

; Define the offset of the kernel
KERNEL_OFFSET equ 0x1000

; Store the boot drive number in memory
mov [BOOT_DRIVE], dl

; Set the base pointer (bp) and stack pointer (sp)
mov bp, 0x9000
mov sp, bp

; Print a message in real mode
mov bx, MSG_REAL_MODE
call print_string

; Load the kernel into memory
call load_kernel

; Switch to protected mode
call switch_to_pm

; Infinite loop
jmp $

%include "assembly/print/print_string.asm"
%include "assembly/print/print_string_pm.asm"
%include "assembly/boot/disk_load.asm"
%include "assembly/boot/gdt.asm"
%include "assembly/boot/pm_switch.asm"

[bits 16]
load_kernel:
    ; Print a message indicating that the kernel is being loaded
    mov bx, MSG_LOAD_KERNEL
    call print_string

    ; Load the kernel from disk into memory
    mov bx, KERNEL_OFFSET
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    ; Print a message indicating that the system has entered protected mode
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    ; Call the kernel code in protected mode
    call KERNEL_OFFSET

    ; Infinite loop
    jmp $

; Define the boot drive variable
BOOT_DRIVE db 0

; Define the messages to be printed
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Successfully landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory.", 0

; Fill the remaining bytes of the boot sector with zeros
times 510 - ($ - $$) db 0

; Add the boot signature
dw 0xaa55

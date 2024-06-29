[bits 16]
switch_to_pm:
    cli ; Disable interrupts

    lgdt [gdt_descriptor] ; Load the GDT

    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm ; Jump to the 32-bit code segment

[bits 32]
init_pm:
    mov ax, DATA_SEG ; Set the data segment register
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; Set the base pointer to 0x90000
    mov esp, ebp ; Set the stack pointer to the base pointer

    call BEGIN_PM ; Call the BEGIN_PM subroutine

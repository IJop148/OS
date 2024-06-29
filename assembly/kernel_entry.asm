[bits 32]
[global _start]
[extern _kernel_main]
_start:
    call _kernel_main
    jmp $
    
gdt_start:
    gdt_null:               ; Null segment descriptor
        dd 0x0              ; Null segment limit (lower 32 bits)
        dd 0x0              ; Null segment base (lower 32 bits)

    gdt_code:               ; Code segment descriptor
        dw 0xffff           ; Code segment limit (16 bits)
        dw 0x0              ; Code segment base (16 bits)
        db 0x0              ; Code segment base (middle 8 bits)
        db 0b10011010       ; Code segment access byte
        db 0b11001111       ; Code segment flags and limit (upper 4 bits)
        db 0x0              ; Code segment base (upper 8 bits)

    gdt_data:               ; Data segment descriptor
        dw 0xffff           ; Data segment limit (16 bits)
        dw 0x0              ; Data segment base (16 bits)
        db 0x0              ; Data segment base (middle 8 bits)
        db 0b10010010       ; Data segment access byte
        db 0b11001111       ; Data segment flags and limit (upper 4 bits)
        db 0x0              ; Data segment base (upper 8 bits)

gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1   ; Size of the GDT (in bytes)
    dd gdt_start                 ; Address of the GDT

CODE_SEG equ gdt_code - gdt_start   ; Offset of the code segment in the GDT
DATA_SEG equ gdt_data - gdt_start   ; Offset of the data segment in the GDT

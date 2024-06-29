[bits 16]
print_string:
    pusha
    mov ah, 0x0e
    .print_chars:
    jmp print_char ; Jump to the print_char subroutine
    .done:
    mov al, 0x0a ; Move the line feed character to AL
    int 0x10 ; Call interrupt 0x10 to print the line feed character
    mov al, 0x0d ; Move the carriage return character to AL
    int 0x10 ; Call interrupt 0x10 to print the carriage return character
    popa ; Restore the registers
    ret ; Return from the subroutine

print_char:
    mov al, [bx] ; Move the character at the memory location pointed by BX to AL
    cmp al, 0 ; Compare AL with 0
    je print_string.done ; If AL is equal to 0, jump to the .done label
    int 0x10 ; Call interrupt 0x10 to print the character in AL
    inc bx ; Increment BX to point to the next character
    jmp print_string.print_chars ; Jump back to the .print_chars label
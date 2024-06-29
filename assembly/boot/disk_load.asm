disk_load:
    push dx         ; Save the value of DX register on the stack
    mov ah, 0x02    ; Set AH register to 0x02 (Read sector from disk)
    mov al, dh      ; Set AL register to the value of DH register
    mov ch, 0x00    ; Set CH register to 0x00 (Cylinder number)
    mov dh, 0x00    ; Set DH register to 0x00 (Head number)
    mov cl, 0x02    ; Set CL register to 0x02 (Sector number)
    int 0x13        ; Call interrupt 0x13 (Disk I/O)
    jc disk_error   ; Jump to disk_error label if carry flag is set (indicating an error)
    pop dx          ; Restore the value of DX register from the stack
    cmp dh, al      ; Compare the value of DH register with AL register
    jne disk_error  ; Jump to disk_error label if they are not equal
    ret             ; Return from the function

disk_error:
    mov bx, DISK_ERROR_MSG  ; Load the address of DISK_ERROR_MSG into BX register
    call print_string       ; Call the print_string function to print the error message
    jmp $                   ; Jump to the current location (infinite loop)

DISK_ERROR_MSG db "Disk read error!", 0  ; Define the DISK_ERROR_MSG string

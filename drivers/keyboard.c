// The driver for the keyboard
#include "keyboard.h"
#include "low_level.h"
#include "screen.h"
#include "interrupt.h"
#include "idt.h"

void handle_key_press(unsigned char scan_code) {
    // If the scan code is less than 0x80, the key has been pressed.
    // If the scan code is greater than or equal to 0x80, the key has been released.
    if (scan_code < 0x80) {
        // The key has been pressed.
        // Check if the key is a letter.
        print_hex(scan_code);
    }
}

// Helper function to convert a byte to a hex string
void byte_to_hex(unsigned char byte, char* str) {
    char hex_chars[] = "0123456789ABCDEF";
    str[0] = '0';
    str[1] = 'x';
    str[2] = hex_chars[(byte >> 4) & 0x0F]; // Extract the high nibble and find the corresponding hex character
    str[3] = hex_chars[byte & 0x0F];        // Extract the low nibble and find the corresponding hex character
    str[4] = '\0';                          // Null-terminate the string
}

// Function definitions
void keyboard_callback() {
    // Read from the keyboard's data port to get the pressed key and clear the buffer
    unsigned char keycode = port_byte_in(0x60);

    char hexStr[5]; // Enough for "0x" + two hex digits + null terminator
    byte_to_hex(keycode, hexStr); // Convert keycode to hex string using the new function

    // Print the hex value to the screen
    print_string("Detected key: ");
    print_string(hexStr);

    // Acknowledge the interrupt to the PIC if needed, e.g., by sending EOI
    pic_send_eoi(IRQ1); // Assuming IRQ1 is the correct IRQ number for the keyboard
}

// Function to send EOI to the appropriate PIC
void pic_send_eoi(unsigned char irq) {
    if (irq >= 8) {
        // If the IRQ is handled by PIC2, acknowledge it there.
        port_byte_out(PIC2_COMMAND, PIC_EOI);
    }
    // Always acknowledge the interrupt at PIC1
    port_byte_out(PIC1_COMMAND, PIC_EOI);
}

// Function to initialize the keyboard
void init_keyboard() {
    idt_set_gate(0x21, (unsigned int)keyboard_callback, 0x08, 0x8E);
}
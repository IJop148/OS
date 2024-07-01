// File: keyboard.c
// -----------------

#include "keyboard.h"
#include "screen.h"
#include "irq.h"
#include "low_level.h"

// Handles the keyboard interrupt
void keyboard_handler() {
    // Read from the keyboard's data buffer
    u8int scancode = port_byte_in(0x60);

    // Print the scancode
    char sc_ascii[2];
    sc_ascii[0] = scancode;
    sc_ascii[1] = '\0';
    print_string(sc_ascii, -1, -1, WHITE_ON_BLACK);

    // Acknowledge the interrupt
    port_byte_out(0x20, 0x20);
}

// Installs the keyboard driver
void keyboard_install() {
    // Register the keyboard handler
    register_interrupt_handler(0, keyboard_handler);

    // Enable the keyboard interrupt
    port_byte_out(0x21, port_byte_in(0x21) & 0xFD);
}




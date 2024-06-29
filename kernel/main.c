#include "screen.h"
#include "keyboard.h"
#include "interrupt.h"
#include "idt.h"

// Code for the kernel entry point
void kernel_main() {
    clear_screen();
    
    print_string("Welcome to the kernel!\n");

    init_idt();
    pic_remap();
    init_interrupt_handlers();
    init_keyboard();

    // Enable interrupts globally
    asm volatile("sti");

    while (1){
        // asm volatile("hlt"); // Halt the CPU until the next interrupt
    }

    return;
}

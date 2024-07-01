#include "screen.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "keyboard.h"
#include "timer.h"
#include "pic.h"

// Code for the kernel entry point
void kernel_main() {
    // clear_screen();

    print_string("Loading kernel...", 0, 0, WHITE_ON_BLACK);

    print_string("GDT...", 0, 1, WHITE_ON_BLACK);
    // Initialize the GDT
    gdt_install();

    print_string("IDT...", 0, 2, WHITE_ON_BLACK);
    // Initialize the IDT
    idt_install();

    print_string("PIC...", 0, 3, WHITE_ON_BLACK);

    // Initialize the PIC
    pic_install();

    print_string("ISRs...", 0, 4, WHITE_ON_BLACK);

    // initialize the ISRs
    isr_install();

    print_string("IRQs...", 0, 5, WHITE_ON_BLACK);
    
    // Initialize the IRQs
    irq_install();

    print_string("Keyboard...", 0, 6, WHITE_ON_BLACK);

    // Initialize the keyboard
    keyboard_install();

    print_string("Timer...", 0, 7, WHITE_ON_BLACK);

    // initialize the timer
    timer_phase(100);

    // // Enable interrupts
    // __asm__ volatile("sti;");

    // Print a welcome message
    print_string("Welcome to the kernel\nSuccy my pippie", 0, 0, WHITE_ON_BLACK);
}

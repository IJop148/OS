// file: timer.c
// -----------------

#include "timer.h"
#include "irq.h"
#include "screen.h"
#include "low_level.h"


u32int tick = 0;

// Handles the timer interrupt
void timer_handler(registers_t regs) {
    tick++;
    print_string("Tick: ", 0, 0, WHITE_ON_BLACK);
    print_int(tick);
}

// Installs the timer driver
void timer_install() {
    // Register the timer handler
    register_interrupt_handler(0, timer_handler); // Replace 'irq0' with a valid identifier or value

    // Enable the timer interrupt
    port_byte_out(0x21, port_byte_in(0x21) & 0xFE);
}

// Sets the timer frequency
void set_timer_phase(int hz) {
    int divisor = 1193180 / hz;       // Calculate the divisor
    port_byte_out(0x43, 0x36);         // Set command byte 0x36
    port_byte_out(0x40, divisor & 0xFF);   // Set low byte of divisor
    port_byte_out(0x40, divisor >> 8);     // Set high byte of divisor
}

// Initializes the timer
void timer_phase(int hz) {
    set_timer_phase(hz);
    timer_install();
}
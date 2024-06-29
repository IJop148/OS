#include "interrupt.h"
#include "low_level.h"

// Initialize all elements to 0 (NULL) to indicate no handler is registered
void init_interrupt_handlers() {
    for (int i = 0; i < NUM_IRQS; i++) {
        interrupt_handlers[i] = 0;
    }
}

// The function to register an interrupt handler for a specific IRQ
void register_interrupt_handler(int irq, interrupt_handler_t handler) {
    if (irq >= 0 && irq < NUM_IRQS) {
        interrupt_handlers[irq] = handler;
    }
}

// The interrupt handler function
void interrupt_handler(registers_t regs) {
    // Get the interrupt number from the registers
    int irq = regs.int_no;

    // Check if a handler is registered for this IRQ
    if (interrupt_handlers[irq] != 0) {
        // Call the handler function
        interrupt_handlers[irq]();
    }

    // If the IRQ is greater than or equal to 40, we need to send an EOI to the slave PIC
    if (irq >= 40) {
        port_byte_out(PIC2_COMMAND, PIC_EOI);
    }

    // Send an EOI to the master PIC
    port_byte_out(PIC1_COMMAND, PIC_EOI);
}
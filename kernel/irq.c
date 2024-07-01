// File: irq.c
// -----------------------------

#include "irq.h"
#include "idt.h"
#include "low_level.h"
#include "pic.h"

// Function pointer array for interrupt handlers
isr_t interrupt_handlers[256];

// Function to register an interrupt handler
void register_interrupt_handler(u8int n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

// Function to handle the interrupt request
void irq_handler(registers_t regs) {
    // If the interrupt is greater than 40, send an EOI to the slave controller
    if (regs.int_no >= 40) {
        pic_send_eoi(PIC_SLAVE_IRQ);
    }
    // Send an EOI to the master interrupt controller
    pic_send_eoi(PIC_MASTER_IRQ);

    // If there is a handler for the interrupt, call it
    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

// Function to initialize the IRQs
void irq_install() {
    // Initialize the PIC
    init_pic();

    // Install the IRQs
    idt_set_gate(32,  (u32int)irq0,  0x08, 0x8E); // IRQ_TIMER (timer)
    idt_set_gate(33,  (u32int)irq1,  0x08, 0x8E); // IRQ_KEYBOARD (keyboard)
    idt_set_gate(34,  (u32int)irq2,  0x08, 0x8E); // IRQ_CASCADE (cascade for 8-15)
    idt_set_gate(35,  (u32int)irq3,  0x08, 0x8E); // IRQ_COM2 (COM2)
    idt_set_gate(36,  (u32int)irq4,  0x08, 0x8E); // IRQ_COM1 (COM1)
    idt_set_gate(37,  (u32int)irq5,  0x08, 0x8E); // IRQ_LPT2 (LPT2)
    idt_set_gate(38,  (u32int)irq6,  0x08, 0x8E); // IRQ_FLOPPY (floppy)
    idt_set_gate(39,  (u32int)irq7,  0x08, 0x8E); // IRQ_LPT1 (LPT1)
    idt_set_gate(40,  (u32int)irq8,  0x08, 0x8E); // IRQ_RTC (RTC)
    idt_set_gate(41,  (u32int)irq9,  0x08, 0x8E); // IRQ_CASCADE2 (cascade for 2-9)
    idt_set_gate(42,  (u32int)irq10, 0x08, 0x8E); // IRQ_RESERVED1 (reserved)
    idt_set_gate(43,  (u32int)irq11, 0x08, 0x8E); // IRQ_RESERVED2 (reserved)
    idt_set_gate(44,  (u32int)irq12, 0x08, 0x8E); // IRQ_PS2_MOUSE (PS2 mouse)
    idt_set_gate(45,  (u32int)irq13, 0x08, 0x8E); // IRQ_FPU (FPU)
    idt_set_gate(46,  (u32int)irq14, 0x08, 0x8E); // IRQ_PRIMARY_ATA (primary ATA)
    idt_set_gate(47,  (u32int)irq15, 0x08, 0x8E); // IRQ_SECONDARY_ATA (secondary ATA)
}

// Function to handle the interrupt
void isr_handler(registers_t regs) {
    // If there is a handler for the interrupt, call it
    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

// Function to initialize the ISRs
void isr_install() {
    // Install the ISRs
    idt_set_gate(0,  (u32int)isr0,   0x08, 0x8E); // ISR0 (divide by zero)
    idt_set_gate(1,  (u32int)isr1,   0x08, 0x8E); // ISR1 (debug)
    idt_set_gate(2,  (u32int)isr2,   0x08, 0x8E); // ISR2 (non-maskable interrupt)
    idt_set_gate(3,  (u32int)isr3,   0x08, 0x8E); // ISR3 (breakpoint)
    idt_set_gate(4,  (u32int)isr4,   0x08, 0x8E); // ISR4 (overflow)
    idt_set_gate(5,  (u32int)isr5,   0x08, 0x8E); // ISR5 (bound range exceeded)
    idt_set_gate(6,  (u32int)isr6,   0x08, 0x8E); // ISR6 (invalid opcode)
    idt_set_gate(7,  (u32int)isr7,   0x08, 0x8E); // ISR7 (device not available)
    idt_set_gate(8,  (u32int)isr8,   0x08, 0x8E); // ISR8 (double fault)
    idt_set_gate(9,  (u32int)isr9,   0x08, 0x8E); // ISR9 (coprocessor segment overrun)
    idt_set_gate(10, (u32int)isr10,  0x08, 0x8E); // ISR10 (invalid TSS)
    idt_set_gate(11, (u32int)isr11,  0x08, 0x8E); // ISR11 (segment not present)
    idt_set_gate(12, (u32int)isr12,  0x08, 0x8E); // ISR12 (stack segment fault)
    idt_set_gate(13, (u32int)isr13,  0x08, 0x8E); // ISR13 (general protection fault)
    idt_set_gate(14, (u32int)isr14,  0x08, 0x8E); // ISR14 (page fault)
    idt_set_gate(15, (u32int)isr15,  0x08, 0x8E); // ISR15 (unknown interrupt)
    idt_set_gate(16, (u32int)isr16,  0x08, 0x8E); // ISR16 (coprocessor fault)
    idt_set_gate(17, (u32int)isr17,  0x08, 0x8E); // ISR17 (alignment check)
    idt_set_gate(18, (u32int)isr18,  0x08, 0x8E); // ISR18 (machine check)
    idt_set_gate(19, (u32int)isr19,  0x08, 0x8E); // ISR19 (SIMD floating-point exception)
    idt_set_gate(20, (u32int)isr20,  0x08, 0x8E); // ISR20 (virtualization exception)
}
#include "idt.h"
#include "low_level.h"


// Function to set an entry in the IDT
void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;
    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags   = flags;
}

// Function to initialize the IDT
void init_idt() {
    idt_ptr.limit = (sizeof(idt_entry_t) * IDT_ENTRIES) - 1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    // Populate the IDT here with idt_set_gate(...)
    // For example, to set the 32nd entry:
    // idt_set_gate(32, (uint32_t)isr32, 0x08, 0x8E);

    // Load the IDT
    asm volatile("lidt (%0)" : : "r" (&idt_ptr));
}

// Remap the PIC
void pic_remap() {
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);
}
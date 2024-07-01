// file: idt.c
// -----------------------------

#include "idt.h"
#include "basic_function.h"

// Define the IDT
idt_gate_t idt[256];
idt_register_t idt_reg;

extern void idt_flush(u32int);

// Function to set an entry in the IDT
void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

// Function to load the IDT
void idt_flush_wrapper() {
    idt_ptr_t idt_ptr;
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (u32int)&idt; 

    idt_flush((u32int)&idt_ptr);
}

// Function to initialize the IDT
void idt_install() {
    // Set the limit and base address of the IDT
    idt_reg.limit = (sizeof(idt_gate_t) * 256) - 1;
    idt_reg.base = (u32int)&idt;

    // Clear the IDT
    memset((u8int*)idt, 0, sizeof(idt_gate_t) * 256);

    // Add any ISRs here

    // Load the IDT
    idt_flush_wrapper();
}
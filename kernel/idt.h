// File: idt.h
// -----------------
// This file contains the definitions for the IDT

#ifndef IDT_H
#define IDT_H

#include "types.h"

// Variable declarations in idt.c
extern idt_gate_t idt[256];
extern idt_register_t idt_reg;


// Function declaration
void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags);
void idt_install();

#endif // IDT_H
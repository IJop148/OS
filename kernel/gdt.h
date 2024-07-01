// gdt.h
// -----------------------------

#ifndef GDT_H
#define GDT_H

#include "types.h"
#include "screen.h"

// Function declarations
void set_gdt_entry(int num, u32int base, u32int limit, u8int access, u8int gran);
void gdt_install();



#endif // GDT_H
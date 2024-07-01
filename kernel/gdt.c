// gdt.c
// -----------------------------

#include "gdt.h"
#include "basic_function.h"

// Define the GDT
gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

// Function to load the GDT
extern void gdt_flush(); // Implemented in gdt_asm.asm

// Function to set a GDT entry
void set_gdt_entry(int num, u32int base, u32int limit, u8int access, u8int gran) {
    // Set the base address
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    // Set the limit
    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = ((limit >> 16) & 0x0F);

    // Set the granularity and access flags
    gdt_entries[num].granularity |= (gran & 0xF0);
    gdt_entries[num].access_flags = access;
}

tss_entry_t setTSS(u32int esp0) {
    tss_entry_t tss_entry;
    memset((u8int*)&tss_entry, 0, sizeof(tss_entry));
    tss_entry.ss0 = 0x10;
    tss_entry.esp0 = 0x0;
    tss_entry.cs = 0x0b;
    tss_entry.ss = 0x13;
    tss_entry.ds = 0x13;
    tss_entry.es = 0x13;
    tss_entry.fs = 0x13;
    tss_entry.gs = 0x13;
    tss_entry.iomap_base = sizeof(tss_entry);
    return tss_entry;
}

// Installs the GDT
void gdt_install() {

    // debug
    print_string("Loading GDT...\n", -1, -1, WHITE_ON_BLACK);
    
    // Set the GDT pointer and limit
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base = (u32int)&gdt_entries;

    // debug
    print_string("GDT pointer set\n", -1, -1, WHITE_ON_BLACK);

    // NULL descriptor
    set_gdt_entry(0, 0, 0, 0, 0);
    // debug
    print_string("NULL descriptor set\n", -1, -1, WHITE_ON_BLACK);


    // Code segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // debug
    print_string("Code segment set\n", -1, -1, WHITE_ON_BLACK);


    // Data segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // debug
    print_string("Data segment set\n", -1, -1, WHITE_ON_BLACK);


    // User mode code segment
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // debug
    print_string("User mode code segment set\n", -1, -1, WHITE_ON_BLACK);

    // User mode data segment
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    // debug
    print_string("User mode data segment set\n", -1, -1, WHITE_ON_BLACK);

    // // TSS
    // tss_entry_t tss_entry = setTSS(0x0);
    // set_gdt_entry(5, (u32int)&tss_entry, sizeof(tss_entry), 0x89, 0x40);
    // // debug
    // print_string("TSS set\n", -1, -1, WHITE_ON_BLACK);

    // debug
    print_string("GDT entries set\n", -1, -1, WHITE_ON_BLACK);

    // Load the GDT
    gdt_flush();

    // debug
    print_string("GDT loaded\n", -1, -1, WHITE_ON_BLACK);
}
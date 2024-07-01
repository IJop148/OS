// file: types.h

#ifndef TYPES_H
#define TYPES_H

    // Defining types for the kernel
    // ints
    typedef unsigned int   u32int;
    typedef          int   s32int;
    typedef unsigned short u16int;
    typedef          short s16int;
    typedef unsigned char  u8int;
    typedef          char  s8int;

    // String
    typedef char* string;

        
    // Structure for registers
    typedef struct {
        u32int ds;                  // Data segment selector
        u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
        u32int int_no, err_code;    // Interrupt number and error code (if applicable)
        u32int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
    } registers_t;

    // Structure for IDT
    typedef struct {
        u16int base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
        u16int sel;                 // Kernel segment selector.
        u8int  always0;             // This must always be zero.
        u8int  flags;               // More flags. See documentation.
        u16int base_hi;             // The upper 16 bits of the address to jump to.
    } __attribute__((packed)) idt_gate_t;

    // A struct describing a pointer to an array of interrupt handlers.
    // This is in a format suitable for giving to 'lidt'.
    typedef struct {
        u16int limit;
        u32int base;                // The address of the first element in our idt_gate_t array.
    } __attribute__((packed)) idt_register_t;

    
    // Define the GDT
    typedef struct {
        u16int limit_low;       // The lower 16 bits of the limit
        u16int base_low;        // The lower 16 bits of the base
        u8int  base_middle;     // The next 8 bits of the base
        u8int  access_flags;    // Access flags
        u8int  granularity;     // Granularity flags
        u8int  base_high;       // The last 8 bits of the base
    } __attribute__((packed)) gdt_entry_t;

    // Define the GDT pointer
    typedef struct {
        u16int limit;       // The upper 16 bits of all selector limits
        u32int base;        // The address of the first gdt_entry_t struct
    } __attribute__((packed)) gdt_ptr_t;

    // TSS structure
    typedef struct {
        u32int prev_tss;   // The previous TSS - if we used hardware task switching this would form a linked list.
        u32int esp0;       // The stack pointer to load when we change to kernel mode.
        u32int ss0;        // The stack segment to load when we change to kernel mode.
        u32int esp1;       // Unused...
        u32int ss1;
        u32int esp2;
        u32int ss2;
        u32int cr3;
        u32int eip;
        u32int eflags;
        u32int eax;
        u32int ecx;
        u32int edx;
        u32int ebx;
        u32int esp;
        u32int ebp;
        u32int esi;
        u32int edi;
        u32int es;         // The value to load into ES when we change to kernel mode.
        u32int cs;         // The value to load into CS when we change to kernel mode.
        u32int ss;         // The value to load into SS when we change to kernel mode.
        u32int ds;         // The value to load into DS when we change to kernel mode.
        u32int fs;         // The value to load into FS when we change to kernel mode.
        u32int gs;         // The value to load into GS when we change to kernel mode.
        u32int ldt;        // Unused...
        u16int trap;
        u16int iomap_base;
    } __attribute__((packed)) tss_entry_t;


    // IDT
    struct idt_entry_struct {
        u8int base_lo; // The lower 16 bits of the address to jump to when this interrupt fires.
        u16int sel;     // Kernel segment selector.
        u8int  always0; // This must always be zero.
        u8int  flags;   // More flags. See documentation.
        u16int base_hi; // The upper 16 bits of the address to jump to.
    } __attribute__((packed));
    typedef struct idt_entry_struct idt_entry_t;
    
    struct idt_ptr_struct {
        u16int limit;
        u32int base; // The address of the first element in our idt_entry_t array.
    } __attribute__((packed));
    typedef struct idt_ptr_struct idt_ptr_t;
    

    // Function pointer definition
    typedef void (*isr_t)(registers_t);

    // Function pointer definition
    typedef void (*irq_t)(registers_t);

#endif // TYPES_H
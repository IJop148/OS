#include "low_level.h"
#include "shortcuts.h"

// IDT entry structure
struct idt_entry_struct {
    uint16_t base_lo; // The lower 16 bits of the address to jump to
    uint16_t sel;     // Kernel segment selector
    uint8_t  always0; // This must always be zero
    uint8_t  flags;   // Flags
    uint16_t base_hi; // The upper 16 bits of the address to jump to
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// IDT register structure
struct idt_ptr_struct {
    uint16_t limit;
    uint32_t base;    // The address of the first element in our idt_entry_t array
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

// Declare an array of IDT entries and an IDT pointer
#define IDT_ENTRIES 256
idt_entry_t idt_entries[IDT_ENTRIES];
idt_ptr_t   idt_ptr;


// Functions
void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags);
void init_idt();
void pic_remap();

#define NUM_IRQS 256 // Assuming 256 possible IRQs for simplicity

// Define the type for the interrupt handler function pointers
typedef void (*interrupt_handler_t)(void);

// Declare an array to hold the handlers for each IRQ
interrupt_handler_t interrupt_handlers[NUM_IRQS];

// Define the registers structure
typedef struct {
    unsigned int ds;                  // Data segment selector
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    unsigned int int_no, err_code;    // Interrupt number and error code (if applicable)
    unsigned int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

// functions
void init_interrupt_handlers();
void register_interrupt_handler(int irq, interrupt_handler_t handler);
void interrupt_handler(registers_t regs);

// PIC ports
#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

// Command to send an End Of Interrupt (EOI)
#define PIC_EOI      0x20
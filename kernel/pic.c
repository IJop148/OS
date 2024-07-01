// File: pic.c
// -----------------

#include "pic.h"
#include "low_level.h"

void io_wait() {
    port_byte_out(0x80, 0);
}

// Initializes the PIC
void init_pic() {
    // ICW1: Begin initialization
    port_byte_out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    port_byte_out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    // ICW2: Map IRQs 0-7 to IDT entries 32-39
    port_byte_out(PIC1_DATA, 0x20);
    port_byte_out(PIC2_DATA, 0x28);
    io_wait();

    // ICW3: PIC1 is the master, PIC2 is the slave
    port_byte_out(PIC1_DATA, 4);
    port_byte_out(PIC2_DATA, 2);
    io_wait();

    // ICW4: Set x86 mode
    port_byte_out(PIC1_DATA, ICW4_8086);
    port_byte_out(PIC2_DATA, ICW4_8086);
    io_wait();

    // Disable all IRQs
    port_byte_out(PIC1_DATA, 0xFF);
    port_byte_out(PIC2_DATA, 0xFF);
}

// Sends an EOI to the PIC
void pic_send_eoi(u8int irq) {
    if (irq >= 8) {
        port_byte_out(PIC2_COMMAND, PIC_EOI);
    }
    port_byte_out(PIC1_COMMAND, PIC_EOI);
}

// Enables the specified IRQ
void pic_enable_irq(u8int irq) {
    u16int port;
    u8int value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = port_byte_in(port) & ~(1 << irq);
    port_byte_out(port, value);
}

// Disables the specified IRQ
void pic_disable_irq(u8int irq) {
    u16int port;
    u8int value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = port_byte_in(port) | (1 << irq);
    port_byte_out(port, value);
}

// Initializes the PIC
void pic_install() {
    init_pic();
    pic_enable_irq(0);
    pic_enable_irq(1);
    pic_enable_irq(2);
    pic_enable_irq(8);
    pic_enable_irq(12);
}

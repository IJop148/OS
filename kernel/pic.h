// File: pic.h
// -----------------

#ifndef PIC_H
#define PIC_H

#include "types.h"

// PIC ports
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

// ICW1 flags
#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01

// ICW4 flags
#define ICW4_8086 0x01

// PIC EOI command
#define PIC_EOI 0x20

// Function declarations
void init_pic();
void pic_install();
void pic_send_eoi(u8int irq);
void pic_enable_irq(u8int irq);

#endif // PIC_H
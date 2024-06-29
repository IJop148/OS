// The header file for the keyboard driver
#define KEYBOARD_DATA_PORT 0x60

// IRQ for the keyboard
#define IRQ1 1


// functions
void init_keyboard();
void handle_key_press(unsigned char scan_code);
void keyboard_callback();
void pic_send_eoi(unsigned char irq);
void keyboard_handler();

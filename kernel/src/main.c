#include <driver/vga.h>

// Code for the kernel entry point
void kernel_main() {
    clearwin(BLACK, WHITE);

    putstr("Hello, World!", WHITE, BLACK);        
}

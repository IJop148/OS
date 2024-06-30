#include "screen.h"

// Code for the kernel entry point
void kernel_main() {
    clear_screen();

    print_string("Welcome to the kernel\nSuccy my pippie", 0, 0, WHITE_ON_BLACK);
}

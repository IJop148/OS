#include "error_handling.h"

// Function to print an error message
void error(char *message) {
    print_string("Error: ");
    print_string(message);
    print_string("\n");
}

// Function to print a warning message
void warning(char *message) {
    print_string("Warning: ");
    print_string(message);
    print_string("\n");
}


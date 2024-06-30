#include "screen.h"
#include "low_level.h"

// Function definitions
void memory_copy(char *source, char *dest, int no_bytes) {
    for (int i = 0; i < no_bytes; i++) {
        *(dest + i) = *(source + i);
    }
}

int get_screen_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int handle_scrolling(int offset) {
    // If the offset is within the screen limits, return it as is.
    if (offset < MAX_ROWS * MAX_COLS * 2) {
        return offset;
    }

    // Shift the rows up by one.
    for (int i = 1; i < MAX_ROWS; i++) {
        char *source = (char *)(VIDEO_ADDRESS + get_screen_offset(0, i));
        char *dest = (char *)(VIDEO_ADDRESS + get_screen_offset(0, i - 1));
        memory_copy(source, dest, MAX_COLS * 2);
    }

    // Clear the last row.
    char *last_line = (char *)(VIDEO_ADDRESS + get_screen_offset(0, MAX_ROWS - 1));
    for (int i = 0; i < MAX_COLS * 2; i++) {
        last_line[i] = 0;
    }

    // Move the offset to the start of the last row.
    offset -= MAX_COLS * 2;

    return offset;
}

int get_cursor() {
    // The device uses its control register as an index
    // to select its internal registers, of which we are
    // interested in:
    // reg 14: which is the high byte of the cursor's offset
    // reg 15: which is the low byte of the cursor's offset
    // Once the internal register has been selected, we may read or
    // write a byte on the data register.
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    // Since the cursor offset reported by the VGA hardware is the
    // number of characters, we multiply by two to convert it to
    // a character cell offset.
    return offset * 2;
}

void clear_screen() {
    int row = 0;
    int col = 0;

    // Loop through each cell of the screen and write a space
    for (row = 0; row < MAX_ROWS; row++) {
        for (col = 0; col < MAX_COLS; col++) {
            print_char(' ', col, row, WHITE_ON_BLACK);
        }
    }

    // Move the cursor back to the top left.
    set_cursor(get_screen_offset(0, 0));
}

void set_cursor(int offset) {
    offset /= 2; // Convert from cell offset to char offset.

    // This is similar to get_cursor, only now we write
    // bytes to those internal device registers.
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
}

void print_char(char character, int col, int row, char attribute_byte) {
    /* Create a byte (char) pointer to the start of video memory */
    unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;

    /* If attribute byte is zero, assume the default style. */
    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }

    /* Get the video memory offset for the screen location */
    int offset;

    /* If col and row are non-negative, use them for offset. */
    if (col >= 0 && row >= 0) {
        offset = get_screen_offset(col, row);
    }
    /* Otherwise, use the current cursor position. */
    else {
        offset = get_cursor();
    }

    // If we see a newline character, set offset to the end of
    // current row, so it will be advanced to the first col
    // of the next row.
    if (character == '\n') {
        int rows = offset / (2 * MAX_COLS);
        offset = get_screen_offset(79, rows);
    }
    // Otherwise, write the character and its attribute byte to
    // video memory at our calculated offset.
    else {
        vidmem[offset] = character;
        vidmem[offset + 1] = attribute_byte;
    }

    // Update the offset to the next character cell, which is
    // two bytes ahead of the current cell.
    offset += 2;

    // Make scrolling adjustment, for when we reach the bottom
    // of the screen.
    offset = handle_scrolling(offset);

    // Update the cursor position on the screen device.
    set_cursor(offset);
}


// Function to print a string to the screen
void print_string(char *string, int start_col, int start_row, char attribute_byte) {
    // Loop through each character of the string and print it
    int i = 0;
    int row = start_row;
    int col = start_col;
    while (string[i] != 0) {
        if(string[i] == '\n') {
            col = 0;
            row++;
            i++;
            continue;
        }
        print_char(string[i], col, row, attribute_byte);
        col = col + 1 < MAX_COLS ? col + 1 : 0;
        row = col == 0 ? row + 1 : row;
        i++;
    }
}

// Function to print an hex values to the screen
void print_hex(unsigned int n) {
    char hex[16];
    int i = 0;
    while (n > 0) {
        int rem = n % 16;
        if (rem < 10) {
            hex[i] = rem + '0';
        } else {
            hex[i] = rem - 10 + 'A';
        }
        n /= 16;
        i++;
    }
    i--;
    while (i >= 0) {
        print_char(hex[i], -1, -1, WHITE_ON_BLACK);
        i--;
    }
}

void print_int(int n) {
    char str[16];
    int i = 0;
    if (n < 0) {
        print_char('-', -1, -1, WHITE_ON_BLACK);
        n = -n;
    }
    while (n > 0) {
        str[i] = n % 10 + '0';
        n /= 10;
        i++;
    }
    i--;
    while (i >= 0) {
        print_char(str[i], -1, -1, WHITE_ON_BLACK);
        i--;
    }
}
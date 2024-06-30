#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// Attribute byte for our default colour scheme.
#define WHITE_ON_BLACK 0x0f
// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5


#ifndef SCREEN_H
#define SCREEN_H

    void memory_copy(char *source, char *dest, int no_bytes);
    int get_screen_offset(int col, int row);
    int handle_scrolling(int offset);
    int get_cursor();
    void clear_screen();
    void set_cursor(int offset);
    void print_char(char character, int col, int row, char attribute_byte);
    void print_string(char *string, int col, int row, char attribute_byte);
    void print_hex(unsigned int n);

#endif // SCREEN_H

#ifndef __DRIVER_VGA_TEXT
#define __DRIVER_VGA_TEXT

#include <types.h>

// VGA text mode constants
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_EXTENT (VGA_WIDTH * VGA_HEIGHT)

// VGA text mode colors
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define LIGHT_BROWN 14
#define WHITE 15

// VGA text mode memory location
#define VGA_START 0xB8000

// Define the cursor ports
#define CURSOR_PORT_COMMAND     (uint16_t) 0x3D4
#define CURSOR_PORT_DATA        (uint16_t) 0x3D5

// VGA text mode character structure
typedef struct {
    char character;
    uint8_t style;
} vga_char;

// VGA text mode color function
uint8_t vga_color(const uint8_t fg_color, const uint8_t bg_color);
void clearwin(uint8_t fg_color, uint8_t bg_color);
void putchar(const char character, const uint8_t fg_color, const uint8_t bg_color);
void putstr(const char *string, const uint8_t fg_color, const uint8_t bg_color);
uint16_t get_cursor_pos();
void show_cursor();
void hide_cursor();
void advance_cursor();
void set_cursor_pos(uint8_t x, uint8_t y);
void scroll_line();

#endif

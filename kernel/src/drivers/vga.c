#include <cpu/port.h>
#include <driver/vga.h>


volatile vga_char *TEXT_AREA = (vga_char*) VGA_START;


uint8_t vga_color(const uint8_t fg_color, const uint8_t bg_color){
    // Put bg color in the higher 4 bits and mask those of fg
    return (bg_color << 4) | (fg_color & 0x0F);
}


void clearwin(uint8_t fg_color, uint8_t bg_color){
    const char space = ' ';
    uint8_t clear_color = vga_color(fg_color, bg_color);

    const vga_char clear_char = {
        .character = space,
        .style = clear_color
    };

    for(uint64_t i = 0; i < VGA_EXTENT; i++) {
        TEXT_AREA[i] = clear_char;
    }
}

uint16_t get_cursor_pos(){
    uint16_t position = 0;

    byte_out(CURSOR_PORT_COMMAND, 0x0F);
    position |= byte_in(CURSOR_PORT_DATA);

    byte_out(CURSOR_PORT_COMMAND, 0x0E);
    position |= byte_in(CURSOR_PORT_DATA) << 8;

    return position;
}

void putchar(const char character, const uint8_t fg_color, const uint8_t bg_color){
    if(character == '\n'){
        // In case of newline
        uint16_t position = get_cursor_pos();
        uint8_t x = position % VGA_WIDTH;
        uint8_t y = position / VGA_WIDTH;
        if(y >= VGA_HEIGHT-1){
            scroll_line();
        } else {
            set_cursor_pos(0, y+1);
        }
    }else if(character == '\r'){
        // In case of carriage return
        uint16_t position = get_cursor_pos();
        uint8_t x = position % VGA_WIDTH;
        uint8_t y = position / VGA_WIDTH;
        set_cursor_pos(0, y);
    }else if(character == '\t'){
        // In case of tab
        uint16_t position = get_cursor_pos();
        uint8_t x = position % VGA_WIDTH;
        uint8_t y = position / VGA_WIDTH;
        uint8_t spaces = 4 - (x % 4);
        for(uint8_t i = 0; i < spaces; i++){
            putchar(' ', fg_color, bg_color);
            advance_cursor();
        }
        // We use 4 spaces for a tab (because I liky thatty wayie)
    }else{
        // In case of normal character
        uint16_t position = get_cursor_pos();
        TEXT_AREA[position].character = character;
        TEXT_AREA[position].style = vga_color(fg_color, bg_color);
    }


    
    uint8_t style = vga_color(fg_color, bg_color);
    vga_char printed = {
        .character = character,
        .style = style
    };


    uint16_t position = get_cursor_pos();
    TEXT_AREA[position] = printed;
}


void putstr(const char *string, const uint8_t fg_color, const uint8_t bg_color){
    while (*string != '\0'){
        putchar(*string++, fg_color, bg_color);
        advance_cursor();
    }
}




void show_cursor(){
    uint8_t current;

    byte_out(CURSOR_PORT_COMMAND, 0x0A);
    current = byte_in(CURSOR_PORT_DATA);
    byte_out(CURSOR_PORT_DATA, current & 0xC0);

    byte_out(CURSOR_PORT_COMMAND, 0x0B);
    current = byte_in(CURSOR_PORT_DATA);
    byte_out(CURSOR_PORT_DATA, current & 0xE0);
}


void hide_cursor(){
    byte_out(CURSOR_PORT_COMMAND, 0x0A);
    byte_out(CURSOR_PORT_DATA, 0x20);
}


void advance_cursor(){
    uint16_t pos = get_cursor_pos();
    pos++;

    if (pos >= VGA_EXTENT){
        scroll_line();
    }

    byte_out(CURSOR_PORT_COMMAND, 0x0F);
    byte_out(CURSOR_PORT_DATA, (uint8_t) (pos & 0xFF));

    byte_out(CURSOR_PORT_COMMAND, 0x0E);
    byte_out(CURSOR_PORT_DATA, (uint8_t) ((pos >> 8) & 0xFF));
}


void set_cursor_pos(uint8_t x, uint8_t y){
    uint16_t pos = x + ((uint16_t) VGA_WIDTH * y);

    if (pos >= VGA_EXTENT){
        scroll_line();
    }

    byte_out(CURSOR_PORT_COMMAND, 0x0F);
    byte_out(CURSOR_PORT_DATA, (uint8_t) (pos & 0xFF));

    byte_out(CURSOR_PORT_COMMAND, 0x0E);
    byte_out(CURSOR_PORT_DATA, (uint8_t) ((pos >> 8) & 0xFF));
}

void scroll_line(){
    for(uint16_t i=0; i < VGA_HEIGHT; i++){
        for(uint16_t j=0; j < VGA_WIDTH-1; j++){
            uint16_t to_pos = j + ((i - 1) * VGA_WIDTH);
            uint16_t from_pos = j + (i * VGA_WIDTH);

            TEXT_AREA[to_pos] = TEXT_AREA[from_pos];
        }
    }

    // Clear the fimal row
    uint16_t i = VGA_HEIGHT - 1;
    for (uint16_t j = 0; j < VGA_WIDTH; j++){
        uint16_t pos = j + (i * VGA_WIDTH);

        vga_char current = TEXT_AREA[pos];
        vga_char clear_char = {
            .character = ' ',
            .style = current.style
        };

        TEXT_AREA[pos] = clear_char;
        set_cursor_pos(0, VGA_HEIGHT - 1);
    }
    
}
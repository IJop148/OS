// Code from page 68 of lecture 
// https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
// straight copy paste shenanigans
#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H

unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);

#endif // LOW_LEVEL_H

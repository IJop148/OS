// Code from page 68 of lecture 
// https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
// straight copy paste shenanigans
#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H

unsigned char byte_in(unsigned short port);
void byte_out(unsigned short port, unsigned char data);

#endif // LOW_LEVEL_H

// file: basic_function.h
// This file contains a set of basic functions that are used in the kernel
// like memory_copy, memory_set, etc.

#include "types.h"

#ifndef BASIC_FUNCTION_H
#define BASIC_FUNCTION_H

// Function definitions
void memcopy(u8int *source, u8int *dest, int no_bytes);
void memset(u8int *dest, u8int val, int len);

#endif // BASIC_FUNCTION_H

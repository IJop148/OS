#include "basic_function.h"

void memset(u8int *dest, u8int val, int len) {
    for (int i = 0; i < len; i++) {
        dest[i] = val;
    }
}

void memcopy(u8int *source, u8int *dest, int no_bytes) {
    for (int i = 0; i < no_bytes; i++) {
        dest[i] = source[i];
    }
}
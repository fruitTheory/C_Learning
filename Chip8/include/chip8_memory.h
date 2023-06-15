#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

#include "config.h"


// this is the memory we have and the size of it
struct chip8_memory
{
    unsigned char memory[CHIP8_MEMORY_SIZE];
};

// fucntions for talking with memory, setting memory, etc
void chip8_memory_set(struct chip8_memory* memory, int index, unsigned char val);
unsigned char chip8_memory_get(struct chip8_memory* memory, int index);

#endif
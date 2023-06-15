#ifndef CHIP8_H
#define CHIP8_H

#include "config.h"
#include "chip8_memory.h"
#include "chip8_registers.h"
#include "chip8_stack.h"

// This is our comptuer struct 
struct chip8
{   
    // and we have..
    struct chip8_memory memory;
    struct chip8_registers registers;
    struct chip8_stack stack;
    
};

#endif
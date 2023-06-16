#include "chip8.h"
#include "chip8_stack.h"
#include <assert.h>

// Functions for the stack
static void chip8_stack_inbounds(struct chip8* chip8){

    assert(chip8->registers.SP < CHIP8_TOTAL_STACK_DEPTH);
}

void chip8_stack_push(struct chip8* chip8, unsigned short val){

    chip8_stack_inbounds(chip8);
    chip8->stack.stack[chip8->registers.SP] = val;
    chip8->registers.SP +=1;


}

unsigned short chip8_stack_pop(struct chip8* chip8){
    
    chip8->registers.SP -= 1;
    chip8_stack_inbounds(chip8);
    unsigned short val = chip8->stack.stack[chip8->registers.SP];
    return val;
}
#include "chip8.h"
#include <memory.h>


//init is basically setting total memory available/needed
void chip8_init(struct chip8* chip8){
    memset(chip8, 0, sizeof(struct chip8));
}
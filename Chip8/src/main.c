#include <stdio.h>
#include "SDL2/SDL.h"
#include "chip8.h"


int main(int argc, char** argv){

    // declare variable of type struct chip8
    struct chip8 chip8;

    // Store value in hex slot 15[Fh] of array and print that out
    chip8.registers.V[0xF] = 25;
    printf("%i\n", chip8.registers.V[0xF]);

    // Example of setting memory and getting from memory
    chip8_memory_set(&chip8.memory, 0x69, 'B');
    // Get from memory location 105 which is equal to hex 0x69
    printf("%c\n", chip8_memory_get(&chip8.memory, 105));


    // init SDL and others vars
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(
        EMULATOR_WINDOW_TITLE, 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        CHIP8_WIDTH * CHIP8_WINDOW_MULT,
        CHIP8_HEIGHT * CHIP8_WINDOW_MULT,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);
    SDL_Event event;
    while(1){
        while ((SDL_PollEvent(&event)))
        {
            if(event.type == SDL_QUIT){
                goto out;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 25, 25, 255);
        SDL_RenderClear(renderer); // clears entire rendering target

        SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255); // color for rect

        // create rectangle 
        SDL_Rect r;
        r.x = 0; r.y = 0; r.w = 40; r.h = 40;

        // fill rect with current target draw color
        SDL_RenderFillRect(renderer, &r);
        SDL_RenderPresent(renderer); // present the renderer
    }

out:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
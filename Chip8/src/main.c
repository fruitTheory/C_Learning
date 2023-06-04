#include <stdio.h>
#include "SDL2/SDL.h"
#include "chip8.h"

int main(int argc, char** argv){

    struct chip8 chip8;
    chip8_memory_set(&chip8.memory, 0x69, 'A');
    printf("%c\n", chip8_memory_get(&chip8.memory, 50));

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(
        EMULATOR_WINDOW_TITLE, 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        CHIP8_WIDTH * CHIP8_WINDOW_MULT,
        CHIP8_HEIGHT * CHIP8_WINDOW_MULT,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

    while(1){
        SDL_Event event;
        while ((SDL_PollEvent(&event)))
        {
            if(event.type == SDL_QUIT){
                goto out;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear;
        SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = 40;
        r.h = 40;
        //SDL_RenderDrawRect(renderer, &r);
        SDL_RenderFillRect(renderer, &r);
        SDL_RenderPresent(renderer);
    }

    //printf("Hello World!\n");
out:    
    SDL_DestroyWindow(window);
    
    return 0;
}
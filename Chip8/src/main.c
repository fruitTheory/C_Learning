#include <stdio.h>
#include "SDL2/SDL.h"
#include "chip8.h"
#include "chip8_keyboard.h"


const char keyboard_map[CHIP8_TOTAL_KEYS] = {
    SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, 
    SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_a, SDLK_b,
    SDLK_c, SDLK_d, SDLK_e, SDLK_f
};

void testing();

int main(int argc, char* argv[]){

    // declare variable of type struct chip8
    struct chip8 chip8;

    testing();

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
                switch(event.type){

                case SDL_QUIT:
                    // if case quit exit program
                    goto out;

                case SDL_KEYDOWN:{
                    // event get key
                    char key = event.key.keysym.sym;

                    // map keys to virtual keys 
                    int vkey = chip8_keyboard_map(keyboard_map, key);
                    printf("key down: %x\n", vkey);

                    // should return a key if -1 is not returned
                    if(vkey != -1){
                        chip8_keyboard_down(&chip8.keyboard, vkey);
                    }
                    }
                break;

                case SDL_KEYUP:{
                    // event get key
                    char key = event.key.keysym.sym;

                    // map keys to virtual keys 
                    int vkey = chip8_keyboard_map(keyboard_map, key);
                    printf("key up\n");

                    // should return a key if -1 is not returned
                    if(vkey != -1){
                        chip8_keyboard_up(&chip8.keyboard, vkey);
                    }
                    }
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


void testing(){

    /*
    *********************************************
    * Section for old tests and comments
    *********************************************
    */

    // declare variable of type struct chip8
    struct chip8 chip8;

    // Store value in hex slot 15[Fh] of array and print that out
    chip8.registers.V[0xF] = 25;
    printf("%i\n", chip8.registers.V[0xF]);

    // Example of setting memory and getting from memory
    chip8_memory_set(&chip8.memory, 0x69, 'B');
    // Get from memory location 105 which is equal to hex 0x69
    printf("%c\n", chip8_memory_get(&chip8.memory, 105));

    // check definition
    printf("%X\n", chip8_keyboard_map(keyboard_map, 10));

    chip8_keyboard_down(&chip8.keyboard, 0xf);// key is up = true
    //chip8_keyboard_up(&chip8.keyboard, 0xf); // key is up = false

    bool is_down = chip8_keyboard_is_down(&chip8.keyboard, 0xf);
    printf("%i\n", is_down); // cast to int

    // setting stack point to 0 and pushing to the stack
    chip8.registers.SP = 0;
    chip8_stack_push(&chip8, 0xff);
    chip8_stack_push(&chip8, 0xaa);

    // pop off the stack, note that once its gone its set to 0 
    printf("%x - %i\n", chip8_stack_pop(&chip8));
    printf("%i - %x\n", chip8_stack_pop(&chip8));

}
#include <stdio.h>
#include <windows.h>
#include "SDL2/SDL.h"
#include "chip8.h"
#include "chip8_keyboard.h"
#include "chip8_screen.h"


// map characters to keyboard array
const char keyboard_map[CHIP8_TOTAL_KEYS] = {
    SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, 
    SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_a, SDLK_b,
    SDLK_c, SDLK_d, SDLK_e, SDLK_f
};

void testing();

int main(int argc, char* argv[]){


    /*-----------------------
        Load Chip8 File
    -----------------------*/

    if(argc < 2){
        printf("You must provide a file to load\n");
        return -1;
    }

    const char* filename = argv[1];
    printf("Filename loaded is: %s\n", filename);

    FILE* f = fopen(filename, "rb");
    if (!f){
        printf("Failed to open file");
        return -1;
    }
    
    // seek end of file
    fseek(f, 0, SEEK_END);
    // ftell gives current position, since we're at end of file can rep the size
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char buf[size];
    // read as one chunk
    int res = fread(buf, size, 1, f);

    if(res != 1){
        printf("Failed to read from file\n");
        return -1;
    }

    /*--------------------
        Initialize
    --------------------*/

    // initialize the computer variable
    struct chip8 chip8;

    // initialize the needed memory of computer
    chip8_init(&chip8);
    
    // load binary
    chip8_load(&chip8, buf, size);\

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

    /*--------------------
        Run Functions
    --------------------*/
    


    /*----------------------------
        Run program loop
    ----------------------------*/

    bool program_is_running = true;
    while(program_is_running){
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
                    int vkey = chip8_keyboard_map(&chip8.keyboard, key);
                    //printf("key down: %x\n", vkey);

                    // should return a key if -1 is not returned
                    if(vkey != -1){
                        chip8_keyboard_down(&chip8.keyboard, vkey);
                        printf("key down: %x\n", vkey);
                    }
                }
                break;

                case SDL_KEYUP:{
                    // event virtual key
                    char key = event.key.keysym.sym;
                    //printf("virtual key: %i\n", key);

                    // event physical key
                    int pkey = event.key.keysym.scancode;
                    //printf("physical key: %i\n", pkey);

                    // map keys to virtual keys 
                    int vkey = chip8_keyboard_map(&chip8.keyboard, key);
                    //printf("key up: %i\n", vkey);

                    // should return a key if -1 is not returned
                    if(vkey != -1){
                        chip8_keyboard_up(&chip8.keyboard, vkey);
                        printf("key up: %i\n", vkey);
                    }
                }
            }
        }


    /*----------------------------
        Setup pixel and color
    ----------------------------*/

        SDL_SetRenderDrawColor(renderer, 0, 25, 25, 255); // color for background
        SDL_RenderClear(renderer); // clears entire rendering target
        SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255); // color for rect/pixel

        for(int x = 0; x < CHIP8_WIDTH; x++){
            for(int y = 0; y < CHIP8_HEIGHT; y++){
                if (chip8_screen_is_set(&chip8.screen, x, y)){
                    // create rectangle as a pixel
                    SDL_Rect r;
                    r.x = x * CHIP8_WINDOW_MULT; // compensate for difference in x
                    r.y = y * CHIP8_WINDOW_MULT; // compensate for difference in y
                    r.w = CHIP8_WINDOW_MULT; // multiply width by 10
                    r.h = CHIP8_WINDOW_MULT; // multiply height by 10
                    
                    // r.x = 0; r.y = 0; r.w = 40; r.h = 40; // original rect

                    // fill rect with current target draw color
                    SDL_RenderFillRect(renderer, &r);

                }
            }
        }

        SDL_RenderPresent(renderer); // present the renderer


    /*----------------------------
        Delays and Instructions
    ----------------------------*/

        // small delay if delay timer is above zero
        if (chip8.registers.delay_timer > 0){
            Sleep(100);
            chip8.registers.delay_timer -= 1;
            printf("Delay\n");
        }

        // small delay if delay timer is above zero
        if (chip8.registers.sound_timer > 0){
            Beep(12000, 100 * chip8.registers.sound_timer);
            chip8.registers.sound_timer = 0;
        }
        
        unsigned short opcode = chip8_memory_get_short(&chip8.memory, chip8.registers.PC);
        if(chip8.registers.PC < CHIP8_MEMORY_SIZE){
            chip8.registers.PC += 2;
        }
        chip8_exec(&chip8, opcode);
        // move program counter 2 bytes since opcodes are 2 bytes

        
    }




    /*----------------------------
        Clean memory
    ----------------------------*/
out:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}


void testing(){

    /*--------------------------------------------------------
        Section for testing and storing old code
    --------------------------------------------------------*/

    // declare variable of type struct chip8
    struct chip8 chip8;


    // draw sprite from character set 0 - 5 - 10 
    chip8_screen_draw_sprite(&chip8.screen, 5, 5, &chip8.memory.memory[0xF], CHIP8_DEFAULT_SPRITE_SIZE);
    
    // check keyboard implementation
    chip8_keyboard_set_map(&chip8.keyboard, keyboard_map);
    chip8.registers.V[0] = 0x00;
    chip8_exec(&chip8, 0xF00A);
    printf("%x\n", chip8.registers.V[0]);

    // exec some shizz
    chip8.registers.V[0] = 0x20;
    chip8.registers.V[1] = 0x30;
    chip8_exec(&chip8, 0x8010);
    printf("%x\n", chip8.registers.V[0]);

    chip8.registers.V[0] = 200;
    chip8.registers.V[1] = 50;
    chip8_exec(&chip8, 0x8014);
    printf("%i\n", chip8.registers.V[0]);
    printf("%i\n", chip8.registers.V[0x0f]);

    chip8.registers.I = 0x00;
    chip8.registers.V[0] = 10;
    chip8.registers.V[1] = 10;
    chip8_exec(&chip8, 0xD015);


    // Below few lines are instruction 3xkk test
    chip8.registers.PC = 0x00;
    chip8.registers.V[0x00] = 0x22;
    // 3xkk skip if Vx = kk
    chip8_exec(&chip8, 0x3021);
    // will program count skip [return 2]
    printf("%x\n", chip8.registers.PC);

    // execute some opcode [return from subroutine]
    //chip8_exec(&chip8, 0x00E0);

    // set pixel x and y on screen
    //chip8_screen_set(&chip8.screen, 0, 0);

    // set delay timer amount
    //chip8.registers.delay_timer = 20;

    // set sound timer amount
    //chip8.registers.sound_timer = 50;

    // Store value in hex slot 15[Fh] of array and print that out
    chip8.registers.V[0xF] = 25;
    printf("%i\n", chip8.registers.V[0xF]);

    // Example of setting memory and getting from memory
    chip8_memory_set(&chip8.memory, 0x69, 'B');
    // Get from memory location 105 which is equal to hex 0x69
    printf("%c\n", chip8_memory_get(&chip8.memory, 105));

    // check definition
    //printf("%X\n", chip8_keyboard_map(keyboard_map, 10));

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
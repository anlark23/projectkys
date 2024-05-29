
#include "types.h"
#include "gdt.h"
#include "interrupts.h"

void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0 , y=0;

    for(int i = 0; str[i] != '\0'; ++i){

        switch(str[i]){
            case '\n': // new line protocal for \n
                y++;
                x=0;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++; //80 is the width of the screen 25 is the length
                break;
        }

        if (x >= 80){
            y++; //new line
            x=0;
        }
        if (y >= 25){ //clears the screen if y exceeds the length
            for(y=0; y < 25; y++){//this loop goes through everything and sets it to empty space char
                for(x=0; x<80; x++){
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';

                }
                x = 0;
                y = 0;
            }

        }

    }

}

typedef void (*constructor)(); //we are defining linker variables in .cpp
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors(){ //called in loader.s
    for(constructor* i = &start_ctors; i != &end_ctors; i++) //The nitwit forgot & in end_ctors
        (*i)();
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t)
{
    printf("Hello World!\n");
    printf("I love you, cold unfeeling robot arm!");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);

    interrupts.Activate();


    while(1);

}

#include <cstdint>
#include "device.h"

void device::cls(){
    for(int i = 0; i < screen_height; i ++){
        for(int j = 0; j < screen_length; j ++){
            device::memory_map[(i * screen_length) + j] = 0;        
        }
    }
}

device::device(uint8_t x, uint8_t y)
    : screen_height(y)
    , screen_length(x){
    memory_map = new uint16_t[memory_size];
    program_counter = memory_map;
    stack_pointer = new uint16_t[stack_size];
    keypad_map = new bool[keypad_size];
    screen_map = new bool[screen_height * screen_length];

    delay_timer = 0;
    sound_timer = 0;
}

device::~device(){
    delete [] memory_map;
    delete [] keypad_map;
    delete [] screen_map;
    delete program_counter;
}
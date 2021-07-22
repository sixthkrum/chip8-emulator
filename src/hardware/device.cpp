#include <cstdint>
#include "device.h"
#include "instructions.h"

void device::cls(){
    for(int i = 0; i < screen_height; i ++){
        for(int j = 0; j < screen_length; j ++){
            device::screen_map[(i * screen_length) + j] = 0;        
        }
    }
}

uint8_t device::keypress_read(){
    // Implement with imgui
    return 1;
}

device::device(uint16_t screen_y_max, uint16_t screen_x_max, uint8_t keypad_size_)
    : screen_height(screen_y_max)
    , screen_length(screen_x_max)
    , keypad_size(keypad_size_)
    , chip8_instruction_set(screen_y_max, screen_x_max, keypad_size_){
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
#include <cstdint>
#include "instructions.h"

#ifndef DEVICE_H
#define DEVICE_H

class device : public chip8_instruction_set{
    private:
    const uint8_t memory_size = 4096; // Bytes
    const uint8_t stack_size = 16; // Words
    const uint8_t keypad_size; // Keys, default 16
    const uint16_t screen_height; // Pixels, default 32
    const uint16_t screen_length; // Pixels, default 64
    
    public:
    uint8_t *memory_map;
    // program_counter is a pointer to the current executing instruction
    // it is not changed by the instruction set and will be set by the control functions in main.cpp
    // it will be set according to where the program_counter_index points to in the memory map in chip8_instruction_set
    uint16_t *program_counter;
    uint16_t *stack_pointer;
    
    bool *keypad_map;
    bool *screen_map;
    
    uint8_t delay_timer;
    uint8_t sound_timer;
    
    void cls();
    uint8_t keypress_read();

    device(uint16_t, uint16_t, uint8_t);
    ~device();  
};

#endif
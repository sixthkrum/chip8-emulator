#include <cstdint>
#include "instructions.h"

#ifndef DEVICE_H
#define DEVICE_H

class device : public chip8_instruction_set{
    private:
    const uint16_t memory_size = 2048; // Words
    const uint8_t stack_size = 16; // Words
    const uint8_t keypad_size; // Keys, default 16
    const uint16_t screen_height; // Pixels, default 32
    const uint16_t screen_length; // Pixels, default 64
    
    public:
    uint16_t *memory_map;
    uint16_t *program_counter;
    uint16_t *stack_pointer;
    bool *keypad_map;
    bool *screen_map;
    uint8_t delay_timer;
    uint8_t sound_timer;
    
    void cls();
    device(uint16_t, uint16_t, uint8_t);
    ~device();  
};

#endif
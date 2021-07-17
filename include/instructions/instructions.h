#include <cstdint>

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

class chip8_instruction_set{
    private:
    uint16_t *memory_map;
    uint16_t *program_counter;
    uint16_t *stack_pointer;

    uint16_t memory_map_index; // Index of device's memory map
    uint16_t program_counter_index; // Index of device's program counter array
    
    uint8_t stack_pointer_index; // Index of device's stack pointer array
    uint8_t min_stack_pointer_index = 0;
    uint8_t max_stack_pointer_index;

    bool *keypad_map;
    bool *screen_map;

    uint8_t delay_timer;
    uint8_t sound_timer;
    
    public:
    // Clears screen
    void cls(); // A device must provide its own implementation of this function
    
    // Returns to the address at the top of the stack
    void ret();
    
    // Jumps to 3 nibble address
    void jp();

    // Calls instruction at 3 nibble address
    void call();
};

#endif
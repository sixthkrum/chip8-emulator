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
    const uint8_t min_stack_pointer_index = 0;
    const uint8_t max_stack_pointer_index = 16;

    bool *keypad_map;
    const uint8_t keypad_size;

    bool *screen_map;
    const uint16_t screen_height;
    const uint16_t screen_length; 
    
    uint8_t delay_timer;
    uint8_t sound_timer;

    static constexpr uint8_t num_registers_8bit = 16;    
    uint8_t *registers_8bit;

    uint16_t *register_16bit;

    uint8_t instruction_lhs; // LHS of operation for current instruction
    uint8_t instruction_rhs; // RHS of operation for current instruction
    uint16_t instruction_3n_2b; // Value of any number that is 3 nibbles or 2 bytes long in an instruction 

    public:
    chip8_instruction_set(uint16_t, uint16_t, uint8_t);
    ~chip8_instruction_set();

    // Blocking read of a keypress
    virtual uint8_t keypress_read(); // A device must provide its own implementation of this function

    // Clears screen
    virtual void cls(); // A device must provide its own implementation of this function
    
    // Returns to the address at the top of the stack
    void ret();
    
    // Jumps to 3 nibble address
    void jp();

    // Calls instruction at 3 nibble address
    void call();

    // Skips next instruction if Vx register's value is equal to given byte
    void sevxb();

    // Skips next instruction if Vx register's value is not equal to given byte
    void snevxb();

    // Skips next instruction if Vx and Vy registers' values are equal
    void sevxvy();

    // Skips next instruction if Vx and Vy registers' values are not equal
    void snevxvy();

    // Skips next instruction if key with value Vx is pressed
    void skp();

    // Skips next instruction if key with value Vx is not pressed
    void sknp();
    
    // Puts value of byte into Vx
    void ldvxb();

    // Puts value of Vy into Vx
    void ldvxvy();

    // Adds value of Vx and byte and puts it into Vx
    void addvxb();

    // Adds value of Vx and Vy and puts it into Vx
    void addvxvy();

    // Adds value of I and Vx and puts it into I
    void addivx();

    // Performs 'or' operation between Vx and Vy and puts it into Vx
    void orvxvy();

    // Performs 'and' operation between Vx and Vy and puts it into Vx
    void andvxvy();

    // Performs 'xor' operation between Vx and Vy and puts it into Vx
    void xorvxvy();
    
    // Subtracts value of Vy from Vx and puts it into Vx
    void subvxvy();

    // Subtracts value of Vx from Vy and puts it into Vx
    void subnvxvy();

    // Sets Vx to Vy >> 1 and stores LSB in VF
    void shrvxvy();

    // Sets Vx to Vy << 1 and stores MSB in VF
    void shlvxvy();

    // Sets value of I to 3 nibble address
    void ldia();

    // Jumps to address (3 nibble + V0)
    void jpav0();
    
    // Puts the value of delay timer into Vx
    void ldvxdt();

    // Puts the value of Vx into delay timer
    void lddtvx();

    // Wait for a key press and store the value of the key in Vx
    void ldvxk(); // A device must provide its own implementation of blocking keypress reads 
};

#endif
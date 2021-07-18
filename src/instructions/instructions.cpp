#include <cstdint>

#include "instructions.h"
#include "common.h"

chip8_instruction_set::chip8_instruction_set(uint16_t screen_y_max, uint16_t screen_x_max, uint8_t keypad_size_)
    : screen_height(screen_y_max)
    , screen_length(screen_x_max)
    , keypad_size(keypad_size_){
    registers_8bit = new uint8_t[num_registers_8bit];
    register_16bit = new uint16_t;
}

chip8_instruction_set::~chip8_instruction_set(){
    delete [] registers_8bit;
    delete register_16bit;
}

void chip8_instruction_set::ret(){
    if(stack_pointer_index != min_stack_pointer_index){
        program_counter_index = stack_pointer[stack_pointer_index];
        stack_pointer_index --;
    }
}

void chip8_instruction_set::jp(){
    program_counter_index = extract_address(program_counter[program_counter_index]);
}

void chip8_instruction_set::call(){
    if(stack_pointer_index != min_stack_pointer_index){
        stack_pointer[++ stack_pointer_index] = program_counter_index;
        program_counter_index = extract_address(program_counter[program_counter_index]);
    }
}

void chip8_instruction_set::sevxb(){
    auto [instruction_lhs, instruction_rhs] = extract_xb(program_counter[program_counter_index]);
    
    if(registers_8bit[instruction_lhs] == instruction_rhs){
        program_counter_index ++;
    }

    program_counter_index ++;
}

void chip8_instruction_set::snevxb(){
    auto [instruction_lhs, instruction_rhs] = extract_xb(program_counter[program_counter_index]);

    if(registers_8bit[instruction_lhs] != instruction_rhs){
        program_counter_index ++;
    }

    program_counter_index ++;
}

void::chip8_instruction_set::sevxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(program_counter[program_counter_index]);

    if(registers_8bit[instruction_lhs] == registers_8bit[instruction_rhs]){
        program_counter_index ++;
    }

    program_counter_index ++;
}

void::chip8_instruction_set::snevxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(program_counter[program_counter_index]);

    if(registers_8bit[instruction_lhs] != registers_8bit[instruction_rhs]){
        program_counter_index ++;
    }

    program_counter_index ++;
}

void::chip8_instruction_set::skp(){
    instruction_lhs = extract_x(program_counter[program_counter_index]);

    // Registers always have positive non zero values
    if(registers_8bit[instruction_lhs] < keypad_size){
        if(keypad_map[registers_8bit[instruction_lhs]] == 1){
            program_counter_index ++;
        }
    }

    program_counter_index ++;
}

void::chip8_instruction_set::sknp(){
    instruction_lhs = extract_x(program_counter[program_counter_index]);
    
    // Registers always have positive non zero values
    if(registers_8bit[instruction_lhs] < keypad_size){
        if(keypad_map[registers_8bit[instruction_lhs]] != 1){
            program_counter_index ++;
        }
    }

    program_counter_index ++;
}
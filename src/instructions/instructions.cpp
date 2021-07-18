#include <cstdint>

#include "instructions.h"
#include "common.h"

chip8_instruction_set::chip8_instruction_set(){
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
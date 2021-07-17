#include <cstdint>
#include <bitset>
#include "instructions.h"

void chip8_instruction_set::ret(){
    if(stack_pointer_index != min_stack_pointer_index){
        program_counter_index = stack_pointer[stack_pointer_index];
        stack_pointer_index --;
    }
}

void chip8_instruction_set::jp(){
    program_counter_index = std::bitset<12>(program_counter[program_counter_index]).to_ulong();
}

void chip8_instruction_set::call(){
    if(stack_pointer_index != min_stack_pointer_index){
        stack_pointer[++ stack_pointer_index] = program_counter_index;
        program_counter_index = std::bitset<12>(program_counter[program_counter_index]).to_ulong();
    }
}
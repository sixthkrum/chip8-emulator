#include <cstdint>
#include <bitset>

#include "instructions.h"
#include "common.h"

chip8_instruction_set::chip8_instruction_set(uint16_t screen_y_max, uint16_t screen_x_max, uint8_t keypad_size_)
    : screen_height(screen_y_max)
    , screen_length(screen_x_max)
    , keypad_size(keypad_size_){
    registers_8bit = new uint8_t[num_registers_8bit];
    register_16bit = new uint16_t;
    set_memory_number_sprites();
}

chip8_instruction_set::~chip8_instruction_set(){
    delete [] registers_8bit;
    delete register_16bit;
}

void chip8_instruction_set::set_memory_number_sprites(){
    // contains the hex code only
    uint8_t temp_num_codes[0x50] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for(int i = 0; i < 0x50 ; i ++){
        memory_map[i] = temp_num_codes[i];
    }
}

uint8_t chip8_instruction_set::keypress_read(){
    return 0;
}

void chip8_instruction_set::cls(){}

void chip8_instruction_set::ret(){
    if(stack_pointer_index != min_stack_pointer_index){
        program_counter_index = stack_pointer[stack_pointer_index];
        stack_pointer_index --;
    }
}

void chip8_instruction_set::jp(){
    program_counter_index = extract_address(*program_counter);
}

void chip8_instruction_set::call(){
    if(stack_pointer_index != min_stack_pointer_index){
        stack_pointer[++ stack_pointer_index] = program_counter_index;
        program_counter_index = extract_address(*program_counter);
    }
}

void chip8_instruction_set::sevxb(){
    auto [instruction_lhs, instruction_rhs] = extract_xb(*program_counter);
    
    if(registers_8bit[instruction_lhs] == instruction_rhs){
        program_counter_index ++;
    }

    program_counter_index ++;
}

void chip8_instruction_set::snevxb(){
    auto [instruction_lhs, instruction_rhs] = extract_xb(*program_counter);

    if(registers_8bit[instruction_lhs] != instruction_rhs){
        program_counter_index ++;
    }

    program_counter_index ++;
}

void::chip8_instruction_set::sevxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);

    if(registers_8bit[instruction_lhs] == registers_8bit[instruction_rhs]){
        program_counter_index ++;
    }

    program_counter_index ++;
}

void::chip8_instruction_set::snevxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);

    if(registers_8bit[instruction_lhs] != registers_8bit[instruction_rhs]){
        program_counter_index ++;
    }
        
    program_counter_index ++;
}

void::chip8_instruction_set::skp(){
    instruction_lhs = extract_x(*program_counter);

    // Registers always have positive non zero values
    if(registers_8bit[instruction_lhs] < keypad_size){
        if(keypad_map[registers_8bit[instruction_lhs]] == 1){
            program_counter_index ++;
        }
    }
            
    program_counter_index ++;
}

void::chip8_instruction_set::sknp(){
    instruction_lhs = extract_x(*program_counter);
    
    // Registers always have positive non zero values
    if(registers_8bit[instruction_lhs] < keypad_size){
        if(keypad_map[registers_8bit[instruction_lhs]] != 1){
            program_counter_index ++;
        }
    }
            
    program_counter_index ++;
}

void chip8_instruction_set::ldvxb(){
    auto [instruction_lhs, instruction_rhs] = extract_xb(*program_counter);
    registers_8bit[instruction_lhs] = instruction_rhs;
            
    program_counter_index ++;
}

void chip8_instruction_set::ldvxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);
    registers_8bit[instruction_lhs] = registers_8bit[instruction_rhs];
            
    program_counter_index ++;
}

void chip8_instruction_set::addvxb(){
    auto [instruction_lhs, instruction_rhs] = extract_xb(*program_counter);
    registers_8bit[instruction_lhs] += instruction_rhs;
            
    program_counter_index ++;
}

void chip8_instruction_set::addvxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);
    uint8_t temp = registers_8bit[instruction_lhs];
    registers_8bit[instruction_lhs] += registers_8bit[instruction_rhs];

    if(temp > registers_8bit[instruction_lhs]){
        registers_8bit[num_registers_8bit - 1] = 1;
    }
            
    program_counter_index ++;
}

void chip8_instruction_set::addivx(){
    instruction_lhs = extract_x(*program_counter);
    *register_16bit += registers_8bit[instruction_lhs];

    program_counter_index ++;
}

void chip8_instruction_set::orvxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);
    registers_8bit[instruction_lhs] |= registers_8bit[instruction_rhs];

    program_counter_index ++;
}

void chip8_instruction_set::andvxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);
    registers_8bit[instruction_lhs] &= registers_8bit[instruction_rhs];
        
    program_counter_index ++;
}

void chip8_instruction_set::xorvxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);
    registers_8bit[instruction_lhs] ^= registers_8bit[instruction_rhs];
        
    program_counter_index ++;
}

void chip8_instruction_set::subvxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);

    if(registers_8bit[instruction_lhs] > registers_8bit[instruction_rhs]){
        registers_8bit[num_registers_8bit - 1] = 1;
    }

    registers_8bit[instruction_lhs] -= registers_8bit[instruction_rhs];
            
    program_counter_index ++;
}

void chip8_instruction_set::subnvxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);

    if(registers_8bit[instruction_lhs] < registers_8bit[instruction_rhs]){
        registers_8bit[num_registers_8bit - 1] = 1;
    }

    registers_8bit[instruction_lhs] = registers_8bit[instruction_rhs] - registers_8bit[instruction_lhs];
            
    program_counter_index ++;
}

void chip8_instruction_set::shrvxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);
    
    if((registers_8bit[instruction_rhs] & 0b00000001) == 1){
        registers_8bit[num_registers_8bit - 1] = 1;
    }

    registers_8bit[instruction_lhs] = registers_8bit[instruction_rhs] >> 1;
            
    program_counter_index ++;
}

void chip8_instruction_set::shlvxvy(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);
    
    if((registers_8bit[instruction_rhs] & 0b10000000) == 0b10000000){
        registers_8bit[num_registers_8bit - 1] = 1;
    }

    registers_8bit[instruction_lhs] = registers_8bit[instruction_rhs] << 1;
            
    program_counter_index ++;
}

void chip8_instruction_set::ldia(){
    *register_16bit = extract_address(*program_counter);
            
    program_counter_index ++;
}

void chip8_instruction_set::jpav0(){
    program_counter_index = extract_address(*program_counter) + registers_8bit[0];
}

void chip8_instruction_set::rndvxb(){
    auto [instruction_lhs, instruction_rhs] = extract_xb(*program_counter);
    registers_8bit[instruction_lhs] = random_8bit() & instruction_rhs;

    program_counter_index ++;    
}

void chip8_instruction_set::drwvxn(){
    auto [instruction_lhs, instruction_rhs] = extract_xy(*program_counter);
    instruction_lhs = registers_8bit[instruction_lhs];
    instruction_rhs = registers_8bit[instruction_rhs];

    uint8_t num_bytes = extract_n(*program_counter);

    instruction_3n_2b = *register_16bit;

    auto position_lambda = [instruction_lhs, instruction_rhs, this](uint16_t i, uint16_t j){
        return ((((instruction_rhs + i) % screen_height) * screen_length) + ((instruction_lhs + j) % screen_length));
    };

    for(uint8_t i = 0; i < num_bytes; i ++){
        instruction_3n_2b += i;
        std::bitset<8> current_byte = std::bitset<8>(memory_map[instruction_3n_2b]);    

        for(uint8_t j = 0; j < 8; j ++){
            uint16_t temp_position = position_lambda(i, j);
            bool temp_pixel_original = screen_map[temp_position];
            bool temp_pixel_new = current_byte[j];

            // Setting VF if the XORing erases some pixel
            if(temp_pixel_original == 1 && temp_pixel_new == 1){
                registers_8bit[num_registers_8bit - 1] = 1;
            }

            screen_map[temp_position] = temp_pixel_original ^ temp_pixel_new;
        }
    }

    program_counter_index ++;    
}

void chip8_instruction_set::ldvxdt(){
    instruction_lhs = extract_x(*program_counter);
    registers_8bit[instruction_lhs] =  delay_timer;

    program_counter_index ++;
}

void chip8_instruction_set::lddtvx(){
    instruction_lhs = extract_x(*program_counter);
    delay_timer = registers_8bit[instruction_lhs];

    program_counter_index ++;
}

void chip8_instruction_set::ldvxk(){
    instruction_lhs = extract_x(*program_counter);
    registers_8bit[instruction_lhs] = keypress_read();

    program_counter_index ++;
}

void chip8_instruction_set::ldstvx(){
    instruction_lhs = extract_x(*program_counter);
    sound_timer = registers_8bit[instruction_lhs];

    program_counter_index ++;
}

void chip8_instruction_set::ldfvx(){
    instruction_lhs = extract_x(*program_counter);
    *register_16bit = instruction_lhs * 5 + sprite_start_position; // 5 width sprites

    program_counter_index ++;
}

void chip8_instruction_set::ldbvx(){
    instruction_lhs = extract_x(*program_counter);
    instruction_lhs = registers_8bit[instruction_lhs];

    for(int i = 0; i < 3; i ++){
        memory_map[*register_16bit + i] = instruction_lhs % (10 * (3 - i));   
    }

    program_counter_index ++;
}

void chip8_instruction_set::ldivx(){
    instruction_lhs = extract_x(*program_counter);

    for(int i = 0; i <= instruction_lhs; i ++){
        memory_map[*register_16bit + i] = registers_8bit[i];
    }
    
    program_counter_index ++;
}

void chip8_instruction_set::ldvxi(){
    instruction_lhs = extract_x(*program_counter);

    for(int i = 0; i <= instruction_lhs; i ++){
        registers_8bit[i] = memory_map[*register_16bit + i];
    }

    program_counter_index ++;
}
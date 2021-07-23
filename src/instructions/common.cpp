#include <tuple>
#include <bit>
#include <bitset>
#include <random>
#include "common.h"

uint16_t extract_address(uint16_t instruction){
    return std::bitset<12>(instruction).to_ulong();
}

std::tuple<uint8_t, uint8_t> extract_xb(uint16_t instruction){
    return std::tuple<uint8_t, uint8_t>{
        std::bitset<8>(instruction).to_ulong()
    ,   std::bitset<4>(std::rotr(instruction, 8)).to_ulong()
    };
}

std::tuple<uint8_t, uint8_t> extract_xy(uint16_t instruction){
    return std::tuple<uint8_t, uint8_t>{
        std::bitset<4>(std::rotr(instruction, 4)).to_ulong()
    ,   std::bitset<4>(std::rotr(instruction, 8)).to_ulong()
    };
}

uint8_t extract_x(uint16_t instruction){
    return uint8_t(std::bitset<4>(std::rotr(instruction, 8)).to_ulong());
}

uint8_t extract_n(uint16_t instruction){
    return uint8_t(std::bitset<4>(instruction).to_ulong());
}

uint8_t random_8bit(){
    std::random_device rd;
    std::mt19937 mt_generator(rd());
    std::uniform_int_distribution<uint8_t> dist(0); // 0 to max(intType), here uint8_t so 255

    return dist(mt_generator);
}
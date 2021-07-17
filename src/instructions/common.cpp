#include <tuple>
#include <bit>
#include <bitset>
#include "common.h"

uint16_t extract_address(uint16_t instruction){
    return std::bitset<12>(instruction).to_ulong();
}

std::tuple<uint8_t, uint8_t> extract_xb(uint16_t instruction){
    uint8_t b = std::bitset<8>(instruction).to_ulong();
    uint8_t x = std::bitset<4>(std::rotr(instruction, 8)).to_ulong();

    return std::tuple<uint8_t, uint8_t>{x, b};
}

std::tuple<uint8_t, uint8_t> extract_xy(uint16_t instruction){
    uint8_t y = std::bitset<4>(std::rotr(instruction, 4)).to_ulong();
    uint8_t x = std::bitset<4>(std::rotr(instruction, 8)).to_ulong();

    return std::tuple<uint8_t, uint8_t>{x, y};
}
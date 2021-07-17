#include <tuple>

#ifndef COMMON_H
#define COMMON_H

// Extract address from given instruction
uint16_t extract_address(uint16_t); 

// Extract a nibble and a byte from given instruction
std::tuple<uint8_t, uint8_t> extract_xb(uint16_t);

// Extract 2 nibbles from given instruction
std::tuple<uint8_t, uint8_t> extract_xy(uint16_t);

#endif
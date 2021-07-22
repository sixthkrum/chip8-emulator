#include <tuple>

#ifndef COMMON_H
#define COMMON_H

// Instructions have 4 nibbles, abcd
// ignored nibbles in instructions are X'd out

// Extract address from given instruction X abc
uint16_t extract_address(uint16_t); 

// Extract a nibble and a byte from given instruction X a bc
std::tuple<uint8_t, uint8_t> extract_xb(uint16_t);

// Extract 2 nibbles from given instruction X a b X
std::tuple<uint8_t, uint8_t> extract_xy(uint16_t);

// Extract a nibble from the given instruction X a X X
uint8_t extract_x(uint16_t);

// Generate a random 8 bit number
uint8_t random_8bit();

#endif
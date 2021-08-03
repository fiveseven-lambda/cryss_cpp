#ifndef INPUT_H
#define INPUT_H

#include <istream>
#include <string>
#include <cstddef>

#include "pos.h"

class Input {
    std::istream &source;
    std::size_t line, byte;
public:
    Input(std::istream &);
    std::pair<pos::Pos, int> peek(), get(std::string &);
    std::size_t get_line(), get_byte();
};

#endif
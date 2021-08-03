#ifndef INPUT_H
#define INPUT_H

#include <istream>
#include <string>
#include <cstddef>

#include "pos.hpp"

class Input {
    std::istream &source;
    bool prompt;
    std::size_t line, byte;
public:
    Input(std::istream &, bool);
    std::pair<pos::Pos, int> peek(), get(std::string &);
    std::size_t get_line(), get_byte();
};

#endif

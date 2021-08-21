#ifndef INPUT_HPP
#define INPUT_HPP

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
};

#endif

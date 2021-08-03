#include "pos.hpp"
#include "error.hpp"
#include <iostream>

namespace error {
    InvalidCharacter::InvalidCharacter(pos::Pos &&pos):
        pos(pos) {}
    void InvalidCharacter::print(const std::string &){
    }
    UnexpectedCharacter::UnexpectedCharacter(pos::Range &&range):
        range(range) {}
    void UnexpectedCharacter::print(const std::string &log){
        std::cerr << "unexpected character `" << range.substr(log) << "` at " << range << std::endl;
    }
}

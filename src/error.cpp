#include "pos.hpp"
#include "error.hpp"
#include <iostream>

namespace error {
    Error::~Error() = default;
    UnexpectedCharacter::UnexpectedCharacter(pos::Range &&range):
        range(std::move(range)) {}
    void UnexpectedCharacter::print(const std::string &log){
        std::cerr << "unexpected character `" << range.substr(log) << "` at " << range << std::endl;
    }
    UnexpectedCharacter::~UnexpectedCharacter() = default;
}

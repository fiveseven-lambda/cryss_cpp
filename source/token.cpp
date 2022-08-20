/**
 * @file token.cpp
 */
#include "token.hpp"

namespace token {
    Token::~Token() = default;
    Identifier::Identifier(std::string_view name): name(name) {}
    Integer::Integer(std::string_view value): value(value) {}

}

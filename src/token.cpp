#include "token.hpp"

namespace token {
    Token::Token() = default;
    Token::~Token() = default;
    Identifier::Identifier(std::string &&name):
        name(std::move(name)) {}
    Integer::Integer(std::int32_t value):
        value(value) {}
    Real::Real(double value):
        value(value) {}
    String::String(std::string &&value):
        value(std::move(value)) {}
}

#include "syntax.hpp"

namespace syntax {
    Expression::Expression(){}
    Expression::~Expression() = default;
    Identifier::Identifier(std::string &&name):
        name(name) {}
    Identifier::~Identifier() = default;
    Integer::Integer(int value):
        value(value) {}
    Integer::~Integer() = default;
    Real::Real(double value):
        value(value) {}
    Real::~Real() = default;
    String::String(std::string &&value):
        value(value) {}
    String::~String() = default;
}

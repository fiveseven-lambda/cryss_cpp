#include "syntax.hpp"

#include <iostream>
#include <iomanip>

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

    // FOR DEBUG
    void Identifier::print(int indent){
        std::cout << std::setw(indent) << "" << name << std::endl;
    }
    void Integer::print(int indent){
        std::cout << std::setw(indent) << "" << value << std::endl;
    }
    void Real::print(int indent){
        std::cout << std::setw(indent) << "" << value << std::endl;
    }
    void String::print(int indent){
        std::cout << std::setw(indent) << "" << value << std::endl;
    }
}

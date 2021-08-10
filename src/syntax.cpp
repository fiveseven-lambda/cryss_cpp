#include "syntax.hpp"

#include <iostream>
#include <iomanip>

namespace syntax {
    Expression::Expression(pos::Range &&range):
        range(std::move(range)) {}
    Expression::~Expression() = default;
    Identifier::Identifier(pos::Range &&range, std::string &&name):
        Expression(std::move(range)),
        name(name) {}
    Identifier::~Identifier() = default;
    Integer::Integer(pos::Range &&range, int value):
        Expression(std::move(range)),
        value(value) {}
    Integer::~Integer() = default;
    Real::Real(pos::Range &&range, double value):
        Expression(std::move(range)),
        value(value) {}
    Real::~Real() = default;
    String::String(pos::Range &&range, std::string &&value):
        Expression(std::move(range)),
        value(value) {}
    String::~String() = default;
    Unary::Unary(pos::Range &&range, UnaryOperator op, std::unique_ptr<Expression> operand):
        Expression(std::move(range)),
        op(op),
        operand(std::move(operand)) {}
    Unary::~Unary() = default;
    pos::Range Expression::get_range(){
        return std::move(range);
    }

    // FOR DEBUG
    void Identifier::print(int indent){
        std::cout << std::setw(indent) << "" << name << "\t" << get_range() << std::endl;
    }
    void Integer::print(int indent){
        std::cout << std::setw(indent) << "" << value << "\t" << get_range() << std::endl;
    }
    void Real::print(int indent){
        std::cout << std::setw(indent) << "" << value << "\t" << get_range() << std::endl;
    }
    void String::print(int indent){
        std::cout << std::setw(indent) << "" << value << "\t" << get_range() << std::endl;
    }
    std::ostream &operator<<(std::ostream &os, const UnaryOperator &op){
        switch(op){
            case UnaryOperator::Minus: return os << "-";
            case UnaryOperator::Reciprocal: return os << "/";
            case UnaryOperator::Not: default: return os << "!";
        }
    }
    void Unary::print(int indent){
        std::cout << std::setw(indent) << "" << op << "\t" << get_range() << std::endl;
        operand->print(indent + 1);
    }
}

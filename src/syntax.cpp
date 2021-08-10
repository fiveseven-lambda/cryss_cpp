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
    Binary::Binary(pos::Range &&range, BinaryOperator op, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right):
        Expression(std::move(range)),
        op(op),
        left(std::move(left)),
        right(std::move(right)) {}
    Binary::~Binary() = default;

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
            case UnaryOperator::Not: return os << "!";
            case UnaryOperator::Print: return os << "?";
        }
        std::terminate();
    }
    void Unary::print(int indent){
        std::cout << std::setw(indent) << "" << op << "\t" << get_range() << std::endl;
        operand->print(indent + 1);
    }
    std::ostream &operator<<(std::ostream &os, const BinaryOperator &op){
        switch(op){
            case BinaryOperator::Add: return os << "+";
            case BinaryOperator::Sub: return os << "-";
            case BinaryOperator::Mul: return os << "*";
            case BinaryOperator::Div: return os << "/";
            case BinaryOperator::Rem: return os << "%";
            case BinaryOperator::Less: return os << "<";
            case BinaryOperator::LessEqual: return os << "<=";
            case BinaryOperator::Greater: return os << ">";
            case BinaryOperator::GreaterEqual: return os << ">=";
            case BinaryOperator::Equal: return os << "==";
            case BinaryOperator::NotEqual: return os << "!=";
            case BinaryOperator::BitAnd: return os << "&";
            case BinaryOperator::BitOr: return os << "|";
            case BinaryOperator::Xor: return os << "^";
            case BinaryOperator::LogicalAnd: return os << "&&";
            case BinaryOperator::LogicalOr: return os << "||";
            case BinaryOperator::LeftShift: return os << "<<";
            case BinaryOperator::RightShift: return os << ">>";
            case BinaryOperator::ForwardShift: return os << ">>>";
            case BinaryOperator::BackwardShift: return os << "<<<";
        }
        std::terminate();
    }
    int precedence(BinaryOperator op){
        switch(op){
            case BinaryOperator::ForwardShift:
            case BinaryOperator::BackwardShift: return 10;
            case BinaryOperator::Mul:
            case BinaryOperator::Div:
            case BinaryOperator::Rem: return 9;
            case BinaryOperator::Add:
            case BinaryOperator::Sub: return 8;
            case BinaryOperator::LeftShift:
            case BinaryOperator::RightShift: return 7;
            case BinaryOperator::BitAnd: return 6;
            case BinaryOperator::BitOr: return 5;
            case BinaryOperator::Xor: return 4;
            case BinaryOperator::Less:
            case BinaryOperator::LessEqual:
            case BinaryOperator::Greater:
            case BinaryOperator::GreaterEqual: return 3;
            case BinaryOperator::Equal:
            case BinaryOperator::NotEqual: return 2;
            case BinaryOperator::LogicalAnd: return 1;
            case BinaryOperator::LogicalOr: return 0;
        }
        std::terminate();
    }
    void Binary::print(int indent){
        left->print(indent + 1);
        std::cout << std::setw(indent) << "" << op << "\t" << get_range() << std::endl;
        right->print(indent + 1);
    }
}

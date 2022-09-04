/**
 * @file pre_expr.cpp
 */

#include "pre_expr.hpp"

namespace pre_expr {
    Expr::~Expr() = default;
}

#ifdef DEBUG
#include <iostream>
static void indent(int depth){
    for(int i = 0; i < depth; i++) std::cout << "    ";
}
namespace pre_expr {
    void Identifier::debug_print(int depth) const {
        indent(depth);
        std::cout << "identifier (" << name << ")" << std::endl;
    }
    void Integer::debug_print(int depth) const {
        indent(depth);
        std::cout << "integer (" << value << ")" << std::endl;
    }
    void UnaryOperation::debug_print(int depth) const {
        std::string_view name;
        switch(unary_operator){
            case UnaryOperator::Plus: name = "plus"; break;
            case UnaryOperator::Minus: name = "minus"; break;
            case UnaryOperator::PreInc: name = "prefix increment"; break;
            case UnaryOperator::PreDec: name = "prefix decrement"; break;
            case UnaryOperator::PostInc: name = "postfix increment"; break;
            case UnaryOperator::PostDec: name = "postfix decrement"; break;
            case UnaryOperator::Recip: name = "reciprocal"; break;
            case UnaryOperator::LogicalNot: name = "logical not"; break;
            case UnaryOperator::BitNot: name = "bit not"; break;
            case UnaryOperator::Print: name = "print";
        }
        indent(depth);
        std::cout << "unary (" << name << ")" << std::endl;
        operand->debug_print(depth + 1);
    }
    void BinaryOperation::debug_print(int depth) const {
        std::string_view name;
        switch(binary_operator){
            case BinaryOperator::Add: name = "add"; break;
            case BinaryOperator::AddAssign: name = "add assign"; break;
            case BinaryOperator::Sub: name = "sub"; break;
            case BinaryOperator::SubAssign: name = "sub assign"; break;
            case BinaryOperator::Mul: name = "mul"; break;
            case BinaryOperator::MulAssign: name = "mul assign"; break;
            case BinaryOperator::Div: name = "div"; break;
            case BinaryOperator::DivAssign: name = "div assign"; break;
            case BinaryOperator::Rem: name = "rem"; break;
            case BinaryOperator::RemAssign: name = "rem assign"; break;
            case BinaryOperator::Assign: name = "assign"; break;
            case BinaryOperator::Equal: name = "equal"; break;
            case BinaryOperator::NotEqual: name = "not equal"; break;
            case BinaryOperator::Less: name = "less"; break;
            case BinaryOperator::LessEqual: name = "less equal"; break;
            case BinaryOperator::LeftShift: name = "left shift"; break;
            case BinaryOperator::LeftShiftAssign: name = "left shift assign"; break;
            case BinaryOperator::BackwardShift: name = "backward shift"; break;
            case BinaryOperator::BackwardShiftAssign: name = "backward shift assign"; break;
            case BinaryOperator::Greater: name = "greater"; break;
            case BinaryOperator::GreaterEqual: name = "greater equal"; break;
            case BinaryOperator::RightShift: name = "right shift"; break;
            case BinaryOperator::RightShiftAssign: name = "right shift assign"; break;
            case BinaryOperator::ForwardShift: name = "forward shift"; break;
            case BinaryOperator::ForwardShiftAssign: name = "forward shift assign"; break;
            case BinaryOperator::BitAnd: name = "bitwise and"; break;
            case BinaryOperator::BitAndAssign: name = "bitwise and assign"; break;
            case BinaryOperator::LogicalAnd: name = "logical and"; break;
            case BinaryOperator::BitOr: name = "bitwise or"; break;
            case BinaryOperator::BitOrAssign: name = "bitwise or assign"; break;
            case BinaryOperator::LogicalOr: name = "logical or"; break;
            case BinaryOperator::BitXor: name = "bitwise xor"; break;
            case BinaryOperator::BitXorAssign: name = "bitwise xor assign";
        }
        indent(depth);
        std::cout << "binary (" << name << ")" << std::endl;
        left->debug_print(depth + 1);
        right->debug_print(depth + 1);
    }
}
#endif

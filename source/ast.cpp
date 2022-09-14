/**
 * @file ast.cpp
 */
#include "ast.hpp"

namespace ast {
    namespace type {
        Type::~Type() = default;
    }
    TopLevel::~TopLevel() = default;
    Stmt::~Stmt() = default;
    Expr::~Expr() = default;

    Identifier::Identifier(std::string_view name):
        name(name) {}
    Number::Number(std::string_view value):
        value(value) {}
    String::String(std::string value):
        value(std::move(value)) {}
    Call::Call(std::unique_ptr<Expr> func, std::vector<std::unique_ptr<Expr>> args):
        func(std::move(func)),
        args(std::move(args)) {}
    UnaryOperation::UnaryOperation(UnaryOperator op, std::unique_ptr<Expr> operand):
        op(op),
        operand(std::move(operand)) {}
    BinaryOperation::BinaryOperation(BinaryOperator op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right):
        op(op),
        left(std::move(left)),
        right(std::move(right)) {}
    List::List(std::vector<std::unique_ptr<Expr>> elems):
        elems(std::move(elems)) {}
    Group::Group(std::unique_ptr<Expr> expr):
        expr(std::move(expr)) {}
}

#ifdef DEBUG
#include <iostream>
class indent {
    int depth;
public:
    indent(int depth): depth(depth) {}
    friend std::ostream &operator<<(std::ostream &os, const indent &ind){
        for(int i = 0; i < ind.depth; i++) os << "  ";
        return os;
    }
};
namespace ast {
    void Identifier::debug_print(int depth) const {
        std::cout << indent(depth) << "identifier(" << name << ")" << std::endl;
    }
    void Number::debug_print(int depth) const {
        std::cout << indent(depth) << "number(" << value << ")" << std::endl;
    }
    void String::debug_print(int depth) const {
        std::cout << indent(depth) << "string(" << value << ")" << std::endl;
    }
    void Call::debug_print(int depth) const {
        std::cout << indent(depth) << "call" << std::endl;
        func->debug_print(depth + 1);
        std::cout << indent(depth) << "args(" << args.size() << "):" << std::endl;
        for(auto &arg : args) arg->debug_print(depth + 1);
    }
    void UnaryOperation::debug_print(int depth) const {
        std::string_view name;
        switch(op){
            case UnaryOperator::Plus: name = "plus"; break;
            case UnaryOperator::Minus: name = "minus"; break;
            case UnaryOperator::Recip: name = "recip"; break;
            case UnaryOperator::LogicalNot: name = "logical not"; break;
            case UnaryOperator::BitNot: name = "bitwise not"; break;
            case UnaryOperator::PreInc: name = "prefix increment"; break;
            case UnaryOperator::PreDec: name = "prefix decrement"; break;
            case UnaryOperator::PostInc: name = "postfix increment"; break;
            case UnaryOperator::PostDec: name = "postfix decrement";
        }
        std::cout << indent(depth) << "unary operation(" << name << ")" << std::endl;
        operand->debug_print(depth + 1);
    }
    void BinaryOperation::debug_print(int depth) const {
        std::string_view name;
        switch(op){
            case BinaryOperator::Add: name = "add"; break;
            case BinaryOperator::Sub: name = "sub"; break;
            case BinaryOperator::Mul: name = "mul"; break;
            case BinaryOperator::Div: name = "div"; break;
            case BinaryOperator::Rem: name = "rem"; break;
            case BinaryOperator::LeftShift: name = "left shift"; break;
            case BinaryOperator::RightShift: name = "right shift"; break;
            case BinaryOperator::ForwardShift: name = "forward shift"; break;
            case BinaryOperator::BackwardShift: name = "backward shift"; break;
            case BinaryOperator::Equal: name = "equal to"; break;
            case BinaryOperator::NotEqual: name = "not equal to"; break;
            case BinaryOperator::Less: name = "less than"; break;
            case BinaryOperator::LessEqual: name = "less than or equal to"; break;
            case BinaryOperator::Greater: name = "greater than"; break;
            case BinaryOperator::GreaterEqual: name = "greater than or equal to"; break;
            case BinaryOperator::LogicalAnd: name = "logical and"; break;
            case BinaryOperator::LogicalOr: name = "logical or"; break;
            case BinaryOperator::BitAnd: name = "bitwise and"; break;
            case BinaryOperator::BitOr: name = "bitwise or"; break;
            case BinaryOperator::BitXor: name = "bitwise xor"; break;
            case BinaryOperator::Index: name = "index"; break;
            case BinaryOperator::Assign: name = "assign"; break;
            case BinaryOperator::AddAssign: name = "add assign"; break;
            case BinaryOperator::SubAssign: name = "sub assign"; break;
            case BinaryOperator::MulAssign: name = "mul assign"; break;
            case BinaryOperator::DivAssign: name = "div assign"; break;
            case BinaryOperator::RemAssign: name = "rem assign"; break;
            case BinaryOperator::BitAndAssign: name = "bitwise and assign"; break;
            case BinaryOperator::BitOrAssign: name = "bitwise or assign"; break;
            case BinaryOperator::BitXorAssign: name = "bitwise xor assign"; break;
            case BinaryOperator::LeftShiftAssign: name = "left shift assign"; break;
            case BinaryOperator::RightShiftAssign: name = "right shift assign"; break;
            case BinaryOperator::ForwardShiftAssign: name = "forward shift assign"; break;
            case BinaryOperator::BackwardShiftAssign: name = "backward shift assign"; break;
        }
        std::cout << indent(depth) << "binary operation(" << name << ")" << std::endl;
        left->debug_print(depth + 1);
        right->debug_print(depth + 1);
    }
    void Group::debug_print(int depth) const {
        std::cout << indent(depth) << "group" << std::endl;
        expr->debug_print(depth + 1);
    }
    void List::debug_print(int depth) const {
        std::cout << indent(depth) << "list(" << elems.size() << ")" << std::endl;
        for(auto &elem : elems) elem->debug_print(depth + 1);
    }
}
#endif

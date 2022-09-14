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
}

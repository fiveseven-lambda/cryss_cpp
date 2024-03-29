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
    Index::Index(std::unique_ptr<Expr> operand, std::unique_ptr<Expr> index):
        operand(std::move(operand)),
        index(std::move(index)) {}
    List::List(std::vector<std::unique_ptr<Expr>> elems):
        elems(std::move(elems)) {}
    Tuple::Tuple(std::vector<std::unique_ptr<Expr>> elems):
        elems(std::move(elems)) {}
    Group::Group(std::unique_ptr<Expr> expr):
        expr(std::move(expr)) {}
    ExprStmt::ExprStmt(std::unique_ptr<Expr> expr):
        expr(std::move(expr)) {}
    While::While(std::unique_ptr<Expr> cond, std::unique_ptr<Stmt> stmt):
        cond(std::move(cond)),
        stmt(std::move(stmt)) {}
    If::If(std::unique_ptr<Expr> cond, std::unique_ptr<Stmt> stmt_true, std::unique_ptr<Stmt> stmt_false):
        cond(std::move(cond)),
        stmt_true(std::move(stmt_true)),
        stmt_false(std::move(stmt_false)) {}
    Block::Block(std::vector<std::unique_ptr<Stmt>> stmts):
        stmts(std::move(stmts)) {}
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
        std::cout << indent(depth) << pos << " identifier(" << name << ")" << std::endl;
    }
    void Number::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " number(" << value << ")" << std::endl;
    }
    void String::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " string(" << value << ")" << std::endl;
    }
    void Call::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " call" << std::endl;
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
        std::cout << indent(depth) << pos << " unary operation(" << name << ")" << std::endl;
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
        std::cout << indent(depth) << pos << " binary operation(" << name << ")" << std::endl;
        left->debug_print(depth + 1);
        right->debug_print(depth + 1);
    }
    void Index::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " index" << std::endl;
        operand->debug_print(depth + 1);
        index->debug_print(depth + 1);
    }
    void Group::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " group" << std::endl;
        expr->debug_print(depth + 1);
    }
    void List::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " list(" << elems.size() << ")" << std::endl;
        for(auto &elem : elems) elem->debug_print(depth + 1);
    }
    void Tuple::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " tuple(" << elems.size() << ")" << std::endl;
        for(auto &elem : elems) elem->debug_print(depth + 1);
    }
    void ExprStmt::debug_print(int depth) const {
        if(expr){
            std::cout << indent(depth) << pos << " expression statement" << std::endl;
            expr->debug_print(depth + 1);
        }else{
            std::cout << indent(depth) << pos << " expression statement (empty)" << std::endl;
        }
    }
    void While::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " while" << std::endl;
        cond->debug_print(depth + 1);
        std::cout << indent(depth) << "do" << std::endl;
        stmt->debug_print(depth + 1);
        std::cout << indent(depth) << "end while" << std::endl;
    }
    void If::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " if" << std::endl;
        cond->debug_print(depth + 1);
        std::cout << indent(depth) << "then" << std::endl;
        stmt_true->debug_print(depth + 1);
        if(stmt_false){
            std::cout << indent(depth) << "else" << std::endl;
            stmt_false->debug_print(depth + 1);
        }
        std::cout << indent(depth) << "end if" << std::endl;
    }
    void Block::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " block" << std::endl;
        for(auto &stmt : stmts){
            stmt->debug_print(depth + 1);
        }
        std::cout << indent(depth) << "end block" << std::endl;
    }
    void Break::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " break" << std::endl;
    }
    void Continue::debug_print(int depth) const {
        std::cout << indent(depth) << pos << " continue" << std::endl;
    }
}
#endif

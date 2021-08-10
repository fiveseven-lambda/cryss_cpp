#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <string>
#include <memory>
#include "pos.hpp"

namespace syntax {
    class Expression {
        pos::Range range;
    public:
        virtual ~Expression();
        Expression(pos::Range &&);
        Expression(const Expression &) = delete;
        Expression &operator=(const Expression &) = delete;
        pos::Range get_range();
        // FOR DEBUG
        virtual void print(int = 0) = 0;
    };
    class Identifier: public Expression {
        std::string name;
    public:
        Identifier(pos::Range &&, std::string &&);
        ~Identifier() override;
        void print(int) override;
    };
    class Integer: public Expression {
        int value;
    public:
        Integer(pos::Range &&, int);
        ~Integer() override;
        void print(int) override;
    };
    class Real: public Expression {
        double value;
    public:
        Real(pos::Range &&, double);
        ~Real() override;
        void print(int) override;
    };
    class String: public Expression {
        std::string value;
    public:
        String(pos::Range &&, std::string &&);
        ~String() override;
        void print(int) override;
    };
    enum class UnaryOperator {
        Minus,
        Reciprocal,
        Not,
        Print
    };
    std::ostream &operator<<(std::ostream &, const UnaryOperator &);
    class Unary: public Expression {
        UnaryOperator op;
        std::unique_ptr<Expression> operand;
    public:
        Unary(pos::Range &&, UnaryOperator, std::unique_ptr<Expression>);
        ~Unary() override;
        void print(int) override;
    };
    enum class BinaryOperator {
        Add,
        Sub,
        Mul,
        Div,
        Rem,
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        Equal,
        NotEqual,
        BitAnd,
        BitOr,
        Xor,
        LogicalAnd,
        LogicalOr,
        LeftShift,
        RightShift,
        ForwardShift,
        BackwardShift
    };
    int precedence(BinaryOperator);
    std::ostream &operator<<(std::ostream &, const BinaryOperator &);
    class Binary: public Expression {
        BinaryOperator op;
        std::unique_ptr<Expression> left, right;
    public:
        Binary(pos::Range &&, BinaryOperator, std::unique_ptr<Expression>, std::unique_ptr<Expression>);
        ~Binary() override;
        void print(int) override;
    };
    class Group: public Expression {
        std::unique_ptr<Expression> expression;
    public:
        Group(pos::Range &&, std::unique_ptr<Expression>);
        ~Group() override;
        void print(int) override;
    };
}

#endif

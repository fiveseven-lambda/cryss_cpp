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
        Not
    };
    class Unary: public Expression {
        UnaryOperator op;
        std::unique_ptr<Expression> operand;
    public:
        Unary(pos::Range &&, UnaryOperator, std::unique_ptr<Expression>);
        ~Unary() override;
        void print(int) override;
    };
}

#endif

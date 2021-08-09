#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <string>

namespace syntax {
    class Expression {
    public:
        virtual ~Expression();
        Expression();
        Expression(const Expression &) = delete;
        Expression &operator=(const Expression &) = delete;
    };
    class Identifier: public Expression {
        std::string name;
    public:
        Identifier(std::string &&);
        ~Identifier() override;
    };
    class Integer: public Expression {
        int value;
    public:
        Integer(int);
        ~Integer() override;
    };
    class Real: public Expression {
        double value;
    public:
        Real(double);
        ~Real() override;
    };
    class String: public Expression {
        std::string value;
    public:
        String(std::string &&);
        ~String() override;
    };
}

#endif

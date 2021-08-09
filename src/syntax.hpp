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
        // FOR DEBUG
        virtual void print(int = 0) = 0;
    };
    class Identifier: public Expression {
        std::string name;
    public:
        Identifier(std::string &&);
        ~Identifier() override;
        void print(int) override;
    };
    class Integer: public Expression {
        int value;
    public:
        Integer(int);
        ~Integer() override;
        void print(int) override;
    };
    class Real: public Expression {
        double value;
    public:
        Real(double);
        ~Real() override;
        void print(int) override;
    };
    class String: public Expression {
        std::string value;
    public:
        String(std::string &&);
        ~String() override;
        void print(int) override;
    };
}

#endif

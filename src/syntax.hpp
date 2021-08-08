#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <string>

namespace syntax {
    class Expression {
    public:
        virtual ~Expression();
    };
    class Identifier: public Expression {
        std::string name;
    public:
        ~Identifier() override;
    };
    class Integer: public Expression {
        int value;
        ~Integer() override;
    };
    class Real: public Expression {
        double value;
        ~Real() override;
    };
}

#endif

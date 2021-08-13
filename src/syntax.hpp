#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <string>
#include <cstdint>

namespace syntax {
    class Expression {
    public:
        virtual ~Expression();
    };
    class Identifier : public Expression {
        std::string name;
    };
    class Integer : public Expression {
        std::int32_t value;
    };
    class Real : public Expression {
        double value;
    };
    class String : public Expression {
        std::string value;
    };
}

#endif

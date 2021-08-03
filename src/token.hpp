#ifndef TOKEN_H
#define TOKEN_H

#include "pos.hpp"

namespace token {
    class Token {
        pos::Range range;
    protected:
        Token(pos::Range &&);
    public:
        virtual ~Token();
        // 動作確認用，あとで消す
        virtual void print() = 0;
    };

    class Identifier: public Token {
        std::string name;
    public:
        Identifier(pos::Range &&, std::string &&);
        ~Identifier() override;
        void print() override;
    };

    class Integer: public Token {
        std::int32_t value;
    public:
        Integer(pos::Range &&, std::int32_t);
        ~Integer() override;
        void print() override;
    };

    class Real: public Token {
        double value;
    public:
        Real(pos::Range &&, double);
        ~Real() override;
        void print() override;
    };
}

#endif

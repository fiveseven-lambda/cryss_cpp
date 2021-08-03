#ifndef TOKEN_H
#define TOKEN_H

#include "pos.h"

namespace token {
    class Token {
        pos::Range range;
    protected:
        Token(pos::Range &&);
    public:
        // 動作確認用，あとで消す
        void print(const std::string &);
    };

    class Identifier: public Token {
        std::string name;
    public:
        Identifier(pos::Range &&, std::string &&);
    };

    class Integer: public Token {
        std::int32_t value;
    public:
        Integer(pos::Range &&, std::int32_t);
    };

    class Real: public Token {
        double value;
    public:
        Real(pos::Range &&, double);
    };
}

#endif
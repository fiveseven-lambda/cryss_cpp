#include <string>
#include <cstddef>
#include <iostream>

#include "token.hpp"

namespace token {
    Token::Token(pos::Range &&range):
        range(range) {}
    Token::~Token() = default;
    Identifier::Identifier(pos::Range &&range, std::string &&name):
        Token(std::move(range)),
        name(name) {}
    Identifier::~Identifier() = default;
    Integer::Integer(pos::Range &&range, std::int32_t value):
        Token(std::move(range)),
        value(value) {}
    Integer::~Integer() = default;
    Real::Real(pos::Range &&range, double value):
        Token(std::move(range)),
        value(value) {}
    Real::~Real() = default;

    // 動作確認用，あとで消す
    void Identifier::print(){
        std::cout << "Identifier(" << name << ")" << std::endl;
    }
    void Integer::print(){
        std::cout << "Integer(" << value << ")" << std::endl;
    }
    void Real::print(){
        std::cout << "Real(" << value << ")" << std::endl;
    }
}

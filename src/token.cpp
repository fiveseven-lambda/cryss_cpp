#include <string>
#include <cstddef>
#include <iostream>

#include "token.hpp"

namespace token {
    Token::Token(pos::Range &&range):
        range(range) {}
    Identifier::Identifier(pos::Range &&range, std::string &&name):
        Token(std::move(range)),
        name(name) {}
    Integer::Integer(pos::Range &&range, std::int32_t value):
        Token(std::move(range)),
        value(value) {}
    Real::Real(pos::Range &&range, double value):
        Token(std::move(range)),
        value(value) {}

    // 動作確認用，あとで消す
    void Token::print(const std::string &log) {
        std::cout << range.substr(log) << std::endl;
    }
}

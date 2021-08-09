#include "pos.hpp"
#include "error.hpp"
#include <iostream>

namespace error {
    Error::~Error() = default;
    UnexpectedCharacter::UnexpectedCharacter(pos::Range &&range):
        range(std::move(range)) {}
    void UnexpectedCharacter::print(const std::string &log){
        std::cerr << "unexpected character `" << range.substr(log) << "` at " << range << std::endl;
    }
    UnexpectedCharacter::~UnexpectedCharacter() = default;
    UnexpectedToken::UnexpectedToken(pos::Range &&range):
        range(std::move(range)) {}
    void UnexpectedToken::print(const std::string &log){
        std::cerr << "unexpected token `" << range.substr(log) << "` at " << range << std::endl;
    }
    UnexpectedToken::~UnexpectedToken() = default;
    EmptyExpressionAfterUnaryOperator::EmptyExpressionAfterUnaryOperator(pos::Range &&range):
        range(std::move(range)) {}
    void EmptyExpressionAfterUnaryOperator::print(const std::string &log){
        std::cerr << "empty expression after unary operator `" << range.substr(log) << "` at " << range << std::endl;
    }
    EmptyExpressionAfterUnaryOperator::~EmptyExpressionAfterUnaryOperator() = default;
}

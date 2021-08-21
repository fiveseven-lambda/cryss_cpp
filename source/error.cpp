#include "pos.hpp"
#include "error.hpp"
#include <iostream>

namespace error {
    Error::~Error() = default;

    UnexpectedCharacter::UnexpectedCharacter(pos::Range &&range):
        range(std::move(range)) {}
    void UnexpectedCharacter::print(const std::string &log){
        std::cerr << "unexpected character `" << range.substr(log) << "` at " << range << std::endl;
        range.display(log);
    }

    UnterminatedComment::UnterminatedComment(pos::Pos &&pos):
        pos(std::move(pos)) {}
    void UnterminatedComment::print(const std::string &log){
        std::cerr << "unterminated comment (started at " << pos << ")" << std::endl;
        pos.display(log);
    }

    UnterminatedStringLiteral::UnterminatedStringLiteral(pos::Pos &&pos):
        pos(std::move(pos)) {}
    void UnterminatedStringLiteral::print(const std::string &log){
        std::cerr << "unterminated string literal (started at " << pos << ")" << std::endl;
        pos.display(log);
    }

    IncompleteScientificNotation::IncompleteScientificNotation(pos::Range &&range):
        range(std::move(range)) {}
    void IncompleteScientificNotation::print(const std::string &log){
        std::cerr << "incomplete scientific notation `" << range.substr(log) << "` at" << range << std::endl;
        range.display(log);
    }

    UnexpectedToken::UnexpectedToken(pos::Range &&range):
        range(std::move(range)) {}
    void UnexpectedToken::print(const std::string &log){
        std::cerr << "unexpected token `" << range.substr(log) << "` at " << range << std::endl;
        range.display(log);
    }

    UndefinedVariable::UndefinedVariable(pos::Range &&range):
        range(std::move(range)) {}
    void UndefinedVariable::print(const std::string &log){
        std::cerr << "undefined variable `" << range.substr(log) << "` at " << range << std::endl;
        range.display(log);
    }

    TypeMismatch::TypeMismatch(pos::Range &&range):
        range(std::move(range)) {}
    void TypeMismatch::print(const std::string &log){
        std::cerr << "type mismatch at " << range << std::endl;
        range.display(log);
    }
}

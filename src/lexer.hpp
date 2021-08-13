#ifndef LEXER_HPP
#define LEXER_HPP

#include "input.hpp"
#include "token.hpp"
#include <iostream>
#include <fstream>
#include <optional>
#include <memory>

class Lexer {
    Input input;
    std::optional<std::pair<pos::Range, std::unique_ptr<token::Token>>> peeked;
public:
    Lexer();
    Lexer(std::ifstream &);
    std::pair<pos::Range, std::unique_ptr<token::Token>> &peek(std::string &), next(std::string &);
};

#endif

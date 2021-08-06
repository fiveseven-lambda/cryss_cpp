#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <optional>
#include "token.hpp"
#include "input.hpp"

class Lexer {
    Input input;
    std::optional<std::optional<std::unique_ptr<token::Token>>> peeked;
    // !peeked ならば何も peek されていない
    // !peeked.value() ならば EOF でこれ以上トークンがない（ということが peek されている）
public:
    Lexer();
    Lexer(std::ifstream &);
    std::optional<std::unique_ptr<token::Token>> &peek(std::string &), next(std::string &);
};

#endif

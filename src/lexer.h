#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <optional>
#include "token.h"
#include "input.h"

class Lexer {
    Input input;
    bool prompt;
    std::size_t line, byte;

public:
    Lexer();
    Lexer(std::ifstream &);
    std::optional<std::unique_ptr<token::Token>> next(std::string &);
};

#endif
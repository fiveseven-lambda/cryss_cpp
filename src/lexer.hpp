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

public:
    Lexer();
    Lexer(std::ifstream &);
    std::optional<std::unique_ptr<token::Token>> next(std::string &);
};

#endif

#include <memory>
#include <cctype>
#include "pos.h"
#include "error.h"
#include "token.h"
#include "lexer.h"

Lexer::Lexer():
    input(std::cin),
    prompt(true) {}

Lexer::Lexer(std::ifstream &file):
    input(file),
    prompt(false) {}

enum class State {
    Identifier,
    Integer,
    Decimal,
};

std::optional<std::unique_ptr<token::Token>> Lexer::next(std::string &log) {
    while(std::isspace(input.peek().second)) input.get(log);
    auto [start, first] = input.get(log);
    if(first == EOF){
        return std::nullopt;
    }else if(std::isdigit(first)){
        std::string ret;
        while(std::isdigit(input.peek().second)) ret.push_back(input.get(log).second);
        auto end = input.peek().first;
        return std::make_unique<token::Integer>(pos::Range(start, end), std::move(std::stol(ret)));
    }else if(std::isalpha(first)){
        std::string ret;
        while(std::isalnum(input.peek().second)) ret.push_back(input.get(log).second);
        auto end = input.peek().first;
        return std::make_unique<token::Identifier>(pos::Range(start, end), std::move(ret));
    }else{
        int n;
        if(first < 0x80){
            n = 0;
        }else if(first < 0xC2){
            throw static_cast<std::unique_ptr<error::Error>>(std::make_unique<error::InvalidCharacter>(std::move(start)));
        }else if(first < 0xE0){
            n = 1;
        }else if(first < 0xF0){
            n = 2;
        }else if(first < 0xF5){
            n = 3;
        }else{
            throw static_cast<std::unique_ptr<error::Error>>(std::make_unique<error::InvalidCharacter>(std::move(start)));
        }
        for(int i = 0; i < n; ++i){
            input.get(log);
        }
        auto end = input.peek().first;
        throw static_cast<std::unique_ptr<error::Error>>(std::make_unique<error::UnexpectedCharacter>(pos::Range(start, end)));
    }
}
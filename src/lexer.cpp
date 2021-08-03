#include <memory>
#include <cctype>
#include "pos.hpp"
#include "error.hpp"
#include "token.hpp"
#include "lexer.hpp"

Lexer::Lexer(): input(std::cin, true) {}

Lexer::Lexer(std::ifstream &file): input(file, false) {}

std::optional<std::unique_ptr<token::Token>> Lexer::next(std::string &log) {
    while(std::isspace(input.peek().second)) input.get(log);
    auto [start, first] = input.get(log);
    if(first == EOF){
        return std::nullopt;
    }else if(std::isalpha(first)){
        std::string ret;
        while(std::isalnum(input.peek().second)) ret.push_back(input.get(log).second);
        auto end = input.peek().first;
        return std::make_unique<token::Identifier>(pos::Range(start, end), std::move(ret));
    }else{
        int ivalue;
        if('0' <= first && first <= '9'){
            ivalue = first - '0';
            while(true){
                auto [pos, c] = input.peek();
                if('0' <= c && c <= '9'){
                    input.get(log);
                    ivalue = ivalue * 10 + (c - '0');
                }else if(c == '.'){
                    input.get(log);
                    break;
                }else{
                    return std::make_unique<token::Integer>(pos::Range(start, pos), ivalue);
                }
            }
        }else if(first == '.'){
            ivalue = 0;
        }else{
            if(first >= 0xF0) input.get(log);
            if(first >= 0xE0) input.get(log);
            if(first >= 0xC0) input.get(log);
            auto end = input.peek().first;
            throw static_cast<std::unique_ptr<error::Error>>(std::make_unique<error::UnexpectedCharacter>(pos::Range(start, end)));
        }
        double dvalue = ivalue;
        double tmp = 1;
        while(true){
            auto [pos, c] = input.peek();
            if('0' <= c && c <= '9'){
                dvalue += (tmp *= .1) * (c - '0');
            }else{
                return std::make_unique<token::Real>(pos::Range(start, pos), dvalue);
            }
            input.get(log);
        }
    }
}

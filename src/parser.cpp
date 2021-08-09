#include "parser.hpp"

std::optional<std::unique_ptr<syntax::Expression>> parse_factor(Lexer &lexer, std::string &log){
    auto optional = lexer.next(log);
    if(!optional){
        return std::nullopt;
    }
    auto term = optional.value()->term();
    if(term){
        return std::move(term.value());
    }
}

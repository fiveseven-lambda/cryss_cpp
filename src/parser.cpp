#include "parser.hpp"
#include "error.hpp"

std::optional<std::unique_ptr<syntax::Expression>> parse_factor(Lexer &lexer, std::string &log){
    auto optional = lexer.next(log);
    if(!optional){
        return std::nullopt;
    }
    auto term = optional.value()->term();
    if(term){
        return std::move(term.value());
    }

    throw static_cast<std::unique_ptr<error::Error>>(std::make_unique<error::UnexpectedToken>(optional.value()->get_range()));
}

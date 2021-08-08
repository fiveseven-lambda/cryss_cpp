#include "parser.hpp"

std::optional<syntax::Expression> parse_factor(Lexer &lexer, std::string &log){
    auto optional = lexer.next(log);
    if(!optional){
        return std::nullopt;
    }else{
        // ここが todo
    }
}

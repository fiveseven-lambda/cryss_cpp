#include "parser.hpp"
#include "error.hpp"

std::optional<std::unique_ptr<syntax::Expression>> parse_factor(Lexer &lexer, std::string &log){
    auto optional = lexer.next(log);
    if(!optional){
        return std::nullopt;
    }
    auto token = std::move(optional.value());
    if(auto term = token->term(); term){
        return std::move(term.value());
    }else if(auto op = token->unary(); op){
        if(auto operand = parse_factor(lexer, log); operand){
            return std::make_unique<syntax::Unary>(op.value(), std::move(operand.value()));
        }else{
            throw static_cast<std::unique_ptr<error::Error>>(std::make_unique<error::EmptyExpressionAfterUnaryOperator>(token->get_range()));
        }
    }else{
        throw static_cast<std::unique_ptr<error::Error>>(std::make_unique<error::UnexpectedToken>(token->get_range()));
    }
}

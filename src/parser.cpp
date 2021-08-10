#include "parser.hpp"
#include "error.hpp"

std::optional<std::unique_ptr<syntax::Expression>> parse_prefix(Lexer &, std::string &);

std::optional<std::unique_ptr<syntax::Expression>> parse_prefix(Lexer &lexer, std::string &log){
    auto optional = lexer.next(log);
    if(!optional){
        return std::nullopt;
    }
    auto token = std::move(optional.value());
    if(auto factor = token->factor(); factor){
        return std::move(factor.value());
    }else if(auto op = token->unary_operator(); op){
        if(auto operand = parse_factor(lexer, log); operand){
            auto range = token->get_range() + operand.value()->get_range();
            return std::make_unique<syntax::Unary>(std::move(range), op.value(), std::move(operand.value()));
        }else{
            throw static_cast<std::unique_ptr<error::Error>>(std::make_unique<error::EmptyExpressionAfterUnaryOperator>(token->get_range()));
        }
    }else{
        throw static_cast<std::unique_ptr<error::Error>>(std::make_unique<error::UnexpectedToken>(token->get_range()));
    }
}

std::optional<std::unique_ptr<syntax::Expression>> parse_factor(Lexer &lexer, std::string &log){
    auto optional = parse_prefix(lexer, log);
    if(!optional){
        return std::nullopt;
    }
    auto expression = std::move(optional.value());
    while(true){
        auto &next = lexer.peek(log);
        if((*next)->question()){
            auto question = lexer.next(log).value();
            auto range = expression->get_range() + question->get_range();
            expression = std::make_unique<syntax::Unary>(std::move(range), syntax::UnaryOperator::Print, std::move(expression));
        }else{
            // 関数呼び出し構文もここで
            return std::move(expression);
        }
    }
}

std::optional<std::unique_ptr<syntax::Expression>> parse_binary_operator(Lexer &lexer, std::string &log, int precedence = 0){
}

#include "parser.hpp"
#include "error.hpp"

std::optional<std::unique_ptr<syntax::Expression>>
    parse_prefix(Lexer &, std::string &),
    parse_factor(Lexer &, std::string &),
    parse_binary_operator(Lexer &lexer, std::string &log, int precedence);

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
    }else if(token->opening_parenthesis()){
        if(auto expression = parse_expression(lexer, log); expression){
            auto optional_close = lexer.next(log);
            auto range = token->get_range() + optional_close.value()->get_range();
            return std::make_unique<syntax::Group>(std::move(range), std::move(expression.value()));
        }else{
            throw;
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
            return std::move(expression);
        }
        // todo: 関数呼び出し構文の条件分岐を追加
    }
}

std::optional<std::unique_ptr<syntax::Expression>> parse_binary_operator(Lexer &lexer, std::string &log, int precedence){
    if(precedence == 11){
        return parse_factor(lexer, log);
    }
    auto optional = parse_binary_operator(lexer, log, precedence + 1);
    if(!optional){
        return std::nullopt;
    }
    auto left = std::move(optional.value());
    while(true){
        auto &next = lexer.peek(log);
        if(auto op = (*next)->binary_operator(); op && syntax::precedence(op.value()) == precedence){
            lexer.next(log);
            auto optional_right = parse_binary_operator(lexer, log, precedence + 1);
            auto right = std::move(optional_right.value());
            auto range = left->get_range() + right->get_range();
            left = std::make_unique<syntax::Binary>(std::move(range), op.value(), std::move(left), std::move(right));
        }else{
            return std::move(left);
        }
    }
}

std::optional<std::unique_ptr<syntax::Expression>> parse_expression(Lexer &lexer, std::string &log){
    return parse_binary_operator(lexer, log, 0);
}

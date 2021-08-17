#include "error.hpp"
#include "parser.hpp"

static syntax::PairRangeExpression
    parse_factor(Lexer &, std::string &),
    parse_expression(Lexer &, std::string &),
    parse_binary_operator(Lexer &, std::string &, int);

syntax::PairRangeExpression parse_factor(Lexer &lexer, std::string &log){
    syntax::PairRangeExpression ret;
    do{
        auto &token_ref = lexer.peek(log).second;
        if(token_ref){
            if(auto factor = token_ref->factor(); factor){
                ret.first = lexer.next(log).first;
                ret.second = std::move(factor);
                break;
            }else if(auto prefix = token_ref->prefix(); prefix){
                auto range_prefix = lexer.next(log).first;
                auto operand = parse_factor(lexer, log);
                if(!operand.second) throw error::make<error::UnexpectedToken>(lexer.next(log).first);
                ret.first = std::move(range_prefix) + operand.first;
                ret.second = std::make_unique<syntax::Unary>(prefix.value(), std::move(operand));
                break;
            }else if(token_ref->is_opening_parenthesis()){
                auto range_opening_parenthesis = lexer.next(log).first;
                auto expression = parse_expression(lexer, log);
                auto [range_next, next] = lexer.next(log);
                if(expression.second && next->is_closing_parenthesis()){
                    ret.second = std::make_unique<syntax::Group>(std::move(expression));
                    ret.first = std::move(range_opening_parenthesis) + range_next;
                    break;
                }else throw error::make<error::UnexpectedToken>(std::move(range_next));
            }
        }
        return std::make_pair(pos::Range(), nullptr);
    }while(false);
    while(true){
        if(auto &token_ref = lexer.peek(log).second; token_ref){
            if(token_ref->is_question()){
                auto range_new = lexer.next(log).first - ret.first;
                ret.second = std::make_unique<syntax::Unary>(syntax::UnaryOperator::Print, std::move(ret));
                ret.first = std::move(range_new);
                continue;
            }
            // todo: 関数呼び出し構文
        }
        return ret;
    }
}

syntax::PairRangeExpression parse_binary_operator(Lexer &lexer, std::string &log, int precedence){
    if(precedence == 11) return parse_factor(lexer, log);
    auto left = parse_binary_operator(lexer, log, precedence + 1);
    if(!left.second) return left;
    while(true){
        if(auto &token_ref = lexer.peek(log).second; token_ref){
            if(auto binary_operator = token_ref->binary_operator(); binary_operator && syntax::precedence(binary_operator.value()) == precedence){
                lexer.next(log);
                auto right = parse_binary_operator(lexer, log, precedence + 1);
                if(!right.second) throw error::make<error::UnexpectedToken>(lexer.next(log).first);
                auto range_new = pos::add_range(left.first, right.first);
                left.second = std::make_unique<syntax::Binary>(binary_operator.value(), std::move(left), std::move(right));
                left.first = std::move(range_new);
                continue;
            }
        }
        return left;
    }
}

syntax::PairRangeExpression parse_expression(Lexer &lexer, std::string &log){
    return parse_binary_operator(lexer, log, 0);
}

syntax::PairRangeSentence parse_sentence(Lexer &lexer, std::string &log){
    auto expression = parse_expression(lexer, log);
    auto [range_next, next] = lexer.next(log);
    if(!expression.second && !next){
        return std::make_pair(std::move(expression.first), nullptr);
    }
    if(next->is_semicolon()){
        return std::make_pair(std::move(range_next) - expression.first, std::make_unique<syntax::ExpressionSentence>(std::move(expression)));
    }
    throw error::make<error::UnexpectedToken>(std::move(range_next));
}

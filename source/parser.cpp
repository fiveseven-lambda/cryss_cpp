/**
 * @file parser.cpp
 */

#include "parser.hpp"
#include "error.hpp"

static std::unique_ptr<ast::Expr> 
    parse_factor(lexer::Lexer &),
    parse_binary_operator(lexer::Lexer &),
    parse_expr(lexer::Lexer &);

static std::unique_ptr<ast::Expr> parse_factor(lexer::Lexer &lexer){
    std::unique_ptr<ast::Expr> ret;
    {
        auto &token_ref = lexer.peek();
        if(!token_ref) return nullptr;
        pos::Range pos;
        if(auto factor = token_ref->factor()){
            ret = std::move(factor);
            pos = std::move(lexer.next()->pos);
        }else if(auto prefix = token_ref->prefix()){
            pos = std::move(lexer.next()->pos);
            auto operand = parse_factor(lexer);
            if(!operand){
                if(auto token = lexer.next()) throw error::make<error::UnexpectedTokenAfterPrefix>(std::move(pos), std::move(token->pos));
                else error::make<error::EOFAfterPrefix>(std::move(pos));
            }
            pos += operand->pos;
            ret = std::make_unique<ast::UnaryOperation>(prefix.value(), std::move(operand));
        }else if(token_ref->is_opening_parenthesis()){
            pos = std::move(lexer.next()->pos);
            auto expr = parse_expr(lexer);
            auto close = lexer.next();
            if(!close) throw error::make<error::NoClosingParenthesis>(std::move(pos));
            if(!close->is_closing_parenthesis()) throw error::make<error::UnexpectedTokenInParenthesis>(std::move(pos), std::move(close->pos));
            if(!expr) throw error::make<error::EmptyParenthesis>(std::move(pos), std::move(close->pos));
            ret = std::make_unique<ast::Group>(std::move(expr));
            pos += close->pos;
        }else if(token_ref->is_opening_bracket()){
        }else{
            return nullptr;
        }
        ret->pos = std::move(pos);
    }
    while(true){
        auto &token_ref = lexer.peek();
        if(auto suffix = token_ref->suffix()){
            pos::Range pos = ret->pos + std::move(lexer.next()->pos);
            ret = std::make_unique<ast::UnaryOperation>(suffix.value(), std::move(ret));
            ret->pos = std::move(pos);
        }else{
            return ret;
        }
    }
}

static std::unique_ptr<ast::Expr> parse_expr(lexer::Lexer &lexer){
    return parse_factor(lexer);
}
static std::unique_ptr<ast::Stmt> parse_stmt(lexer::Lexer &lexer){
    return parse_expr(lexer);
}
std::unique_ptr<ast::TopLevel> parse_top_level(lexer::Lexer &lexer){
    return parse_stmt(lexer);
}

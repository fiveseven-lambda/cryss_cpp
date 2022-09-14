/**
 * @file parser.cpp
 */

#include "parser.hpp"

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
        }
        ret->pos = std::move(pos);
    }
    while(true){
        return ret;
    }
}
static std::unique_ptr<ast::Expr> parse_expr(lexer::Lexer &){}
static std::unique_ptr<ast::Stmt> parse_stmt(lexer::Lexer &){}
std::unique_ptr<ast::TopLevel> parse_top_level(lexer::Lexer &){}

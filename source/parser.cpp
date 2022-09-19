/**
 * @file parser.cpp
 */

#include "parser.hpp"
#include "error.hpp"
#include <utility>

static std::unique_ptr<ast::Expr> 
    parse_factor(lexer::Lexer &),
    parse_binary_operator(lexer::Lexer &, int current_precedence),
    parse_expr(lexer::Lexer &);
static std::tuple<std::vector<std::unique_ptr<ast::Expr>>, bool, pos::Range>
    parse_list(lexer::Lexer &, token::BracketType, pos::Range &);
static std::unique_ptr<ast::Stmt>
    parse_stmt(lexer::Lexer &);

std::unique_ptr<ast::Expr> parse_factor(lexer::Lexer &lexer){
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
        }else if(auto bracket_type = token_ref->opening_bracket_type()){
            pos = std::move(lexer.next()->pos);
            auto [elems, trailing_comma, close_pos] = parse_list(lexer, bracket_type.value(), pos);
            pos += close_pos;
            if(bracket_type == token::BracketType::Round){
                if(elems.size() == 1 && !trailing_comma){
                    ret = std::make_unique<ast::Group>(std::move(elems.front()));
                }else{
                    ret = std::make_unique<ast::Tuple>(std::move(elems));
                }
            }else{
                ret = std::make_unique<ast::List>(std::move(elems));
            }
        }else{
            return nullptr;
        }
        ret->pos = std::move(pos);
    }
    while(true){
        auto &token_ref = lexer.peek();
        pos::Range pos;
        if(!token_ref) return ret;
        if(auto suffix = token_ref->suffix()){
            pos = ret->pos + lexer.next()->pos;
            ret = std::make_unique<ast::UnaryOperation>(suffix.value(), std::move(ret));
        }else if(auto bracket_type = token_ref->opening_bracket_type()){
            auto pos_open = std::move(lexer.next()->pos);
            auto [elems, trailing_comma, pos_close] = parse_list(lexer, bracket_type.value(), pos_open);
            pos = ret->pos + pos_close;
            if(bracket_type == token::BracketType::Round){
                ret = std::make_unique<ast::Call>(std::move(ret), std::move(elems));
            }else{
                if(elems.size() == 0){
                    throw error::make<error::EmptyIndex>(std::move(pos_open), std::move(pos_close));
                }else if(elems.size() == 1){
                    ret = std::make_unique<ast::Index>(std::move(ret), std::move(elems.front()));
                }else{
                    throw error::make<error::MultipleIndices>(std::move(pos_open), std::move(pos_close));
                }
            }
        }else{
            return ret;
        }
        ret->pos = std::move(pos);
    }
}

enum Precedence {
    AssignPrecedence,
    LogicalOrPrecedence,
    LogicalAndPrecedence,
    ComparisonPrecedence,
    BitOrPrecedence,
    BitXorPrecedence,
    BitAndPrecedence,
    BitShiftPrecedence,
    AddSubPrecedence,
    MulDivRemPrecedence,
    TimeShiftPrecedence,
    MaxPrecedence,
};
static Precedence precedence(ast::BinaryOperator op){
    switch(op){
        case ast::BinaryOperator::ForwardShift:
        case ast::BinaryOperator::BackwardShift:
            return TimeShiftPrecedence;
        case ast::BinaryOperator::Mul:
        case ast::BinaryOperator::Div:
        case ast::BinaryOperator::Rem:
            return MulDivRemPrecedence;
        case ast::BinaryOperator::Add:
        case ast::BinaryOperator::Sub:
            return AddSubPrecedence;
        case ast::BinaryOperator::RightShift:
        case ast::BinaryOperator::LeftShift:
            return BitShiftPrecedence;
        case ast::BinaryOperator::BitAnd:
            return BitAndPrecedence;
        case ast::BinaryOperator::BitXor:
            return BitXorPrecedence;
        case ast::BinaryOperator::BitOr:
            return BitOrPrecedence;
        case ast::BinaryOperator::Equal:
        case ast::BinaryOperator::NotEqual:
        case ast::BinaryOperator::Less:
        case ast::BinaryOperator::LessEqual:
        case ast::BinaryOperator::Greater:
        case ast::BinaryOperator::GreaterEqual:
            return ComparisonPrecedence;
        case ast::BinaryOperator::LogicalAnd:
            return LogicalAndPrecedence;
        case ast::BinaryOperator::LogicalOr:
            return LogicalOrPrecedence;
        case ast::BinaryOperator::Assign:
        case ast::BinaryOperator::AddAssign:
        case ast::BinaryOperator::SubAssign:
        case ast::BinaryOperator::MulAssign:
        case ast::BinaryOperator::DivAssign:
        case ast::BinaryOperator::RemAssign:
        case ast::BinaryOperator::BitAndAssign:
        case ast::BinaryOperator::BitOrAssign:
        case ast::BinaryOperator::BitXorAssign:
        case ast::BinaryOperator::LeftShiftAssign:
        case ast::BinaryOperator::RightShiftAssign:
        case ast::BinaryOperator::ForwardShiftAssign:
        case ast::BinaryOperator::BackwardShiftAssign:
            return AssignPrecedence;
    }
}
enum class Associativity{
    LeftToRight,
    RightToLeft,
};
static Associativity associativity(int precedence){
    if(precedence == AssignPrecedence) return Associativity::RightToLeft;
    else return Associativity::LeftToRight;
}
std::unique_ptr<ast::Expr> parse_binary_operator(lexer::Lexer &lexer, int current_precedence){
    if(current_precedence == MaxPrecedence){
        return parse_factor(lexer);
    }
    auto left = parse_binary_operator(lexer, current_precedence + 1);
    if(!left) return nullptr;
    bool left_to_right = associativity(current_precedence) == Associativity::LeftToRight;
    while(true){
        auto &op_token = lexer.peek();
        if(!op_token) return left;
        auto op = op_token->infix();
        if(op && precedence(op.value()) == current_precedence){
            auto &op_pos = lexer.next()->pos;
            auto right = parse_binary_operator(lexer, current_precedence + left_to_right);
            if(!right){
                if(auto token = lexer.next()) throw error::make<error::UnexpectedTokenAfterInfix>(std::move(op_pos), std::move(token->pos));
                else throw error::make<error::EOFAfterInfix>(std::move(op_pos));
            }
            pos::Range pos = left->pos + right->pos;
            left = std::make_unique<ast::BinaryOperation>(op.value(), std::move(left), std::move(right));
            left->pos = std::move(pos);
            if(left_to_right) continue;
        }
        return left;
    }
}

std::tuple<std::vector<std::unique_ptr<ast::Expr>>, bool, pos::Range> parse_list(lexer::Lexer &lexer, token::BracketType opening_bracket_type, pos::Range &pos_open){
    std::vector<std::unique_ptr<ast::Expr>> ret;
    bool trailing_comma = true;
    while(true){
        auto expr = parse_expr(lexer);
        // ここで expr は nullptr の可能性がある
        auto &token = lexer.peek();
        if(token && token->is_comma()){
            auto pos_comma = std::move(lexer.next()->pos);
            if(!expr) throw error::make<error::EmptyItemInList>(std::move(pos_comma));
            ret.push_back(std::move(expr));
        }else{
            if(expr){
                ret.push_back(std::move(expr));
                trailing_comma = false;
            }
            break;
        }
    }
    auto close = lexer.next();
    if(!close) throw error::make<error::NoClosingBracket>(std::move(pos_open));
    auto closing_bracket_type = close->closing_bracket_type();
    if(!closing_bracket_type) throw error::make<error::UnexpectedTokenInBracket>(std::move(pos_open), std::move(close->pos));
    if(opening_bracket_type != closing_bracket_type) throw error::make<error::DifferentClosingBracket>(std::move(pos_open), std::move(close->pos));
    return {std::move(ret), trailing_comma, std::move(close->pos)};
}

std::unique_ptr<ast::Expr> parse_expr(lexer::Lexer &lexer){
    return parse_binary_operator(lexer, 0);
}

template <class EOFError, class UnexpectedTokenError>
std::unique_ptr<token::Token> read_token(lexer::Lexer &lexer, bool (token::Token::*cond)() const, pos::Range &arg){
    auto token = lexer.next();
    if(!token) throw error::make<EOFError>(std::move(arg));
    if(!((*token).*cond)()) throw error::make<UnexpectedTokenError>(std::move(arg), std::move(token->pos));
    return token;
}

std::unique_ptr<ast::Stmt> parse_stmt(lexer::Lexer &lexer){
    auto &token_ref = lexer.peek();
    if(!token_ref) return nullptr;
    if(token_ref->is_opening_brace()){
        auto pos_open = std::move(lexer.next()->pos);
        std::vector<std::unique_ptr<ast::Stmt>> stmts;
        while(auto stmt = parse_stmt(lexer)) stmts.push_back(std::move(stmt));
        auto pos_close = std::move(read_token<error::NoClosingBracket, error::UnexpectedTokenInBracket>(lexer, &token::Token::is_closing_brace, pos_open)->pos);
        auto ret = std::make_unique<ast::Block>(std::move(stmts));
        ret->pos = pos_open + pos_close;
        return ret;
    }else if(auto keyword = token_ref->keyword()){
        if(keyword.value() == token::Keyword::If){
            auto pos_if = std::move(lexer.next()->pos);
            auto cond_open = read_token<error::EOFAfterIf, error::UnexpectedTokenAfterIf>(lexer, &token::Token::is_opening_parenthesis, pos_if);
            auto cond = parse_expr(lexer);
            if(!cond) TODO;
            auto cond_close = read_token<error::NoClosingBracket, error::UnexpectedTokenInBracket>(lexer, &token::Token::is_closing_parenthesis, cond_open->pos);
            auto stmt_true = parse_stmt(lexer);
            if(!stmt_true) TODO;
            auto pos = pos_if + stmt_true->pos;
            std::unique_ptr<ast::Stmt> stmt_false;
            auto &maybe_else = lexer.peek();
            if(maybe_else && maybe_else->keyword() == token::Keyword::Else){
                auto pos_else = std::move(lexer.next()->pos);
                stmt_false = parse_stmt(lexer);
                if(!stmt_false) TODO;
                pos += stmt_false->pos;
            }
            auto ret = std::make_unique<ast::If>(std::move(cond), std::move(stmt_true), std::move(stmt_false));
            ret->pos = std::move(pos);
            return ret;
        }else if(keyword.value() == token::Keyword::While){
            auto pos_while = std::move(lexer.next()->pos);
            auto cond_open = read_token<error::EOFAfterWhile, error::UnexpectedTokenAfterWhile>(lexer, &token::Token::is_opening_parenthesis, pos_while);
            auto cond = parse_expr(lexer);
            if(!cond) TODO;
            auto cond_close = read_token<error::NoClosingBracket, error::UnexpectedTokenInBracket>(lexer, &token::Token::is_closing_parenthesis, cond_open->pos);
            auto stmt = parse_stmt(lexer);
            if(!stmt) TODO;
            auto pos = pos_while + stmt->pos;
            auto ret = std::make_unique<ast::While>(std::move(cond), std::move(stmt));
            ret->pos = std::move(pos);
            return ret;
        }else if(keyword.value() == token::Keyword::Break){
            auto pos_break = std::move(lexer.next()->pos);
            auto semicolon = read_token<error::EOFAfterBreak, error::UnexpectedTokenAfterBreak>(lexer, &token::Token::is_semicolon, pos_break);
            auto ret = std::make_unique<ast::Break>();
            ret->pos = pos_break + semicolon->pos;
            return ret;
        }else if(keyword.value() == token::Keyword::Continue){
            auto pos_continue = std::move(lexer.next()->pos);
            auto semicolon = read_token<error::EOFAfterContinue, error::UnexpectedTokenAfterContinue>(lexer, &token::Token::is_semicolon, pos_continue);
            auto ret = std::make_unique<ast::Continue>();
            ret->pos = pos_continue + semicolon->pos;
            return ret;
        }else{
            TODO;
        }
    }

    auto expr = parse_expr(lexer);
    auto &token = lexer.peek();
    if(!token){
        // token_ref は nullptr でないが，token は nullptr．
        // よってここで expr は空でない
        throw error::make<error::EOFAfterExpr>(std::move(expr->pos));
    }
    if(token->is_semicolon()){
        auto pos_semicolon = std::move(lexer.next()->pos);
        auto pos = expr ? expr->pos + pos_semicolon : std::move(pos_semicolon);
        auto ret = std::make_unique<ast::ExprStmt>(std::move(expr));
        ret->pos = std::move(pos);
        return ret;
    }else if(!expr){
        return nullptr;
    }else{
        TODO;
    }
}
std::unique_ptr<ast::TopLevel> parse_top_level(lexer::Lexer &lexer){
    return parse_stmt(lexer);
}

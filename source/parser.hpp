/**
 * @file parser.hpp
 */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "ast.hpp"
#include "lexer.hpp"

std::unique_ptr<ast::TopLevel> parse_top_level(lexer::Lexer &);

#endif

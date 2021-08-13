#ifndef PARSER_HPP
#define PARSER_HPP

#include <utility>
#include <memory>
#include <string>
#include "pos.hpp"
#include "lexer.hpp"
#include "syntax.hpp"

std::pair<pos::Range, std::unique_ptr<syntax::Expression>> parse_expression(Lexer &, std::string &);

#endif

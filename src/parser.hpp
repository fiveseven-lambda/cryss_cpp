#ifndef PARSER_HPP
#define PARSER_HPP

#include <utility>
#include <memory>
#include <string>
#include "pos.hpp"
#include "lexer.hpp"
#include "syntax.hpp"

syntax::PairRangeExpression parse_expression(Lexer &, std::string &);

#endif

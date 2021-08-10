#ifndef PARSER_HPP
#define PARSER_HPP

#include <optional>
#include <memory>
#include "syntax.hpp"
#include "lexer.hpp"

// 最終的にここには全体のパーサだけ残す

// これはいずれ parser.cpp 内にうつす
std::optional<std::unique_ptr<syntax::Expression>> parse_expression(Lexer &, std::string &);

#endif

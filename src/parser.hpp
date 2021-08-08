#ifndef PARSER_HPP
#define PARSER_HPP

#include <optional>
#include "syntax.hpp"
#include "lexer.hpp"

std::optional<syntax::Expression> parse_factor(Lexer &, std::string &);

#endif

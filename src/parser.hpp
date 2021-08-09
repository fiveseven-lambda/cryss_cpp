#ifndef PARSER_HPP
#define PARSER_HPP

#include <optional>
#include <memory>
#include "syntax.hpp"
#include "lexer.hpp"

std::optional<std::unique_ptr<syntax::Expression>> parse_factor(Lexer &, std::string &);

#endif

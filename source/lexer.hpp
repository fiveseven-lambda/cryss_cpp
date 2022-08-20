/**
 * @file lexer.hpp
 * @brief 字句解析を行う
 */
#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include <string>
#include <queue>
#include <istream>
#include <memory>

#include "token.hpp"

namespace lexer {
    class LineLexer {
        std::vector<pos::Pos> comments;
    public:
        void run(
            std::size_t,
            const std::string_view &,
            std::queue<std::unique_ptr<token::Token>> &
        );
        void deal_with_eof();
    };

    class Lexer {
        std::istream &source;
        bool prompt;
        bool is_beginning_of_sentence;
        std::vector<std::string> log;
        std::queue<std::unique_ptr<token::Token>> tokens;
        LineLexer line_lexer;
    public:
        Lexer();
        Lexer(std::istream &);
        void beginning_of_sentence();
        const std::vector<std::string> &get_log() const;
        std::unique_ptr<token::Token> next(), &peek();
    };
}

#endif

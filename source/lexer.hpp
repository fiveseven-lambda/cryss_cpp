/**
 * @file lexer.hpp
 * @brief 字句解析を行う
 */
#ifndef LEXER_HPP
#define LEXER_HPP

#include <queue>
#include <istream>
#include <memory>
#include <optional>
#include <deque>

#include "token.hpp"

/**
 * @brief 字句解析を行う
 */
namespace lexer {
    /**
     * @brief Lexer が内部で用いる．
     *
     * 入力を読まない．
     */
    class LineLexer {
        std::vector<pos::Pos> comments;
        std::optional<std::pair<pos::Pos, std::string>> string;
    public:
        bool is_first_token;
        LineLexer();
        void run(
            std::size_t,
            const std::string_view &,
            std::queue<std::unique_ptr<token::Token>> &
        );
        void deal_with_eof();
    };

    /**
     * @brief 入力を読みながら，トークンに分解する．
     */
    class Lexer {
        std::istream &source;
        bool prompt;
        std::deque<std::string> log;
        std::queue<std::unique_ptr<token::Token>> tokens;
        LineLexer line_lexer;
    public:
        Lexer(std::istream &, bool);
        void reset_prompt();
        const std::deque<std::string> &get_log() const;
        std::unique_ptr<token::Token> next(), &peek();
    };
}

#endif

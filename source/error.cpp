/**
 * @file error.cpp
 */

#include "error.hpp"

namespace error {
    Error::~Error() = default;
    /**
     * @brief コンストラクタ
     * @param pos 予期せぬ文字のあった場所
     */
    UnexpectedCharacter::UnexpectedCharacter(pos::Pos pos): pos(pos) {}
    /**
     * @brief コンストラクタ
     * @param poss コメントの開始位置．ネストしていた場合それら全て
     */
    UnterminatedComment::UnterminatedComment(std::vector<pos::Pos> poss): poss(std::move(poss)) {}
    /**
     * @brief コンストラクタ
     * @param pos 文字列リテラルの開始位置．
     */
    UnterminatedStringLiteral::UnterminatedStringLiteral(pos::Pos pos): pos(pos) {}
    /**
     * @brief コンストラクタ
     * @param prefix 前置演算子の位置
     * @param token 予期せぬトークンの位置
     */
    UnexpectedTokenAfterPrefix::UnexpectedTokenAfterPrefix(pos::Range prefix, pos::Range token): prefix(std::move(prefix)), token(std::move(token)) {}
    /**
     * @brief コンストラクタ
     * @param prefix 前置演算子の位置
     */
    EOFAfterPrefix::EOFAfterPrefix(pos::Range prefix): prefix(std::move(prefix)) {}
    /**
     * @brief コンストラクタ
     * @param open 開き括弧の位置
     */
    NoClosingParenthesis::NoClosingParenthesis(pos::Range open): open(std::move(open)) {}
    /**
     * @brief コンストラクタ
     * @param open 開き括弧の位置
     * @param token 予期せぬトークンの位置
     */
    UnexpectedTokenInParenthesis::UnexpectedTokenInParenthesis(pos::Range open, pos::Range token): open(std::move(open)), token(std::move(token)) {}
    /**
     * @brief コンストラクタ
     * @param open 開き括弧の位置
     * @param close 閉じ括弧の位置
     */
    EmptyParenthesis::EmptyParenthesis(pos::Range open, pos::Range close): open(std::move(open)), close(std::move(close)) {}

    void UnexpectedCharacter::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected character at " << pos << std::endl;
        pos.eprint(log);
    }
    void UnterminatedComment::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unterminated comment" << std::endl;
        for(const pos::Pos &pos : poss){
            std::cerr << "started at " << pos << std::endl;
            pos.eprint(log);
        }
    }
    void UnterminatedStringLiteral::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unterminated string literal (started at " << pos << ")" << std::endl;
        pos.eprint(log);
    }   
    void UnexpectedTokenAfterPrefix::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected token at " << token << std::endl;
        token.eprint(log);
        std::cerr << "after prefix operator at " << prefix << std::endl;
        prefix.eprint(log);
    }
    void EOFAfterPrefix::eprint(const std::deque<std::string> &log) const {
        std::cerr << "expected token, found EOF after prefix operator at " << prefix << std::endl;
        prefix.eprint(log);
    }
    void NoClosingParenthesis::eprint(const std::deque<std::string> &log) const {
        std::cerr << "no closing parenthesis corresponding to opening parenthesis at " << open << std::endl;
        open.eprint(log);
    }
    void UnexpectedTokenInParenthesis::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected token at " << token << std::endl;
        token.eprint(log);
        std::cerr << "parenthesis opened at " << open << std::endl;
        open.eprint(log);
    }
    void EmptyParenthesis::eprint(const std::deque<std::string> &log) const {
        std::cerr << "empty parenthesis opened at " << open << std::endl;
        open.eprint(log);
        std::cerr << "closed at " << close << std::endl;
        close.eprint(log);
    }
}

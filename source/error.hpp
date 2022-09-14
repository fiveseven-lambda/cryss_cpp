/**
 * @file error.hpp
 * @brief エラーを定義する
 */
#ifndef ERROR_HPP
#define ERROR_HPP

#include <deque>
#include <memory>
#include "pos.hpp"

/**
 * @brief 各種エラーを定義する．
 */
namespace error {
    /**
     * @brief 全てのエラーの基底クラス．
     */
    class Error {
    public:
        virtual ~Error();
        /**
         * @brief 標準エラー出力でエラーの内容を説明する．
         * @param source ソースコードの文字列
         */
        void virtual eprint(const std::deque<std::string> &source) const = 0;
    };

    /**
     * @brief エラーを生成するときのヘルパ関数．
     *
     * `T` が `Error` の派生クラスのとき，`make<T>(...)` は `T` のコンストラクタを呼び出し `std::unique_ptr<Error>` にして返す．
     */
    template<class Err, class... Args>
    std::unique_ptr<Error> make(Args&&... args){
        return std::make_unique<Err>(std::forward<Args>(args)...);
    }

    /**
     * @brief Lexer：予期せぬ文字が現れた．
     * 空白とコメント以外に，トークンの始まりとして適さない文字があった．
     */
    class UnexpectedCharacter : public Error {
        pos::Pos pos;
    public:
        UnexpectedCharacter(pos::Pos);
        void eprint(const std::deque<std::string> &) const override;
    };

    /**
     * @brief Lexer：コメントが終了しないまま EOF に達した．
     */
    class UnterminatedComment : public Error {
        std::vector<pos::Pos> poss;
    public:
        UnterminatedComment(std::vector<pos::Pos>);
        void eprint(const std::deque<std::string> &) const override;
    };

    /**
     * @brief Lexer：文字列リテラルが終了しないまま EOF に達した．
     */
    class UnterminatedStringLiteral : public Error {
        pos::Pos pos;
    public:
        UnterminatedStringLiteral(pos::Pos);
        void eprint(const std::deque<std::string> &) const override;
    };

    /**
     * @brief parser：前置演算子の後に予期せぬトークンがあった．
     */
    class UnexpectedTokenAfterPrefix : public Error {
        pos::Range prefix, token;
    public:
        UnexpectedTokenAfterPrefix(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };

    /**
     * @brief parser：前置演算子の後に EOF があった．
     */
    class EOFAfterPrefix : public Error {
        pos::Range prefix;
    public:
        EOFAfterPrefix(pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };

    /**
     * @brief parser：開き丸括弧に対応する閉じ丸括弧が無いまま EOF に達した．
     */
    class NoClosingParenthesis : public Error {
        pos::Range open;
    public:
        NoClosingParenthesis(pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };

    /**
     * @brief parser：丸括弧の中に予期せぬトークンがあった．
     */
    class UnexpectedTokenInParenthesis : public Error {
        pos::Range open, token;
    public:
        UnexpectedTokenInParenthesis(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };

    /**
     * @brief parser：中身が空の丸括弧があった
     */
    class EmptyParenthesis: public Error {
        pos::Range open, close;
    public:
        EmptyParenthesis(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
}

#endif

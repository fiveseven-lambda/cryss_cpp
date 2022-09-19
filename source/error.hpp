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
     */
    class NoClosingBracket: public Error {
        pos::Range open;
    public:
        NoClosingBracket(pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };

    /**
     */
    class UnexpectedTokenInBracket : public Error {
        pos::Range open, token;
    public:
        UnexpectedTokenInBracket(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };

    /**
     */
    class DifferentClosingBracket: public Error {
        pos::Range open, close;
    public:
        DifferentClosingBracket(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };

    /**
     * @brief parser：中置演算子の後に予期せぬトークンがあった．
     */
    class UnexpectedTokenAfterInfix : public Error {
        pos::Range infix, token;
    public:
        UnexpectedTokenAfterInfix(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };

    /**
     * @brief parser：中置演算子の後に EOF があった．
     */
    class EOFAfterInfix : public Error {
        pos::Range infix;
    public:
        EOFAfterInfix(pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     * @brief parser：
     */
    class EmptyItemInList : public Error {
        pos::Range comma;
    public:
        EmptyItemInList(pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    class EmptyIndex : public Error {
        pos::Range open, close;
    public:
        EmptyIndex(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    class MultipleIndices : public Error {
        pos::Range open, close;
    public:
        MultipleIndices(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     * @brief parser：
     */
    class EOFAfterExpr : public Error {
        pos::Range expr;
    public:
        EOFAfterExpr(pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     * @brief parser：
     */
    class UnexpectedTokenAfterExpr : public Error {
        pos::Range expr, token;
    public:
        UnexpectedTokenAfterExpr(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     *
     */
    class EOFAfterIf : public Error {
        pos::Range keyword;
    public:
        EOFAfterIf(pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     *
     */
    class UnexpectedTokenAfterIf : public Error {
        pos::Range keyword, token;
    public:
        UnexpectedTokenAfterIf(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     *
     */
    class EOFAfterWhile : public Error {
        pos::Range keyword;
    public:
        EOFAfterWhile(pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     *
     */
    class UnexpectedTokenAfterWhile : public Error {
        pos::Range keyword, token;
    public:
        UnexpectedTokenAfterWhile(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     *
     */
    class EOFAfterBreak : public Error {
        pos::Range keyword;
    public:
        EOFAfterBreak(pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     *
     */
    class UnexpectedTokenAfterBreak : public Error {
        pos::Range keyword, token;
    public:
        UnexpectedTokenAfterBreak(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     *
     */
    class EOFAfterContinue : public Error {
        pos::Range keyword;
    public:
        EOFAfterContinue(pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     *
     */
    class UnexpectedTokenAfterContinue : public Error {
        pos::Range keyword, token;
    public:
        UnexpectedTokenAfterContinue(pos::Range, pos::Range);
        void eprint(const std::deque<std::string> &) const override;
    };
    /**
     * @brief エラーメッセージが未実装
     */
    class Unimplemented: public Error {
        const char *file;
        unsigned line;
    public:
        Unimplemented(const char *, unsigned);
        void eprint(const std::deque<std::string> &) const override;
    };
}

#define TODO throw error::make<error::Unimplemented>(__FILE__, __LINE__)

#endif

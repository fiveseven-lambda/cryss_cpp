/**
 * @file error.hpp
 * @brief エラーを定義する
 */
#ifndef ERROR_HPP
#define ERROR_HPP

#include <memory>
#include "pos.hpp"

//! 各種エラーを定義する．
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
        void virtual eprint(const std::vector<std::string> &source) const = 0;
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
     *
     * 空白とコメント以外に，トークンの始まりとして適さない文字があった．
     */
    class UnexpectedCharacter : public Error {
        pos::Pos pos;
    public:
        UnexpectedCharacter(pos::Pos);
        void eprint(const std::vector<std::string> &) const override;
    };

    /**
     * @brief Lexer：コメントが終了しなかった．
     *
     * コメントの途中で EOF に達した．
     */
    class UnterminatedComment : public Error {
        std::vector<pos::Pos> poss;
    public:
        UnterminatedComment(std::vector<pos::Pos>);
        void eprint(const std::vector<std::string> &) const override;
    };

    /**
     * @brief Lexer：文字列リテラル中に無効なエスケープシーケンスがあった．
     *
     * 行が `\` で終了した．
     */
    class InvalidEscape : public Error {
        pos::Pos pos;
    public:
        InvalidEscape(pos::Pos);
        void eprint(const std::vector<std::string> &) const override;
    };
}

#endif

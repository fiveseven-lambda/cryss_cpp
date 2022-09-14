/**
 * @file token.hpp
 * @brief トークンを定義する
 */
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <optional>
#include <string_view>
#include "pos.hpp"
#include "ast.hpp"

/**
 * @brief トークンを定義する．
 */
namespace token {
    /**
     * @brief 全てのトークンの基底クラス
     */
    class Token {
    public:
        //! ソースコード中の位置
        pos::Range pos;
        virtual ~Token();
        virtual std::unique_ptr<ast::Expr> factor();
        virtual std::optional<ast::UnaryOperator> prefix(), suffix();
        virtual std::optional<ast::BinaryOperator> infix();
#ifdef DEBUG
        virtual void debug_print(int) const = 0;
#endif
    };
    /**
     * @brief 識別子 `[a-zA-Z_$][a-zA-Z0-9_$]*`
     */
    class Identifier : public Token {
        std::string_view name;
    public:
        Identifier(std::string_view);
        std::unique_ptr<ast::Expr> factor() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    /**
     * @brief 数値リテラル
     */
    class Number : public Token {
        std::string_view value;
    public:
        Number(std::string_view);
        std::unique_ptr<ast::Expr> factor() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    /**
     * @brief 文字列リテラル
     */
    class String : public Token {
        std::string value;
    public:
        String(std::string value);
        std::unique_ptr<ast::Expr> factor() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `+`
    class Plus : public Token {
        std::optional<ast::UnaryOperator> prefix() override;
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `++`
    class DoublePlus : public Token {
        std::optional<ast::UnaryOperator> prefix() override;
        std::optional<ast::UnaryOperator> suffix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `+=`
    class PlusEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `-`
    class Hyphen : public Token {
        std::optional<ast::UnaryOperator> prefix() override;
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `--`
    class DoubleHyphen : public Token {
        std::optional<ast::UnaryOperator> prefix() override;
        std::optional<ast::UnaryOperator> suffix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `-=`
    class HyphenEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `*`
    class Asterisk : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `*=`
    class AsteriskEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `/`
    class Slash : public Token {
        std::optional<ast::UnaryOperator> prefix() override;
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `/=`
    class SlashEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `%`
    class Percent : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `%=`
    class PercentEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `=`
    class Equal : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `==`
    class DoubleEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `!`
    class Exclamation : public Token {
        std::optional<ast::UnaryOperator> prefix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `!=`
    class ExclamationEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `<`
    class Less : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `<=`
    class LessEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `<<`
    class DoubleLess : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `<<=`
    class DoubleLessEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `<<<`
    class TripleLess : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `<<<=`
    class TripleLessEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `>`
    class Greater : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `>=`
    class GreaterEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `>>`
    class DoubleGreater : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `>>=`
    class DoubleGreaterEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `>>>`
    class TripleGreater : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `>>>=`
    class TripleGreaterEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `&`
    class Ampersand : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `&=`
    class AmpersandEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `&&`
    class DoubleAmpersand : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `|`
    class Bar : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `|=`
    class BarEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `||`
    class DoubleBar : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `^`
    class Circumflex : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `^=`
    class CircumflexEqual : public Token {
        std::optional<ast::BinaryOperator> infix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `.`
    class Dot : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `:`
    class Colon : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `;`
    class Semicolon : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `,`
    class Comma : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `?`
    class Question : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `#`
    class Hash : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `~`
    class Tilde : public Token {
        std::optional<ast::UnaryOperator> prefix() override;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `(`
    class OpeningParenthesis : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `)`
    class ClosingParenthesis : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `[`
    class OpeningBracket : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `]`
    class ClosingBracket : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `{`
    class OpeningBrace : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
    //! `}`
    class ClosingBrace : public Token {
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };
}

#endif

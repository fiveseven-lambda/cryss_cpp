#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <memory>
#include <optional>
#include "syntax.hpp"

namespace token {
    class Token {
        Token(const Token &) = delete;
        Token &operator=(const Token &) = delete;
    protected:
        Token();
    public:
        virtual ~Token();
        virtual std::unique_ptr<syntax::Expression> factor();
        virtual std::optional<syntax::UnaryOperator> prefix();
        virtual std::optional<syntax::BinaryOperator> binary_operator();
        virtual std::optional<std::string> identifier();
        virtual bool is_question(), is_opening_parenthesis(), is_closing_parenthesis(), is_semicolon(), is_equal(), is_keyword_let();
    };
    class Identifier : public Token {
        std::string name;
    public:
        Identifier(std::string &&);
        std::optional<std::string> identifier() override;
        std::unique_ptr<syntax::Expression> factor() override;
    };
    class KeywordLet : public Token {
    public:
        bool is_keyword_let() override;
    };
    class Integer : public Token {
        std::int32_t value;
    public:
        Integer(std::int32_t);
        std::unique_ptr<syntax::Expression> factor() override;
    };
    class Real : public Token {
        double value;
    public:
        Real(double);
        std::unique_ptr<syntax::Expression> factor() override;
    };
    class String : public Token {
        std::string value;
    public:
        String(std::string &&);
        std::unique_ptr<syntax::Expression> factor() override;
    };
    class Plus : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Hyphen : public Token {
    public:
        std::optional<syntax::UnaryOperator> prefix() override;
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Asterisk : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Slash : public Token {
    public:
        std::optional<syntax::UnaryOperator> prefix() override;
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Percent : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Equal : public Token {
    public:
        bool is_equal() override;
    };
    class DoubleEqual : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Exclamation : public Token {
    public:
        std::optional<syntax::UnaryOperator> prefix() override;
    };
    class ExclamationEqual : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Less : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class LessEqual : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class DoubleLess : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class TripleLess : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Greater : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class GreaterEqual : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class DoubleGreater: public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class TripleGreater : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Ampersand : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class DoubleAmpersand : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Bar : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class DoubleBar : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Circumflex : public Token {
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Colon : public Token {};
    class Semicolon : public Token {
        bool is_semicolon() override;
    };
    class Comma : public Token {};
    class Dot : public Token {};
    class Question : public Token {
        bool is_question() override;
    };
    class OpeningParenthesis : public Token {
        bool is_opening_parenthesis() override;
    };
    class ClosingParenthesis : public Token {
        bool is_closing_parenthesis() override;
    };
    class OpeningBracket : public Token {};
    class ClosingBracket : public Token {};
    class OpeningBrace : public Token {};
    class ClosingBrace : public Token {};
}

#endif

#ifndef TOKEN_H
#define TOKEN_H

#include <optional>
#include <memory>
#include "pos.hpp"
#include "syntax.hpp"

namespace token {
    class Token {
        pos::Range range;
    protected:
        Token(pos::Range &&);
    public:
        virtual ~Token();
        pos::Range get_range();
        Token(const Token &) = delete;
        Token &operator=(const Token &) = delete;
        virtual std::optional<std::unique_ptr<syntax::Expression>> factor();
        virtual std::optional<syntax::UnaryOperator> unary_operator();
        virtual std::optional<syntax::BinaryOperator> binary_operator();
        virtual bool question();
    };

    class Identifier: public Token {
        std::string name;
    public:
        Identifier(pos::Range &&, std::string &&);
        ~Identifier() override;
        std::optional<std::unique_ptr<syntax::Expression>> factor() override;
    };

    class Integer: public Token {
        std::int32_t value;
    public:
        Integer(pos::Range &&, std::int32_t);
        ~Integer() override;
        std::optional<std::unique_ptr<syntax::Expression>> factor() override;
    };

    class Real: public Token {
        double value;
    public:
        Real(pos::Range &&, double);
        ~Real() override;
        std::optional<std::unique_ptr<syntax::Expression>> factor() override;
    };

    class String: public Token {
        std::string value;
    public:
        String(pos::Range &&, std::string &&);
        ~String() override;
        std::optional<std::unique_ptr<syntax::Expression>> factor() override;
    };


    class Plus: public Token {
    public:
        Plus(pos::Range &&);
        ~Plus() override;
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Hyphen: public Token {
    public:
        Hyphen(pos::Range &&);
        ~Hyphen() override;
        std::optional<syntax::UnaryOperator> unary_operator() override;
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Asterisk: public Token {
    public:
        Asterisk(pos::Range &&);
        ~Asterisk() override;
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Slash: public Token {
    public:
        Slash(pos::Range &&);
        ~Slash() override;
        std::optional<syntax::UnaryOperator> unary_operator() override;
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Percent: public Token {
    public:
        Percent(pos::Range &&);
        ~Percent() override;
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Circumflex: public Token {
    public:
        Circumflex(pos::Range &&);
        ~Circumflex() override;
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Equal: public Token {
    public:
        Equal(pos::Range &&);
        ~Equal() override;
    };
    class DoubleEqual: public Token {
    public:
        DoubleEqual(pos::Range &&);
        ~DoubleEqual() override;
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Exclamation: public Token {
    public:
        Exclamation(pos::Range &&);
        ~Exclamation() override;
        std::optional<syntax::UnaryOperator> unary_operator() override;
    };
    class ExclamationEqual: public Token {
    public:
        ExclamationEqual(pos::Range &&);
        ~ExclamationEqual() override;
        std::optional<syntax::BinaryOperator> binary_operator() override;
    };
    class Less: public Token {
    public:
        Less(pos::Range &&);
        ~Less() override;
    };
    class LessEqual: public Token {
    public:
        LessEqual(pos::Range &&);
        ~LessEqual() override;
    };
    class DoubleLess: public Token {
    public:
        DoubleLess(pos::Range &&);
        ~DoubleLess() override;
    };
    class Greater: public Token {
    public:
        Greater(pos::Range &&);
        ~Greater() override;
    };
    class GreaterEqual: public Token {
    public:
        GreaterEqual(pos::Range &&);
        ~GreaterEqual() override;
    };
    class DoubleGreater: public Token {
    public:
        DoubleGreater(pos::Range &&);
        ~DoubleGreater() override;
    };
    class Ampersand: public Token {
    public:
        Ampersand(pos::Range &&);
        ~Ampersand() override;
    };
    class DoubleAmpersand: public Token {
    public:
        DoubleAmpersand(pos::Range &&);
        ~DoubleAmpersand() override;
    };
    class Bar: public Token {
    public:
        Bar(pos::Range &&);
        ~Bar() override;
    };
    class DoubleBar: public Token {
    public:
        DoubleBar(pos::Range &&);
        ~DoubleBar() override;
    };
    class Colon: public Token {
    public:
        Colon(pos::Range &&);
        ~Colon() override;
    };
    class Semicolon: public Token {
    public:
        Semicolon(pos::Range &&);
        ~Semicolon() override;
    };
    class Comma: public Token {
    public:
        Comma(pos::Range &&);
        ~Comma() override;
    };
    class Dot: public Token {
    public:
        Dot(pos::Range &&);
        ~Dot() override;
    };
    class Question: public Token {
    public:
        Question(pos::Range &&);
        ~Question() override;
        bool question() override;
    };
    class OpeningParenthesis: public Token {
    public:
        OpeningParenthesis(pos::Range &&);
        ~OpeningParenthesis() override;
    };
    class ClosingParenthesis: public Token {
    public:
        ClosingParenthesis(pos::Range &&);
        ~ClosingParenthesis() override;
    };
    class OpeningBracket: public Token {
    public:
        OpeningBracket(pos::Range &&);
        ~OpeningBracket() override;
    };
    class ClosingBracket: public Token {
    public:
        ClosingBracket(pos::Range &&);
        ~ClosingBracket() override;
    };
    class OpeningBrace: public Token {
    public:
        OpeningBrace(pos::Range &&);
        ~OpeningBrace() override;
    };
    class ClosingBrace: public Token {
    public:
        ClosingBrace(pos::Range &&);
        ~ClosingBrace() override;
    };
}

#endif

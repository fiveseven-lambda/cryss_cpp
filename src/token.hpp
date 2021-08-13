#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

namespace token {
    class Token {
        Token(const Token &) = delete;
        Token &operator=(const Token &) = delete;
    protected:
        Token();
    public:
        virtual ~Token();
    };
    class Identifier : public Token {
        std::string name;
    public:
        Identifier(std::string &&);
    };
    class Integer : public Token {
        std::int32_t value;
    public:
        Integer(std::int32_t);
    };
    class Real : public Token {
        double value;
    public:
        Real(double);
    };
    class String : public Token {
        std::string value;
    public:
        String(std::string &&);
    };
    class Plus : public Token {};
    class Hyphen : public Token {};
    class Asterisk : public Token {};
    class Slash : public Token {};
    class Percent : public Token {};
    class Circumflex : public Token {};
    class Equal : public Token {};
    class DoubleEqual : public Token {};
    class Exclamation : public Token {};
    class ExclamationEqual : public Token {};
    class Less : public Token {};
    class LessEqual : public Token {};
    class DoubleLess : public Token {};
    class TripleLess : public Token {};
    class Greater : public Token {};
    class GreaterEqual : public Token {};
    class DoubleGreater: public Token {};
    class TripleGreater : public Token {};
    class Ampersand : public Token {};
    class DoubleAmpersand : public Token {};
    class Bar : public Token {};
    class DoubleBar : public Token {};
    class Colon : public Token {};
    class Semicolon : public Token {};
    class Comma : public Token {};
    class Dot : public Token {};
    class Question : public Token {};
    class OpeningParenthesis : public Token {};
    class ClosingParenthesis : public Token {};
    class OpeningBracket : public Token {};
    class ClosingBracket : public Token {};
    class OpeningBrace : public Token {};
    class ClosingBrace : public Token {};
}

#endif

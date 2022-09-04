/**
 * @file token.cpp
 */
#include "token.hpp"

namespace token {
    Token::~Token() = default;
    Identifier::Identifier(std::string_view name): name(name) {}
    Number::Number(std::string_view value): value(value) {}
    String::String(std::string value) : value(std::move(value)) {}

}

#ifdef DEBUG
#include <iostream>
static void indent(int depth){
    for(int i = 0; i < depth; i++) std::cout << "    ";
}
namespace token {
    void Identifier::debug_print(int depth) const {
        indent(depth);
        std::cout << "identifier (" << name << ")" << std::endl;
    }
    void Number::debug_print(int depth) const {
        indent(depth);
        std::cout << "integer (" << value << ")" << std::endl;
    }
    void String::debug_print(int depth) const {
        indent(depth);
        std::cout << "string (" << value << ")" << std::endl;
    }

#define define_debug_print(token, text) \
    void token::debug_print(int depth) const { \
        indent(depth); \
        std::cout << text << std::endl; \
    } \

    define_debug_print(Plus, "plus (+)")
    define_debug_print(DoublePlus, "double plus (++)")
    define_debug_print(PlusEqual, "plus equal (+=)")
    define_debug_print(Hyphen, "hyphen (-)")
    define_debug_print(DoubleHyphen, "double hyphen (--)")
    define_debug_print(HyphenEqual, "hyphen equal (-=)")
    define_debug_print(Asterisk, "asterisk (*)")
    define_debug_print(AsteriskEqual, "asterisk equal (*=)")
    define_debug_print(Slash, "slash (/)")
    define_debug_print(SlashEqual, "slash equal (/=)")
    define_debug_print(Percent, "percent (%)")
    define_debug_print(PercentEqual, "percent equal (%=)")
    define_debug_print(Equal, "equal (=)")
    define_debug_print(DoubleEqual, "double equal (==)")
    define_debug_print(Exclamation, "exclamation (!)")
    define_debug_print(ExclamationEqual, "exclamation equal (!=)")
    define_debug_print(Less, "less (<)")
    define_debug_print(LessEqual, "less equal (<=)")
    define_debug_print(DoubleLess, "double less (<<)")
    define_debug_print(DoubleLessEqual, "double less equal (<<=)")
    define_debug_print(TripleLess, "triple less (<<<)")
    define_debug_print(TripleLessEqual, "triple less equal (<<<=)")
    define_debug_print(Greater, "greater (>)")
    define_debug_print(GreaterEqual, "greater equal (>=)")
    define_debug_print(DoubleGreater, "double greater (>>)")
    define_debug_print(DoubleGreaterEqual, "double greater equal (>>=)")
    define_debug_print(TripleGreater, "triple greater (>>>)")
    define_debug_print(TripleGreaterEqual, "triple greater equal (>>>=)")
    define_debug_print(Ampersand, "ampersand (&)")
    define_debug_print(AmpersandEqual, "ampersand equal (&=)")
    define_debug_print(DoubleAmpersand, "double ampersand (&&)")
    define_debug_print(Bar, "bar (|)")
    define_debug_print(BarEqual, "bar equal (|=)")
    define_debug_print(DoubleBar, "double bar (||)")
    define_debug_print(Circumflex, "circumflex (^)")
    define_debug_print(CircumflexEqual, "circumflex equal (^=)")
    define_debug_print(Dot, "dot (.)")
    define_debug_print(Colon, "colon (:)")
    define_debug_print(Semicolon, "semicolon (;)")
    define_debug_print(Comma, "comma (,)")
    define_debug_print(Question, "question (?)")
    define_debug_print(Hash, "hash (#)")
    define_debug_print(Tilde, "tilde (~)")
    define_debug_print(OpeningParenthesis, "opening parenthesis '('")
    define_debug_print(ClosingParenthesis, "closing parenthesis ')'")
    define_debug_print(OpeningBracket, "opening bracket '['")
    define_debug_print(ClosingBracket, "closing bracket ']'")
    define_debug_print(OpeningBrace, "opening brace '{'")
    define_debug_print(ClosingBrace, "closing brace '}'")
}
#endif


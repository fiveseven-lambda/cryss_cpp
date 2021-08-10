#include <string>
#include <cstddef>
#include <iostream>

#include "token.hpp"

namespace token {
    Token::Token(pos::Range &&range):
        range(std::move(range)) {}
    Token::~Token() = default;
    pos::Range Token::get_range() {
        return std::move(range);
    }

    Identifier::Identifier(pos::Range &&range, std::string &&name):
        Token(std::move(range)),
        name(name) {}
    Identifier::~Identifier() = default;
    Integer::Integer(pos::Range &&range, std::int32_t value):
        Token(std::move(range)),
        value(value) {}
    Integer::~Integer() = default;
    Real::Real(pos::Range &&range, double value):
        Token(std::move(range)),
        value(value) {}
    Real::~Real() = default;
    String::String(pos::Range &&range, std::string &&value):
        Token(std::move(range)),
        value(value) {}
    String::~String() = default;
    Plus::Plus(pos::Range &&range):
        Token(std::move(range)) {}
    Plus::~Plus() = default;
    Hyphen::Hyphen(pos::Range &&range):
        Token(std::move(range)) {}
    Hyphen::~Hyphen() = default;
    Asterisk::Asterisk(pos::Range &&range):
        Token(std::move(range)) {}
    Asterisk::~Asterisk() = default;
    Slash::Slash(pos::Range &&range):
        Token(std::move(range)) {}
    Slash::~Slash() = default;
    Percent::Percent(pos::Range &&range):
        Token(std::move(range)) {}
    Percent::~Percent() = default;
    Circumflex::Circumflex(pos::Range &&range):
        Token(std::move(range)) {}
    Circumflex::~Circumflex() = default;
    Equal::Equal(pos::Range &&range):
        Token(std::move(range)) {}
    Equal::~Equal() = default;
    DoubleEqual::DoubleEqual(pos::Range &&range):
        Token(std::move(range)) {}
    DoubleEqual::~DoubleEqual() = default;
    Exclamation::Exclamation(pos::Range &&range):
        Token(std::move(range)) {}
    Exclamation::~Exclamation() = default;
    ExclamationEqual::ExclamationEqual(pos::Range &&range):
        Token(std::move(range)) {}
    ExclamationEqual::~ExclamationEqual() = default;
    Less::Less(pos::Range &&range):
        Token(std::move(range)) {}
    Less::~Less() = default;
    LessEqual::LessEqual(pos::Range &&range):
        Token(std::move(range)) {}
    LessEqual::~LessEqual() = default;
    DoubleLess::DoubleLess(pos::Range &&range):
        Token(std::move(range)) {}
    DoubleLess::~DoubleLess() = default;
    Greater::Greater(pos::Range &&range):
        Token(std::move(range)) {}
    Greater::~Greater() = default;
    GreaterEqual::GreaterEqual(pos::Range &&range):
        Token(std::move(range)) {}
    GreaterEqual::~GreaterEqual() = default;
    DoubleGreater::DoubleGreater(pos::Range &&range):
        Token(std::move(range)) {}
    DoubleGreater::~DoubleGreater() = default;
    Ampersand::Ampersand(pos::Range &&range):
        Token(std::move(range)) {}
    Ampersand::~Ampersand() = default;
    DoubleAmpersand::DoubleAmpersand(pos::Range &&range):
        Token(std::move(range)) {}
    DoubleAmpersand::~DoubleAmpersand() = default;
    Bar::Bar(pos::Range &&range):
        Token(std::move(range)) {}
    Bar::~Bar() = default;
    DoubleBar::DoubleBar(pos::Range &&range):
        Token(std::move(range)) {}
    DoubleBar::~DoubleBar() = default;
    Colon::Colon(pos::Range &&range):
        Token(std::move(range)) {}
    Colon::~Colon() = default;
    Semicolon::Semicolon(pos::Range &&range):
        Token(std::move(range)) {}
    Semicolon::~Semicolon() = default;
    Comma::Comma(pos::Range &&range):
        Token(std::move(range)) {}
    Comma::~Comma() = default;
    Dot::Dot(pos::Range &&range):
        Token(std::move(range)) {}
    Dot::~Dot() = default;
    Question::Question(pos::Range &&range):
        Token(std::move(range)) {}
    Question::~Question() = default;
    OpeningParenthesis::OpeningParenthesis(pos::Range &&range):
        Token(std::move(range)) {}
    OpeningParenthesis::~OpeningParenthesis() = default;
    ClosingParenthesis::ClosingParenthesis(pos::Range &&range):
        Token(std::move(range)) {}
    ClosingParenthesis::~ClosingParenthesis() = default;
    OpeningBracket::OpeningBracket(pos::Range &&range):
        Token(std::move(range)) {}
    OpeningBracket::~OpeningBracket() = default;
    ClosingBracket::ClosingBracket(pos::Range &&range):
        Token(std::move(range)) {}
    ClosingBracket::~ClosingBracket() = default;
    OpeningBrace::OpeningBrace(pos::Range &&range):
        Token(std::move(range)) {}
    OpeningBrace::~OpeningBrace() = default;
    ClosingBrace::ClosingBrace(pos::Range &&range):
        Token(std::move(range)) {}
    ClosingBrace::~ClosingBrace() = default;

    std::optional<std::unique_ptr<syntax::Expression>> Token::factor(){
        return std::nullopt;
    }
    std::optional<std::unique_ptr<syntax::Expression>> Identifier::factor(){
        return std::make_unique<syntax::Identifier>(get_range(), std::move(name));
    }
    std::optional<std::unique_ptr<syntax::Expression>> Integer::factor(){
        return std::make_unique<syntax::Integer>(get_range(), value);
    }
    std::optional<std::unique_ptr<syntax::Expression>> Real::factor(){
        return std::make_unique<syntax::Real>(get_range(), value);
    }
    std::optional<std::unique_ptr<syntax::Expression>> String::factor(){
        return std::make_unique<syntax::String>(get_range(), std::move(value));
    }
    std::optional<syntax::UnaryOperator> Token::unary_operator() {
        return std::nullopt;
    }
    std::optional<syntax::UnaryOperator> Hyphen::unary_operator() {
        return syntax::UnaryOperator::Minus;
    }
    std::optional<syntax::UnaryOperator> Slash::unary_operator() {
        return syntax::UnaryOperator::Reciprocal;
    }
    std::optional<syntax::UnaryOperator> Exclamation::unary_operator() {
        return syntax::UnaryOperator::Not;
    }
    std::optional<syntax::BinaryOperator> Token::binary_operator() {
        return std::nullopt;
    }
    std::optional<syntax::BinaryOperator> Plus::binary_operator() {
        return syntax::BinaryOperator::Add;
    }
    std::optional<syntax::BinaryOperator> Hyphen::binary_operator() {
        return syntax::BinaryOperator::Sub;
    }
    std::optional<syntax::BinaryOperator> Asterisk::binary_operator() {
        return syntax::BinaryOperator::Mul;
    }
    std::optional<syntax::BinaryOperator> Slash::binary_operator() {
        return syntax::BinaryOperator::Div;
    }
    std::optional<syntax::BinaryOperator> Percent::binary_operator() {
        return syntax::BinaryOperator::Rem;
    }
    std::optional<syntax::BinaryOperator> Circumflex::binary_operator() {
        return syntax::BinaryOperator::Pow;
    }
    std::optional<syntax::BinaryOperator> DoubleEqual::binary_operator() {
        return syntax::BinaryOperator::Equal;
    }
    std::optional<syntax::BinaryOperator> ExclamationEqual::binary_operator() {
        return syntax::BinaryOperator::NotEqual;
    }
    bool Token::question(){
        return false;
    }
    bool Question::question(){
        return true;
    }
}

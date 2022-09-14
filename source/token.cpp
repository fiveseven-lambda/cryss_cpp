/**
 * @file token.cpp
 */
#include "token.hpp"

namespace token {
    Token::~Token() = default;
    Identifier::Identifier(std::string_view name): name(name) {}
    Number::Number(std::string_view value): value(value) {}
    String::String(std::string value) : value(std::move(value)) {}

    std::unique_ptr<ast::Expr> Token::factor(){ return nullptr; }
    std::unique_ptr<ast::Expr> Identifier::factor(){ return std::make_unique<ast::Identifier>(name); }
    std::unique_ptr<ast::Expr> Number::factor(){ return std::make_unique<ast::Number>(value); }
    std::unique_ptr<ast::Expr> String::factor(){ return std::make_unique<ast::String>(std::move(value)); }

    std::optional<ast::UnaryOperator> Token::prefix(){ return std::nullopt; }
    std::optional<ast::UnaryOperator> Plus::prefix(){ return ast::UnaryOperator::Plus; }
    std::optional<ast::UnaryOperator> Hyphen::prefix(){ return ast::UnaryOperator::Minus; }
    std::optional<ast::UnaryOperator> DoublePlus::prefix(){ return ast::UnaryOperator::PreInc; }
    std::optional<ast::UnaryOperator> DoubleHyphen::prefix(){ return ast::UnaryOperator::PreDec; }
    std::optional<ast::UnaryOperator> Slash::prefix(){ return ast::UnaryOperator::Recip; }
    std::optional<ast::UnaryOperator> Exclamation::prefix(){ return ast::UnaryOperator::LogicalNot; }
    std::optional<ast::UnaryOperator> Tilde::prefix(){ return ast::UnaryOperator::BitNot; }

    std::optional<ast::UnaryOperator> Token::suffix(){ return std::nullopt; }
    std::optional<ast::UnaryOperator> DoublePlus::suffix(){ return ast::UnaryOperator::PostInc; }
    std::optional<ast::UnaryOperator> DoubleHyphen::suffix(){ return ast::UnaryOperator::PostDec; }

    std::optional<ast::BinaryOperator> Token::infix(){ return std::nullopt; }
    std::optional<ast::BinaryOperator> Plus::infix(){ return ast::BinaryOperator::Add; }
    std::optional<ast::BinaryOperator> Hyphen::infix(){ return ast::BinaryOperator::Sub; }
    std::optional<ast::BinaryOperator> Asterisk::infix(){ return ast::BinaryOperator::Mul; }
    std::optional<ast::BinaryOperator> Slash::infix(){ return ast::BinaryOperator::Div; }
    std::optional<ast::BinaryOperator> Percent::infix(){ return ast::BinaryOperator::Rem; }
    std::optional<ast::BinaryOperator> DoubleGreater::infix(){ return ast::BinaryOperator::RightShift; }
    std::optional<ast::BinaryOperator> DoubleLess::infix(){ return ast::BinaryOperator::LeftShift; }
    std::optional<ast::BinaryOperator> TripleGreater::infix(){ return ast::BinaryOperator::ForwardShift; }
    std::optional<ast::BinaryOperator> TripleLess::infix(){ return ast::BinaryOperator::BackwardShift; }
    std::optional<ast::BinaryOperator> DoubleEqual::infix(){ return ast::BinaryOperator::Equal; }
    std::optional<ast::BinaryOperator> ExclamationEqual::infix(){ return ast::BinaryOperator::NotEqual; }
    std::optional<ast::BinaryOperator> Less::infix(){ return ast::BinaryOperator::Less; }
    std::optional<ast::BinaryOperator> LessEqual::infix(){ return ast::BinaryOperator::LessEqual; }
    std::optional<ast::BinaryOperator> Greater::infix(){ return ast::BinaryOperator::Greater; }
    std::optional<ast::BinaryOperator> GreaterEqual::infix(){ return ast::BinaryOperator::GreaterEqual; }
    std::optional<ast::BinaryOperator> DoubleAmpersand::infix(){ return ast::BinaryOperator::LogicalAnd; }
    std::optional<ast::BinaryOperator> DoubleBar::infix(){ return ast::BinaryOperator::LogicalOr; }
    std::optional<ast::BinaryOperator> Ampersand::infix(){ return ast::BinaryOperator::BitAnd; }
    std::optional<ast::BinaryOperator> Bar::infix(){ return ast::BinaryOperator::BitOr; }
    std::optional<ast::BinaryOperator> Circumflex::infix(){ return ast::BinaryOperator::BitXor; }
    std::optional<ast::BinaryOperator> Equal::infix(){ return ast::BinaryOperator::Assign; }
    std::optional<ast::BinaryOperator> PlusEqual::infix(){ return ast::BinaryOperator::AddAssign; }
    std::optional<ast::BinaryOperator> HyphenEqual::infix(){ return ast::BinaryOperator::SubAssign; }
    std::optional<ast::BinaryOperator> AsteriskEqual::infix(){ return ast::BinaryOperator::MulAssign; }
    std::optional<ast::BinaryOperator> SlashEqual::infix(){ return ast::BinaryOperator::DivAssign; }
    std::optional<ast::BinaryOperator> PercentEqual::infix(){ return ast::BinaryOperator::RemAssign; }
    std::optional<ast::BinaryOperator> AmpersandEqual::infix(){ return ast::BinaryOperator::BitAndAssign; }
    std::optional<ast::BinaryOperator> BarEqual::infix(){ return ast::BinaryOperator::BitOrAssign; }
    std::optional<ast::BinaryOperator> CircumflexEqual::infix(){ return ast::BinaryOperator::BitXorAssign; }
    std::optional<ast::BinaryOperator> DoubleGreaterEqual::infix(){ return ast::BinaryOperator::RightShiftAssign; }
    std::optional<ast::BinaryOperator> DoubleLessEqual::infix(){ return ast::BinaryOperator::LeftShiftAssign; }
    std::optional<ast::BinaryOperator> TripleGreaterEqual::infix(){ return ast::BinaryOperator::ForwardShiftAssign; }
    std::optional<ast::BinaryOperator> TripleLessEqual::infix(){ return ast::BinaryOperator::BackwardShiftAssign; }

    bool Token::is_opening_parenthesis() const { return false; }
    bool OpeningParenthesis::is_opening_parenthesis() const { return true; }
    bool Token::is_closing_parenthesis() const { return false; }
    bool ClosingParenthesis::is_closing_parenthesis() const { return true; }
    bool Token::is_opening_bracket() const { return false; }
    bool OpeningBracket::is_opening_bracket() const { return true; }
    bool Token::is_closing_bracket() const { return false; }
    bool ClosingBracket::is_closing_bracket() const { return true; }
    bool Token::is_opening_brace() const { return false; }
    bool OpeningBrace::is_opening_brace() const { return true; }
    bool Token::is_closing_brace() const { return false; }
    bool ClosingBrace::is_closing_brace() const { return true; }
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
        std::cout << "number (" << value << ")" << std::endl;
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


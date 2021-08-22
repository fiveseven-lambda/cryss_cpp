#include "token.hpp"

namespace token {
    Token::Token() = default;
    Token::~Token() = default;
    Identifier::Identifier(std::string &&name):
        name(std::move(name)) {}
    Integer::Integer(std::int32_t value):
        value(value) {}
    Real::Real(double value):
        value(value) {}
    String::String(std::string &&value):
        value(std::move(value)) {}

    std::optional<std::string> Token::identifier(){ return std::nullopt; }
    std::optional<std::string> Identifier::identifier(){ return std::move(name); }

    std::unique_ptr<syntax::Expression> Token::factor(){ return nullptr; }
    std::unique_ptr<syntax::Expression> Identifier::factor(){ return std::make_unique<syntax::Identifier>(std::move(name)); }
    std::unique_ptr<syntax::Expression> Integer::factor(){ return std::make_unique<syntax::Integer>(value); }
    std::unique_ptr<syntax::Expression> Real::factor(){ return std::make_unique<syntax::Real>(value); }
    std::unique_ptr<syntax::Expression> String::factor(){ return std::make_unique<syntax::String>(std::move(value)); }

    std::optional<syntax::UnaryOperator> Token::prefix(){ return std::nullopt; }
    std::optional<syntax::UnaryOperator> Hyphen::prefix(){ return syntax::UnaryOperator::Minus; }
    std::optional<syntax::UnaryOperator> Slash::prefix(){ return syntax::UnaryOperator::Reciprocal; }
    std::optional<syntax::UnaryOperator> Exclamation::prefix(){ return syntax::UnaryOperator::Not; }

    std::optional<syntax::BinaryOperator> Token::binary_operator(){ return std::nullopt; }
    std::optional<syntax::BinaryOperator> Plus::binary_operator(){ return syntax::BinaryOperator::Add; }
    std::optional<syntax::BinaryOperator> Hyphen::binary_operator(){ return syntax::BinaryOperator::Sub; }
    std::optional<syntax::BinaryOperator> Asterisk::binary_operator(){ return syntax::BinaryOperator::Mul; }
    std::optional<syntax::BinaryOperator> Slash::binary_operator(){ return syntax::BinaryOperator::Div; }
    std::optional<syntax::BinaryOperator> Percent::binary_operator(){ return syntax::BinaryOperator::Rem; }
    std::optional<syntax::BinaryOperator> DoubleEqual::binary_operator(){ return syntax::BinaryOperator::Equal; }
    std::optional<syntax::BinaryOperator> ExclamationEqual::binary_operator(){ return syntax::BinaryOperator::NotEqual; }
    std::optional<syntax::BinaryOperator> Less::binary_operator(){ return syntax::BinaryOperator::Less; }
    std::optional<syntax::BinaryOperator> LessEqual::binary_operator(){ return syntax::BinaryOperator::LessEqual; }
    std::optional<syntax::BinaryOperator> DoubleLess::binary_operator(){ return syntax::BinaryOperator::LeftShift; }
    std::optional<syntax::BinaryOperator> TripleLess::binary_operator(){ return syntax::BinaryOperator::BackwardShift; }
    std::optional<syntax::BinaryOperator> Greater::binary_operator(){ return syntax::BinaryOperator::Greater; }
    std::optional<syntax::BinaryOperator> GreaterEqual::binary_operator(){ return syntax::BinaryOperator::GreaterEqual; }
    std::optional<syntax::BinaryOperator> DoubleGreater::binary_operator(){ return syntax::BinaryOperator::RightShift; }
    std::optional<syntax::BinaryOperator> TripleGreater::binary_operator(){ return syntax::BinaryOperator::ForwardShift; }
    std::optional<syntax::BinaryOperator> Ampersand::binary_operator(){ return syntax::BinaryOperator::BitAnd; }
    std::optional<syntax::BinaryOperator> DoubleAmpersand::binary_operator(){ return syntax::BinaryOperator::LogicalAnd; }
    std::optional<syntax::BinaryOperator> Bar::binary_operator(){ return syntax::BinaryOperator::BitOr; }
    std::optional<syntax::BinaryOperator> DoubleBar::binary_operator(){ return syntax::BinaryOperator::LogicalOr; }
    std::optional<syntax::BinaryOperator> Circumflex::binary_operator(){ return syntax::BinaryOperator::Xor; }

    bool Token::is_question(){ return false; }
    bool Question::is_question(){ return true; }
    bool Token::is_opening_parenthesis(){ return false; }
    bool OpeningParenthesis::is_opening_parenthesis(){ return true; }
    bool Token::is_closing_parenthesis(){ return false; }
    bool ClosingParenthesis::is_closing_parenthesis(){ return true; }
    bool Token::is_semicolon(){ return false; }
    bool Semicolon::is_semicolon(){ return true; }
    bool Token::is_equal(){ return false; }
    bool Equal::is_equal(){ return true; }
    bool Token::is_keyword_let(){ return false; }
    bool KeywordLet::is_keyword_let(){ return true; }
}

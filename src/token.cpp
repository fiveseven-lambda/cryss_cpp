#include <string>
#include <cstddef>
#include <iostream>

#include "token.hpp"

namespace token {
    Token::Token(pos::Range &&range):
        range(range) {}
    Token::~Token() = default;

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
    String::String(pos::Range &&range, std::string value):
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

    // 動作確認用，あとで消す
    void Token::print_all(const std::string &log){
        print();
        std::cout << range << ": " << range.substr(log) << std::endl;
    }
    void Identifier::print(){
        std::cout << "Identifier(" << name << ")" << std::endl;
    }
    void Integer::print(){
        std::cout << "Integer(" << value << ")" << std::endl;
    }
    void Real::print(){
        std::cout << "Real(" << value << ")" << std::endl;
    }
    void String::print(){
        std::cout << "String(" << value << ")" << std::endl;
    }
    void Plus::print(){
        std::cout << "Plus" << std::endl;
    }
    void Hyphen::print(){
        std::cout << "Hyphen" << std::endl;
    }
    void Asterisk::print(){
        std::cout << "Asterisk" << std::endl;
    }
    void Slash::print(){
        std::cout << "Slash" << std::endl;
    }
    void Percent::print(){
        std::cout << "Percent" << std::endl;
    }
    void Circumflex::print(){
        std::cout << "Circumflex" << std::endl;
    }
    void Equal::print(){
        std::cout << "Equal" << std::endl;
    }
    void DoubleEqual::print(){
        std::cout << "DoubleEqual" << std::endl;
    }
    void Exclamation::print(){
        std::cout << "Exclamation" << std::endl;
    }
    void ExclamationEqual::print(){
        std::cout << "ExclamationEqual" << std::endl;
    }
    void Less::print(){
        std::cout << "Less" << std::endl;
    }
    void LessEqual::print(){
        std::cout << "LessEqual" << std::endl;
    }
    void DoubleLess::print(){
        std::cout << "DoubleLess" << std::endl;
    }
    void Greater::print(){
        std::cout << "Greater" << std::endl;
    }
    void GreaterEqual::print(){
        std::cout << "GreaterEqual" << std::endl;
    }
    void DoubleGreater::print(){
        std::cout << "DoubleGreater" << std::endl;
    }
    void Ampersand::print(){
        std::cout << "Ampersand" << std::endl;
    }
    void DoubleAmpersand::print(){
        std::cout << "DoubleAmpersand" << std::endl;
    }
    void Bar::print(){
        std::cout << "Bar" << std::endl;
    }
    void DoubleBar::print(){
        std::cout << "DoubleBar" << std::endl;
    }
    void Colon::print(){
        std::cout << "Colon" << std::endl;
    }
    void Semicolon::print(){
        std::cout << "Semicolon" << std::endl;
    }
    void Comma::print(){
        std::cout << "Comma" << std::endl;
    }
    void Dot::print(){
        std::cout << "Dot" << std::endl;
    }
    void Question::print(){
        std::cout << "Question" << std::endl;
    }
    void OpeningParenthesis::print(){
        std::cout << "OpeningParenthesis" << std::endl;
    }
    void ClosingParenthesis::print(){
        std::cout << "ClosingParenthesis" << std::endl;
    }
    void OpeningBracket::print(){
        std::cout << "OpeningBracket" << std::endl;
    }
    void ClosingBracket::print(){
        std::cout << "ClosingBracket" << std::endl;
    }
    void OpeningBrace::print(){
        std::cout << "OpeningBrace" << std::endl;
    }
    void ClosingBrace::print(){
        std::cout << "ClosingBrace" << std::endl;
    }
}

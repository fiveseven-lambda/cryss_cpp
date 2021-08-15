#include <cmath>
#include <vector>
#include <limits>
#include "error.hpp"
#include "lexer.hpp"

Lexer::Lexer():
    input(std::cin, true) {}
Lexer::Lexer(std::ifstream &file):
    input(file, false) {}

static std::int32_t to_digit(int c){
    if('0' <= c && c <= '9'){
        return c - '0';
    }else switch(c){
        case 'A': case 'a': return 10;
        case 'B': case 'b': return 11;
        case 'C': case 'c': return 12;
        case 'D': case 'd': return 13;
        case 'E': case 'e': return 14;
        case 'F': case 'f': return 15;
        default: return std::numeric_limits<std::int32_t>::max();
    }
}

std::pair<pos::Range, std::unique_ptr<token::Token>> &Lexer::peek(std::string &log){
    if(!peeked){
        std::unique_ptr<token::Token> token;
        while(std::isspace(input.peek().second)) input.get(log);
        auto [start, first] = input.get(log);
        auto exponent = [&]() -> double {
            bool minus = false;
            if(auto c = input.peek().second; c == '+' || c == '-'){
                input.get(log);
                if(c == '-') minus = true;
            }
            auto [pos, first] = input.get(log);
            if(!std::isdigit(first)) throw error::make<error::IncompleteScientificNotation>(pos::Range(start, pos));
            int ret = first - '0';
            while(true){
                auto c = input.peek().second;
                if(std::isdigit(c)){
                    input.get(log);
                    ret = ret * 10 + (c - '0');
                }else{
                    if(minus) ret = -ret;
                    return ret;
                }
            }
        };
        auto decimal = [&](double value) -> double {
            double tmp = 1;
            while(true){
                auto c = input.peek().second;
                if(std::isdigit(c)){
                    input.get(log);
                    value += (tmp *= .1) * (c - '0');
                }else if(c == 'e' || c == 'E'){
                    input.get(log);
                    return value* std::pow(10, exponent());
                }else{
                    return value;
                }
            }
        };
        if(first == EOF){
            token = nullptr;
        }else if(std::isalpha(first)){
            std::string name(1, std::char_traits<char>::to_char_type(first));
            while(std::isalnum(input.peek().second))
                name.push_back(std::char_traits<char>::to_char_type(input.get(log).second));
            token = std::make_unique<token::Identifier>(std::move(name));
        }else if(first == '"'){
            std::string name;
            int c;
            while((c = input.get(log).second) != '"'){
                if(c == EOF) throw error::make<error::UnterminatedStringLiteral>(std::move(start));
                if(c == '\\'){
                    c = input.get(log).second;
                    switch(c){
                        case 'n': c = '\n'; break;
                        case 'r': c = '\r'; break;
                        case 't': c = '\t'; break;
                        case '0': c = '\0'; break;
                    }
                }
                name.push_back(std::char_traits<char>::to_char_type(c));
            }
            token = std::make_unique<token::String>(std::move(name));
        }else if(first == '/'){
            auto c = input.peek().second;
            if(c == '*'){
                // コメントの開始 `/*` の `*` を peek 中
                input.get(log); // `*` を get
                std::vector<pos::Pos> comment(1, start); // コメント開始位置： `/`
                while(!comment.empty()){
                    auto [pos, c] = input.get(log);
                    if(c == EOF){
                        throw error::make<error::UnterminatedComment>(std::move(comment.back()));
                    }else if(c == '*'){
                        if(input.peek().second == '/'){
                            input.get(log);
                            comment.pop_back();
                        }
                    }else if(c == '/'){
                        if(input.peek().second == '*'){
                            input.get(log);
                            comment.push_back(pos);
                        }
                    }
                }
                return peek(log);
            }else if(c == '/'){
                input.get(log);
                while(input.get(log).second != '\n');
                return peek(log);
            }else{
                token = std::make_unique<token::Slash>();
            }
        }else if(first == '='){
            if(input.peek().second == '='){
                input.get(log);
                token = std::make_unique<token::DoubleEqual>();
            }else{
                token = std::make_unique<token::Equal>();
            }
        }else if(first == '!'){
            if(input.peek().second == '='){
                input.get(log);
                token = std::make_unique<token::ExclamationEqual>();
            }else{
                token = std::make_unique<token::Exclamation>();
            }
        }else if(first == '<'){
            auto c = input.peek().second;
            if(c == '='){
                input.get(log);
                token = std::make_unique<token::LessEqual>();
            }else if(c == '<'){
                input.get(log); // 2 文字目 get
                if(input.peek().second == '<'){
                    input.get(log); // 3 文字目 get
                    token = std::make_unique<token::TripleLess>();
                }else{
                    token = std::make_unique<token::DoubleLess>();
                }
            }else{
                token = std::make_unique<token::Less>();
            }
        }else if(first == '>'){
            auto c = input.peek().second;
            if(c == '='){
                input.get(log);
                token = std::make_unique<token::GreaterEqual>();
            }else if(c == '>'){
                input.get(log); // 2 文字目 get
                if(input.peek().second == '>'){
                    input.get(log); // 3 文字目 get
                    token = std::make_unique<token::TripleGreater>();
                }else{
                    token = std::make_unique<token::DoubleGreater>();
                }
            }else{
                token = std::make_unique<token::Greater>();
            }
        }else if(first == '&'){
            if(input.peek().second == '&'){
                input.get(log);
                token = std::make_unique<token::DoubleAmpersand>();
            }else{
                token = std::make_unique<token::Ampersand>();
            }
        }else if(first == '|'){
            if(input.peek().second == '|'){
                input.get(log);
                token = std::make_unique<token::DoubleBar>();
            }else{
                token = std::make_unique<token::Bar>();
            }
        }else if(first == '.'){
            if(!std::isdigit(input.peek().second)){
                token = std::make_unique<token::Dot>();
            }else{
                token = std::make_unique<token::Real>(decimal(0));
            }
        }else if(first == '+') token = std::make_unique<token::Plus>();
        else if(first == '-') token = std::make_unique<token::Hyphen>();
        else if(first == '*') token = std::make_unique<token::Asterisk>();
        else if(first == '%') token = std::make_unique<token::Percent>();
        else if(first == '^') token = std::make_unique<token::Circumflex>();
        else if(first == ':') token = std::make_unique<token::Colon>();
        else if(first == ';') token = std::make_unique<token::Semicolon>();
        else if(first == ',') token = std::make_unique<token::Comma>();
        else if(first == '?') token = std::make_unique<token::Question>();
        else if(first == '(') token = std::make_unique<token::OpeningParenthesis>();
        else if(first == ')') token = std::make_unique<token::ClosingParenthesis>();
        else if(first == '[') token = std::make_unique<token::OpeningBracket>();
        else if(first == ']') token = std::make_unique<token::ClosingBracket>();
        else if(first == '{') token = std::make_unique<token::OpeningBrace>();
        else if(first == '}') token = std::make_unique<token::ClosingBrace>();
        else if(std::isdigit(first)) do{
            if(first == '0'){
                auto c = input.peek().second;
                std::int32_t radix;
                switch(c){
                    case 'b': radix = 2; break;
                    case 'o': radix = 8; break;
                    case 'x': radix = 16; break;
                    default: radix = 0;
                }
                if(radix){
                    input.get(log);
                    std::int32_t value = 0;
                    while(true){
                        auto digit = to_digit(input.peek().second);
                        if(digit >= radix) break;
                        input.get(log);
                        value = value * radix + digit;
                    }
                    token = std::make_unique<token::Integer>(value);
                    break;
                }
            }
            std::int32_t value = first - '0';
            int c;
            while(std::isdigit(c = input.peek().second)){
                input.get(log);
                value = value * 10 + (c - '0');
            }
            if(c == '.'){
                input.get(log);
                token = std::make_unique<token::Real>(decimal(value));
            }else if(c == 'e' || c == 'E'){
                input.get(log);
                token = std::make_unique<token::Real>(value * std::pow(10, exponent()));
            }else{
                token = std::make_unique<token::Integer>(value);
            }
        }while(false); else{
            if(first >= 0xF0) input.get(log);
            if(first >= 0xE0) input.get(log);
            if(first >= 0xC0) input.get(log);
            throw error::make<error::UnexpectedCharacter>(pos::Range(start, input.peek().first));
        }
        peeked = std::make_pair(pos::Range(start, input.peek().first), std::move(token));
    }
    return peeked.value();
}

std::pair<pos::Range, std::unique_ptr<token::Token>> Lexer::next(std::string &log) {
    peek(log);
    auto ret = std::move(peeked).value();
    peeked = std::nullopt;
    return ret;
}

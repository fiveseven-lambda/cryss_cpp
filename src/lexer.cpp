#include <vector>
#include "error.hpp"
#include "lexer.hpp"

Lexer::Lexer():
    input(std::cin, true) {}
Lexer::Lexer(std::ifstream &file):
    input(file, false) {}

std::pair<pos::Range, std::unique_ptr<token::Token>> &Lexer::peek(std::string &log){
    if(!peeked){
        std::unique_ptr<token::Token> token;
        while(std::isspace(input.peek().second)) input.get(log);
        auto [start, first] = input.get(log);
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
                if(c == EOF){
                    throw static_cast<std::unique_ptr<error::Error>>(std::make_unique<error::UnterminatedStringLiteral>(std::move(start)));
                }else if(c == '\\'){
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
        }else if(first == '+'){
            token = std::make_unique<token::Plus>();
        }else if(first == '-'){
            token = std::make_unique<token::Hyphen>();
        }else if(first == '*'){
            token = std::make_unique<token::Asterisk>();
        }else if(first == '/'){
            auto c = input.peek().second;
            if(c == '*'){
                // コメントの開始 `/*` の `*` を peek 中
                input.get(log); // `*` を get
                std::vector<pos::Pos> comment(1, start); // コメント開始位置： `/`
                while(!comment.empty()){
                    auto [pos, c] = input.get(log);
                    if(c == EOF){
                        throw static_cast<std::unique_ptr<error::Error>>(std::make_unique<error::UnterminatedComment>(std::move(comment.back())));
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
        }else if(first == '%'){
            token = std::make_unique<token::Asterisk>();
        }else if(first == '^'){
            token = std::make_unique<token::Circumflex>();
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
        }else if(first == ':'){
            token = std::make_unique<token::Colon>();
        }else if(first == ';'){
            token = std::make_unique<token::Semicolon>();
        }else if(first == ','){
            token = std::make_unique<token::Comma>();
        }else if(first == '?'){
            token = std::make_unique<token::Question>();
        }else if(first == '('){
            token = std::make_unique<token::OpeningParenthesis>();
        }else if(first == ')'){
            token = std::make_unique<token::ClosingParenthesis>();
        }else if(first == '['){
            token = std::make_unique<token::OpeningBracket>();
        }else if(first == ']'){
            token = std::make_unique<token::ClosingBracket>();
        }else if(first == '{'){
            token = std::make_unique<token::OpeningBrace>();
        }else if(first == '}'){
            token = std::make_unique<token::ClosingBrace>();
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

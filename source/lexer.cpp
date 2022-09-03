/**
 * @file lexer.cpp
 */
#include "lexer.hpp"
#include "error.hpp"

#include <iostream>

namespace lexer {
    /**
     * @brief 標準入力から読む．
     *
     * 1行読むたびに，プロンプトを出力する．
     */
    Lexer::Lexer():
        source(std::cin),
        prompt(true),
        is_beginning_of_sentence(true) {}
    /**
     * @brief 指定された `std::istream` から読む．
     *
     * プロンプトは出力しない．
     */
    Lexer::Lexer(std::istream &source):
        source(source),
        prompt(false) {}

    void Lexer::beginning_of_sentence(){
        is_beginning_of_sentence = true;
    }
    /**
     * @brief 今までに読んだ入力の記録を返す．
     */
    const std::vector<std::string> &Lexer::get_log() const {
        return log;
    }

    std::unique_ptr<token::Token> &Lexer::peek(){
        while(tokens.empty()){
            if(source){
                // まだ EOF に達していない
                // 次の行が何行目か
                auto line_num = log.size();
                // log に空の std::string を追加し，1 行読んで格納
                log.emplace_back();
                if(prompt){
                    if(is_beginning_of_sentence){
                        std::cout << "> ";
                        is_beginning_of_sentence = false;
                    }else{
                        std::cout << "+ ";
                    }
                }
                std::getline(source, log.back());
                // 字句解析を行う
                line_lexer.run(line_num, log.back(), tokens);
            }else{
                // EOF に達した
                // コメント中なら例外を投げる
                line_lexer.deal_with_eof();
                // トークンの代わりに nullptr を入れる
                tokens.emplace();
            }
        }
        // ここで tokens は空でない
        return tokens.front();
    }

    std::unique_ptr<token::Token> Lexer::next(){
        auto ret = std::move(peek());
        tokens.pop();
        return ret;
    }

    void LineLexer::run(
        std::size_t line_num,
        const std::string_view &line,
        std::queue<std::unique_ptr<token::Token>> &tokens
    ){
        std::size_t cursor = 0;
        auto advance_if = [&](char ch){
            bool ret = cursor < line.size() && line[cursor] == ch;
            if(ret) cursor++;
            return ret;
        };
        while(true){
            while(true){
                if(!comments.empty()){
                    if(cursor >= line.size() - 1){
                        return;
                    }else if(line[cursor] == '*' && line[cursor + 1] == '/'){
                        comments.pop_back();
                        cursor += 2;
                        continue;
                    }else if(line[cursor] == '/' && line[cursor + 1] == '*'){
                        comments.emplace_back(line_num, cursor);
                        cursor += 2;
                        continue;
                    }
                }else if(string){
                    if(cursor == line.size()){
                        string.value().second.push_back('\n');
                        return;
                    }else if(line[cursor] == '"'){
                        cursor++;
                        std::unique_ptr<token::Token> token = std::make_unique<token::String>(std::move(string.value().second));
                        token->pos = pos::Range(string.value().first, pos::Pos(line_num, cursor));
                        tokens.push(std::move(token));
                        string.reset();
                        continue;
                    }else{
                        char ch;
                        if(line[cursor] == '\\'){
                            if(cursor == line.size() - 1){
                                throw error::make<error::InvalidEscape>(pos::Pos(line_num, cursor));
                            }else{
                                cursor++;
                                switch(line[cursor]){
                                    case 'n': ch = '\n'; break;
                                    case 't': ch = '\t'; break;
                                    case 'r': ch = '\r'; break;
                                    case '0': ch = '\0'; break;
                                    default: ch = line[cursor];
                                }
                            }
                        }else{
                            ch = line[cursor];
                        }
                        string.value().second.push_back(ch);
                    }
                }else if(cursor == line.size()){
                    return;
                }else if(line[cursor] == '"'){
                    string.emplace(pos::Pos(line_num, cursor), "");
                }else if(!std::isspace(line[cursor])) break;
                ++cursor;
            }
            std::size_t start = cursor;
            std::unique_ptr<token::Token> token;
            if(std::isdigit(line[start])){
                while(std::isdigit(line[cursor])) cursor++;
                token = std::make_unique<token::Integer>(line.substr(start, cursor - start));
            }else if(std::isalpha(line[start]) || line[start] == '_' || line[start] == '$'){
                while(std::isalnum(line[cursor]) || line[cursor] == '_' || line[cursor] == '$') cursor++;
                token = std::make_unique<token::Identifier>(line.substr(start, cursor - start));
            }else if(advance_if('+')){
                if(advance_if('+')) token = std::make_unique<token::DoublePlus>();
                else if(advance_if('=')) token = std::make_unique<token::PlusEqual>();
                else token = std::make_unique<token::Plus>();
            }else if(advance_if('-')){
                if(advance_if('-')) token = std::make_unique<token::DoubleHyphen>();
                else if(advance_if('=')) token = std::make_unique<token::HyphenEqual>();
                else token = std::make_unique<token::Hyphen>();
            }else if(advance_if('*')){
                if(advance_if('=')) token = std::make_unique<token::AsteriskEqual>();
                else token = std::make_unique<token::Asterisk>();
            }else if(advance_if('/')){
                if(line[cursor] == '/'){
                    return;
                }else if(advance_if('*')){
                    comments.emplace_back(line_num, start);
                    continue;
                }else if(advance_if('=')) token = std::make_unique<token::SlashEqual>();
                else token = std::make_unique<token::Slash>();
            }else if(advance_if('%')){
                if(advance_if('=')) token = std::make_unique<token::PercentEqual>();
                else token = std::make_unique<token::Percent>();
            }else if(advance_if('=')){
                if(advance_if('=')) token = std::make_unique<token::DoubleEqual>();
                else token = std::make_unique<token::Equal>();
            }else if(advance_if('!')){
                if(advance_if('=')) token = std::make_unique<token::ExclamationEqual>();
                else token = std::make_unique<token::Exclamation>();
            }else if(advance_if('<')){
                if(advance_if('<')){
                    if(advance_if('<')){
                        if(advance_if('=')) token = std::make_unique<token::TripleLessEqual>();
                        else token = std::make_unique<token::TripleLess>();
                    }else if(advance_if('=')) token = std::make_unique<token::DoubleLessEqual>();
                    else token = std::make_unique<token::DoubleLess>();
                }else if(advance_if('=')) token = std::make_unique<token::LessEqual>();
                else token = std::make_unique<token::Less>();
            }else if(advance_if('>')){
                if(advance_if('>')){
                    if(advance_if('>')){
                        if(advance_if('=')) token = std::make_unique<token::TripleGreaterEqual>();
                        else token = std::make_unique<token::TripleGreater>();
                    }else if(advance_if('=')) token = std::make_unique<token::DoubleGreaterEqual>();
                    else token = std::make_unique<token::DoubleGreater>();
                }else if(advance_if('=')) token = std::make_unique<token::GreaterEqual>();
                else token = std::make_unique<token::Greater>();
            }else if(advance_if('&')){
                if(advance_if('&')) token = std::make_unique<token::DoubleAmpersand>();
                else if(advance_if('=')) token = std::make_unique<token::AmpersandEqual>();
                else token = std::make_unique<token::Ampersand>();
            }else if(advance_if('|')){
                if(advance_if('|')) token = std::make_unique<token::DoubleBar>();
                else if(advance_if('=')) token = std::make_unique<token::BarEqual>();
                else token = std::make_unique<token::Bar>();
            }else if(advance_if('^')){
                if(advance_if('=')) token = std::make_unique<token::CircumflexEqual>();
                else token = std::make_unique<token::Circumflex>();
            }else if(advance_if('.')) token = std::make_unique<token::Dot>();
            else if(advance_if(':')) token = std::make_unique<token::Colon>();
            else if(advance_if(';')) token = std::make_unique<token::Semicolon>();
            else if(advance_if(',')) token = std::make_unique<token::Comma>();
            else if(advance_if('?')) token = std::make_unique<token::Question>();
            else if(advance_if('#')) token = std::make_unique<token::Hash>();
            else if(advance_if('~')) token = std::make_unique<token::Tilde>();
            else if(advance_if('(')) token = std::make_unique<token::OpeningParenthesis>();
            else if(advance_if(')')) token = std::make_unique<token::ClosingParenthesis>();
            else if(advance_if('[')) token = std::make_unique<token::OpeningBracket>();
            else if(advance_if(']')) token = std::make_unique<token::ClosingBracket>();
            else if(advance_if('{')) token = std::make_unique<token::OpeningBrace>();
            else if(advance_if('}')) token = std::make_unique<token::ClosingBrace>();
            else throw error::make<error::UnexpectedCharacter>(pos::Pos(line_num, cursor));
            token->pos = pos::Range(line_num, start, cursor);
            tokens.push(std::move(token));
        }
    }

    void LineLexer::deal_with_eof(){
        if(!comments.empty()){
            throw error::make<error::UnterminatedComment>(std::move(comments));
        }
    }
}

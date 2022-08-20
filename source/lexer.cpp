/**
 * @file lexer.cpp
 */
#include "lexer.hpp"

#include <iostream>

namespace lexer {
    /**
     * @brief 標準入力から読む．
     *
     * 1行読むたびに，プロンプトを出力する．
     */
    Lexer::Lexer(): source(std::cin), prompt(true) {}
    /**
     * @brief 指定された `std::istream` から読む．
     *
     * プロンプトは出力しない．
     */
    Lexer::Lexer(std::istream &source): source(source), prompt(false) {}

    void Lexer::beginning_of_sentence(){
        is_beginning_of_sentence = true;
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
        auto advance_if = [&](char c){
            bool ret = cursor < line.size() && line[cursor] == c;
            if(ret) cursor++;
            return ret;
        };
        while(true){
            while(true){
                if(cursor == line.size()) return;
                if(!comments.empty()){
                    if(cursor < line.size() - 1){
                        if(line[cursor] == '*' && line[cursor + 1] == '/'){
                            comments.pop_back();
                            cursor += 2;
                            continue;
                        }else if(line[cursor] == '/' && line[cursor + 1] == '*'){
                            comments.emplace_back(line_num, cursor);
                            cursor += 2;
                            continue;
                        }
                    }
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
                token = std::make_unique<token::Plus>();
            }
            token->pos = pos::Range(line_num, start, cursor);
            tokens.push(std::move(token));
        }
    }

    void LineLexer::deal_with_eof(){
        if(!comments.empty()){
        }
    }
}

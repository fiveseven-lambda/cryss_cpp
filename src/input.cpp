#include <iostream>
#include "input.hpp"

Input::Input(std::istream &source, bool prompt):
    source(source),
    prompt(prompt),
    line(0),
    byte(0) {
    if(prompt) {
        std::cout << "> ";
    }
}

std::pair<pos::Pos, int> Input::peek(){
    return std::make_pair(pos::Pos(line, byte), source.peek());
}
std::pair<pos::Pos, int> Input::get(std::string &log){
    int c = source.get();
    if(c != EOF){
        // std::basic_istream::get() の仕様により EOF でないなら char の範囲に収まってる（はず？）
        // std::char_traits<char>::to_char_type() が何やってるかはよく分からない
        log.push_back(std::char_traits<char>::to_char_type(c));
    }
    auto ret = std::make_pair(pos::Pos(line, byte), c);
    ++byte;
    if(c == '\n'){
        ++line;
        if(prompt){
            std::cout << "> ";
        }
    }
    return ret;
}

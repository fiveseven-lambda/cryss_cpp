#include "pos.hpp"
#include "error.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "environment.hpp"

int main(){
    Lexer lexer;
    std::string log;

    environment::Environment environment;
    try{
        while(true){
            auto sentence = parse_sentence(lexer, log);
            if(!environment.run(std::move(sentence))){
                break;
            }
        }
    }catch(std::unique_ptr<error::Error> &err){
        err->print(log);
    }
}

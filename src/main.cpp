#include "pos.hpp"
#include "error.hpp"
#include "token.hpp"
#include "lexer.hpp"

int main(){
    Lexer lexer;
    std::string log;
    try{
        while(lexer.next(log).second);
    }catch(std::unique_ptr<error::Error> &err){
        err->print(log);
    }
}

#include "pos.hpp"
#include "error.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main(){
    Lexer lexer;
    std::string log;
    try{
        auto [range, expression] = parse_expression(lexer, log);
        if(expression){
            expression->print();
        }
    }catch(std::unique_ptr<error::Error> &err){
        err->print(log);
    }
}

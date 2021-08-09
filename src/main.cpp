#include "pos.hpp"
#include "error.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main(){
    Lexer lexer;
    std::string log;
    try {
        while(auto optional = parse_factor(lexer, log)) {
            optional.value()->print();
        }
    } catch(std::unique_ptr<error::Error> &err) {
        err->print(log);
    }
}

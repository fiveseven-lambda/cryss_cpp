#include "pos.h"
#include "error.h"
#include "lexer.h"

int main(){
    Lexer lexer;
    std::string log;
    try {
        while(auto optional = lexer.next(log)) {
            optional.value()->print(log);
        }
    } catch(std::unique_ptr<error::Error> &err) {
        err->print(log);
    }
}
#include "pos.hpp"
#include "error.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "environment.hpp"

#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

std::unique_ptr<llvm::orc::LLJIT> jit;

int main(){
    LLVMInitializeNativeTarget();
    jit = std::move(llvm::orc::LLJITBuilder().create().get());
    LLVMInitializeNativeAsmPrinter();

    Lexer lexer;
    std::string log;

    environment::Environment environment;
    try{
        while(true){
            auto sentence = parse_sentence(lexer, log);
            if(!sentence.second) break;
            environment.run(std::move(sentence));
        }
    }catch(std::unique_ptr<error::Error> &err){
        err->print(log);
    }
}

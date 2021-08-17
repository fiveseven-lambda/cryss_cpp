#include "context.hpp"
#include "environment.hpp"

namespace environment {
    Environment::Environment(){
    }
    bool Environment::run(syntax::PairRangeSentence sentence){
        if(!sentence.second) return false;
        auto module = std::make_unique<llvm::Module>("", *context.getContext());
        llvm::Function *function = llvm::Function::Create(llvm::FunctionType::get(integer_type, std::vector<llvm::Type *>(), false), llvm::Function::ExternalLinkage, "", module.get());
        llvm::BasicBlock *basic_block = llvm::BasicBlock::Create(*context.getContext(), "entry", function);
        builder->SetInsertPoint(basic_block);
        // builder->CreateRet(llvm::ConstantInt::get(integer_type, 0, true));
        sentence.second->compile(variables, sentence.first);
        module->print(llvm::errs(), nullptr);
        return true;
    }
}
#include "context.hpp"
#include "variable.hpp"

value::Value Variable::value() const {
    return value::Value(builder.CreateLoad(type->llvm_type(), ptr), type->clone());
}
Variable::Variable(std::unique_ptr<type::Type> type, llvm::Value *ptr):
    type(std::move(type)),
    ptr(ptr) {}

Variables declare(const GlobalVariables &global_variables, llvm::Module &module){
    Variables ret;
    for(auto &variable : global_variables){
        llvm::Value *ptr = new llvm::GlobalVariable(module, variable.second->llvm_type(), false, llvm::GlobalValue::ExternalLinkage, nullptr, variable.first);
        ret.emplace(variable.first, Variable(variable.second->clone(), ptr));
    }
    return ret;
}

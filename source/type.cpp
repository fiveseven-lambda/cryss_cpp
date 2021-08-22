
#include "type.hpp"
#include "context.hpp"
#include "llvm/IR/LLVMContext.h"

namespace type {
    Type::~Type() = default;
    Sound::Sound(std::unique_ptr<Type> element_type):
        element_type(std::move(element_type)) {}
    Iter::Iter(std::unique_ptr<Type> element_type):
        element_type(std::move(element_type)) {}
    Array::Array(std::unique_ptr<Type> element_type):
        element_type(std::move(element_type)) {}
    Function::Function(std::vector<std::unique_ptr<Type>> argument_types, std::unique_ptr<Type> result_type):
        argument_types(std::move(argument_types)),
        result_type(std::move(result_type)) {}
    llvm::Type *Boolean::llvm_type(){ return boolean_type; }
    llvm::Type *Integer::llvm_type(){ return integer_type; }
    llvm::Type *Real::llvm_type(){ return real_type; }
    llvm::Type *String::llvm_type(){ /* todo */ }
    llvm::Type *Sound::llvm_type(){ /* todo */ }
    llvm::Type *Iter::llvm_type(){ /* todo */ }
    llvm::Type *Array::llvm_type(){ /* todo */ }
    llvm::Type *Function::llvm_type(){ /* todo */ }
    std::unique_ptr<Type> Boolean::clone(){ return std::make_unique<Boolean>(); }
    std::unique_ptr<Type> Integer::clone(){ return std::make_unique<Integer>(); }
    std::unique_ptr<Type> Real::clone(){ return std::make_unique<Real>(); }
    std::unique_ptr<Type> String::clone(){ return std::make_unique<String>(); }
    std::unique_ptr<Type> Sound::clone(){ return std::make_unique<Sound>(element_type->clone()); }
    std::unique_ptr<Type> Iter::clone(){ return std::make_unique<Iter>(element_type->clone()); }
    std::unique_ptr<Type> Array::clone(){ return std::make_unique<Array>(element_type->clone()); }
    std::unique_ptr<Type> Function::clone(){
        std::vector<std::unique_ptr<Type>> new_argument_types(argument_types.size());
        for(std::size_t i = 0; i < argument_types.size(); ++i){
            new_argument_types[i] = argument_types[i]->clone();
        }
        return std::make_unique<Function>(std::move(new_argument_types), result_type->clone());
    }
    llvm::Value *Type::require(const std::unique_ptr<Type> &, llvm::Value *){ return nullptr; }
    llvm::Value *Boolean::require(const std::unique_ptr<Type> &type, llvm::Value *value){ return type->from_boolean(value); }
    llvm::Value *Integer::require(const std::unique_ptr<Type> &type, llvm::Value *value){ return type->from_integer(value); }
    llvm::Value *Real::require(const std::unique_ptr<Type> &type, llvm::Value *value){ return type->from_real(value); }
    llvm::Value *Type::from_boolean(llvm::Value *){ return nullptr; }
    llvm::Value *Boolean::from_boolean(llvm::Value *value){ return value; }
    llvm::Value *Type::from_integer(llvm::Value *){ return nullptr; }
    llvm::Value *Integer::from_integer(llvm::Value *value){ return value; }
    llvm::Value *Real::from_integer(llvm::Value *value){ return builder.CreateSIToFP(value, real_type); }
    llvm::Value *Type::from_real(llvm::Value *){ return nullptr; }
    llvm::Value *Real::from_real(llvm::Value *value){ return value; }

    llvm::Constant *Type::default_value(){
        // この関数は消す
        // いずれ純粋仮想関数に
        return llvm::ConstantInt::get(integer_type, 0);
    }
    llvm::Constant *Integer::default_value(){
        return llvm::ConstantInt::get(integer_type, 0);
    }
}

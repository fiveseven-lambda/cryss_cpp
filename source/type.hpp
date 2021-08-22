#ifndef TYPE_HPP
#define TYPE_HPP

#include <vector>
#include <memory>
#include <string>

#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

namespace type {
    class Type {
    public:
        virtual llvm::Type *llvm_type() = 0;
        virtual ~Type();
        virtual std::unique_ptr<Type> clone() = 0;
        virtual llvm::Value *require(std::unique_ptr<Type>, llvm::Value *);
        virtual llvm::Value *from_boolean(llvm::Value *), *from_integer(llvm::Value *), *from_real(llvm::Value *);
    };
    class Boolean : public Type {
    public:
        llvm::Type *llvm_type() override;
        std::unique_ptr<Type> clone() override;
        llvm::Value *require(std::unique_ptr<Type>, llvm::Value *) override;
        llvm::Value *from_boolean(llvm::Value *) override;
    };
    class Integer : public Type {
    public:
        llvm::Type *llvm_type() override;
        std::unique_ptr<Type> clone() override;
        llvm::Value *require(std::unique_ptr<Type>, llvm::Value *) override;
        llvm::Value *from_integer(llvm::Value *) override;
    };
    class Real : public Type {
    public:
        llvm::Type *llvm_type() override;
        std::unique_ptr<Type> clone() override;
        llvm::Value *require(std::unique_ptr<Type>, llvm::Value *) override;
        llvm::Value *from_real(llvm::Value *) override;
    };
    class String : public Type {
    public:
        llvm::Type *llvm_type() override;
        std::unique_ptr<Type> clone() override;
    };
    class Sound : public Type {
        std::unique_ptr<Type> element_type;
    public:
        llvm::Type *llvm_type() override;
        std::unique_ptr<Type> clone() override;
        Sound(std::unique_ptr<Type>);
    };
    class Iter : public Type {
        std::unique_ptr<Type> element_type;
    public:
        llvm::Type *llvm_type() override;
        std::unique_ptr<Type> clone() override;
        Iter(std::unique_ptr<Type>);
    };
    class Array : public Type {
        std::unique_ptr<Type> element_type;
    public:
        llvm::Type *llvm_type() override;
        std::unique_ptr<Type> clone() override;
        Array(std::unique_ptr<Type>);
    };
    class Function : public Type {
        std::vector<std::unique_ptr<Type>> argument_types;
    public:
        llvm::Type *llvm_type() override;
        std::unique_ptr<Type> result_type;
        std::unique_ptr<Type> clone() override;
        Function(std::vector<std::unique_ptr<Type>>, std::unique_ptr<Type>);
    };
}

#endif

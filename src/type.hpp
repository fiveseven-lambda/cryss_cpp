#ifndef TYPE_HPP
#define TYPE_HPP

#include <vector>
#include <memory>
#include <string>

#include <unordered_map>

#include "llvm/IR/Type.h"

namespace type {
    class Type {
        virtual llvm::Type *llvm_type() = 0;
    public:
        virtual ~Type();
    };
    class Boolean : public Type {
        llvm::Type *llvm_type() override;
    };
    class Integer : public Type {
        llvm::Type *llvm_type() override;
    };
    class Real : public Type {
        llvm::Type *llvm_type() override;
    };
    class String : public Type { };
    class Sound : public Type {
        std::unique_ptr<Type> element_type;
    };
    class Iter : public Type {
        std::unique_ptr<Type> element_type;
    };
    class Array : public Type {
        std::unique_ptr<Type> element_type;
    };
    class Function : public Type {
        std::vector<std::unique_ptr<Type>> argument_types;
        std::unique_ptr<Type> result_type;
    };
}

using Variables = std::unordered_map<std::string, type::Type>;

#endif

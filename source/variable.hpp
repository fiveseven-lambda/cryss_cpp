#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <unordered_map>
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "type.hpp"
#include "value.hpp"

class Variable {
    std::unique_ptr<type::Type> type;
    llvm::Value *ptr;
public:
    Variable(std::unique_ptr<type::Type>, llvm::Value *);
    value::Value value() const;
};

// 今のところ， cryss 上で宣言された変数名をそのまま LLVM でも同じ名前で宣言してる
// （いずれ変えそう）
using GlobalVariables = std::unordered_map<std::string, std::unique_ptr<type::Type>>;
using Variables = std::unordered_map<std::string, Variable>;

Variables declare(const GlobalVariables &, llvm::Module &);

#endif

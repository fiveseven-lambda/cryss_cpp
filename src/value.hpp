#ifndef VALUE_HPP
#define VALUE_HPP

#include "llvm/IR/Value.h"

namespace value {
    class Value {
        llvm::Value *value;
    public:
        Value(llvm::Value *);
        llvm::Value *require(llvm::Type *);
    };
}

#endif
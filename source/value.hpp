#ifndef VALUE_HPP
#define VALUE_HPP

#include "llvm/IR/Value.h"
#include "type.hpp"

namespace value {
    class Value {
    public: // 一時的に public にする，あとで消す
        llvm::Value *value;
        std::unique_ptr<type::Type> type;
    public:
        Value(llvm::Value *, std::unique_ptr<type::Type>);
        llvm::Value *require(std::unique_ptr<type::Type>);
    };
}

#endif

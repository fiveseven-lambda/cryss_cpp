
#include "value.hpp"

namespace value {
    Value::Value(llvm::Value *value):
        value(value) {}
    llvm::Value *Value::require(llvm::Type *type){
        if(value->getType() == type){
            return value;
        }
        return nullptr;
    }
}
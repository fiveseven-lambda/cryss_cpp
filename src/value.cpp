
#include "value.hpp"

namespace value {
    Value::Value(llvm::Value *value, std::unique_ptr<type::Type> type):
        value(value),
        type(std::move(type)) {}
    llvm::Value *Value::require(llvm::Type *type){
        if(value->getType() == type){
            return value;
        }
        return nullptr;
    }
}
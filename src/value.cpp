
#include "value.hpp"

namespace value {
    Value::Value(llvm::Value *value, std::unique_ptr<type::Type> type):
        value(value),
        type(std::move(type)) {}
    llvm::Value *Value::require(std::unique_ptr<type::Type> required){
        return nullptr;
    }
}

#include "value.hpp"

namespace value {
    Value::Value(llvm::Value *value, std::unique_ptr<type::Type> type):
        value(value),
        type(std::move(type)) {}
    llvm::Value *Value::require(std::unique_ptr<type::Type> required){
        // type が bool, required が bool → value を返す
        // type が bool, required が integer → value をキャストして返す
        return type->require(std::move(required), value);
    }
}

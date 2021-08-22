
#include "value.hpp"

namespace value {
    Value::Value(llvm::Value *value, std::unique_ptr<type::Type> type):
        value(value),
        type(std::move(type)) {}
    llvm::Value *Value::require(const std::unique_ptr<type::Type> &required){
        // type が bool, required が bool → value を返す
        // type が bool, required が integer → value をキャストして返す
        return type->require(required, value);
    }
    std::unique_ptr<type::Type> Value::get_type(){
        return type->clone();
    }
}

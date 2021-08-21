
#include "type.hpp"
#include "llvm/IR/LLVMContext.h"

extern llvm::Type *boolean_type, *integer_type, *real_type;

namespace type {
    Type::~Type() = default;
    llvm::Type *Boolean::llvm_type(){
        return boolean_type;
    }
    llvm::Type *Integer::llvm_type(){
        return integer_type;
    }
    llvm::Type *Real::llvm_type(){
        return real_type;
    }
}
#include "context.hpp"

// todo: 名前空間で包め

llvm::orc::ThreadSafeContext context(std::make_unique<llvm::LLVMContext>());
llvm::IRBuilder<> builder(*context.getContext());
llvm::Type *boolean_type = llvm::Type::getInt1Ty(*context.getContext());
llvm::Type *integer_type = llvm::Type::getInt32Ty(*context.getContext());
llvm::Type *real_type = llvm::Type::getDoubleTy(*context.getContext());

llvm::FunctionType *function_type = llvm::FunctionType::get(integer_type, false);
#include "context.hpp"

llvm::orc::ThreadSafeContext context(std::make_unique<llvm::LLVMContext>());
auto builder = std::make_unique<llvm::IRBuilder<>>(*context.getContext());
llvm::IntegerType *integer_type = llvm::Type::getInt32Ty(*context.getContext());
llvm::Type *double_type = llvm::Type::getDoubleTy(*context.getContext());
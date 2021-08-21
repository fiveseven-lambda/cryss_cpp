#include "context.hpp"

llvm::orc::ThreadSafeContext context(std::make_unique<llvm::LLVMContext>());
auto builder = std::make_unique<llvm::IRBuilder<>>(*context.getContext());
llvm::Type *boolean_type = llvm::Type::getInt1Ty(*context.getContext());
llvm::Type *integer_type = llvm::Type::getInt32Ty(*context.getContext());
llvm::Type *real_type = llvm::Type::getDoubleTy(*context.getContext());
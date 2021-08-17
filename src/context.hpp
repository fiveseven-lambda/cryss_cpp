#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <memory>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/ConstantFolder.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"

extern llvm::orc::ThreadSafeContext context;
extern std::unique_ptr<llvm::IRBuilder<llvm::ConstantFolder, llvm::IRBuilderDefaultInserter>> builder;

extern llvm::IntegerType *integer_type;
extern llvm::Type *double_type;

#endif
#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <memory>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/ConstantFolder.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"

extern llvm::orc::ThreadSafeContext context;
extern llvm::IRBuilder<llvm::ConstantFolder, llvm::IRBuilderDefaultInserter> builder;

extern llvm::Type *boolean_type, *integer_type, *real_type;

extern std::unique_ptr<llvm::orc::LLJIT> jit;

extern llvm::FunctionType *function_type;

#endif

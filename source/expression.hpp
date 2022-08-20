/**
 * @file expression.hpp
 */
#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <utility>
#include "llvm/IR/Value.h"

#include "pos.hpp"
#include "type.hpp"

namespace expression {
    class Expression {
    public:
        pos::Range pos;
        virtual ~Expression();
        /**
         * @brief 左辺値
         * @todo 引数に何が必要か考える．
         * リテラルの型を得るために `TypeContext` は必要．
         */
        virtual std::pair<const type::Type &, llvm::Value *> lvalue() = 0;
        /**
         * @brief 右辺値
         * @todo 引数に何が必要か考える
         */
        virtual std::pair<const type::Type &, llvm::Value *> rvalue() = 0;
    };
}

#endif

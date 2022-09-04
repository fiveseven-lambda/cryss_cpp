/**
 * @file pre_stmt.hpp
 */

#ifndef PRE_STMT_HPP
#define PRE_STMT_HPP

#include "pre_expr.hpp"

namespace pre_stmt {
    class Stmt {
    public:
        pos::Range pos;
        virtual ~Stmt();
#ifdef DEBUG
        virtual void debug_print(int = 0) const = 0;
#endif
    };
    class Expr : public Stmt {
        std::unique_ptr<pre_expr::Expr> expr;
    public:
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Decl : public Stmt {
        std::unique_ptr<pre_expr::Expr> left, right;
    public:
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
}

#endif

/**
 * @file pre_expr.hpp
 */

#ifndef PRE_EXPR_HPP
#define PRE_EXPR_HPP

#include "pos.hpp"
#include <memory>

namespace pre_expr {
    /**
     * @brief 全ての式の基底クラス
     */
    class Expr {
    public:
        pos::Range pos;
        virtual ~Expr();
#ifdef DEBUG
        virtual void debug_print(int = 0) const = 0;
#endif
    };
    /**
     * @brief 単一の識別子からなる式
     */
    class Identifier : public Expr {
        std::string_view name;
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    /**
     * @brief 単一の整数リテラルからなる式
     */
    class Integer : public Expr {
        std::string_view value;
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    /**
     * @brief 単一の小数リテラルからなる式
     */
    class Decimal : public Expr {
        std::string_view value;
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    /**
     * @brief 単一の文字列リテラルからなる式
     */
    class String : public Expr {
        std::string_view value;
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    enum class UnaryOperator {
        Plus,
        Minus,
        PreInc,
        PreDec,
        PostInc,
        PostDec,
        Recip,
        LogicalNot,
        BitNot,
        Print,
    };
    class UnaryOperation : public Expr {
        UnaryOperator unary_operator;
        std::unique_ptr<Expr> operand;
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    enum class BinaryOperator {
        Add,
        AddAssign,
        Sub,
        SubAssign,
        Mul,
        MulAssign,
        Div,
        DivAssign,
        Rem,
        RemAssign,
        Assign,
        Equal,
        NotEqual,
        Less,
        LessEqual,
        LeftShift,
        LeftShiftAssign,
        BackwardShift,
        BackwardShiftAssign,
        Greater,
        GreaterEqual,
        RightShift,
        RightShiftAssign,
        ForwardShift,
        ForwardShiftAssign,
        BitAnd,
        BitAndAssign,
        LogicalAnd,
        BitOr,
        BitOrAssign,
        LogicalOr,
        BitXor,
        BitXorAssign,
    };
    class BinaryOperation : public Expr {
        BinaryOperator binary_operator;
        std::unique_ptr<Expr> left, right;
    public:
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Group : public Expr {
        std::unique_ptr<Expr> expression;
    public:
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Call : public Expr {
        std::unique_ptr<Expr> function;
        std::vector<std::unique_ptr<Expr>> arguments;
    public:
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
}

#endif

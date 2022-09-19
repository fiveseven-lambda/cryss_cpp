/**
 * @file ast.hpp
 * @brief AST を定義する．
 */
#ifndef AST_HPP
#define AST_HPP

#include <string_view>
#include <memory>

#include "pos.hpp"

namespace ast {
    namespace type {
        class Type {
        public:
            pos::Range pos;
            virtual ~Type();
        };
        class Identifier : public Type {
            std::string_view name;
        };
        class List : public Type {
            std::unique_ptr<Type> elem;
        };
        class Sound : public Type {
            std::unique_ptr<Type> result;
        };
    }
    class TopLevel {
    public:
        pos::Range pos;
        virtual ~TopLevel();
#ifdef DEBUG
        virtual void debug_print(int) const = 0;
#endif
    };
    class Stmt : public TopLevel {
    public:
        virtual ~Stmt() override;
#ifdef DEBUG
        virtual void debug_print(int) const override = 0;
#endif
    };
    class Expr {
    public:
        pos::Range pos;
        virtual ~Expr();
#ifdef DEBUG
        virtual void debug_print(int) const = 0;
#endif
    };
    class Identifier : public Expr {
        std::string_view name;
    public:
        Identifier(std::string_view);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Number : public Expr {
        std::string_view value;
    public:
        Number(std::string_view);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class String : public Expr {
        std::string value;
    public:
        String(std::string);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Call : public Expr {
        std::unique_ptr<Expr> func;
        std::vector<std::unique_ptr<Expr>> args;
    public:
        Call(std::unique_ptr<Expr>, std::vector<std::unique_ptr<Expr>>);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    enum class UnaryOperator {
        Plus,
        Minus,
        Recip,
        LogicalNot,
        BitNot,
        PreInc,
        PreDec,
        PostInc,
        PostDec,
    };
    class UnaryOperation : public Expr {
        UnaryOperator op;
        std::unique_ptr<Expr> operand;
    public:
        UnaryOperation(UnaryOperator, std::unique_ptr<Expr>);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    enum class BinaryOperator {
        Add,
        Sub,
        Mul,
        Div,
        Rem,
        LeftShift,
        RightShift,
        ForwardShift,
        BackwardShift,
        Equal,
        NotEqual,
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        LogicalAnd,
        LogicalOr,
        BitAnd,
        BitOr,
        BitXor,
        Assign,
        AddAssign,
        SubAssign,
        MulAssign,
        DivAssign,
        RemAssign,
        BitAndAssign,
        BitOrAssign,
        BitXorAssign,
        LeftShiftAssign,
        RightShiftAssign,
        ForwardShiftAssign,
        BackwardShiftAssign,
    };
    class BinaryOperation : public Expr {
        BinaryOperator op;
        std::unique_ptr<Expr> left, right;
    public:
        BinaryOperation(BinaryOperator, std::unique_ptr<Expr>, std::unique_ptr<Expr>);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Index : public Expr {
        std::unique_ptr<Expr> operand;
        std::unique_ptr<Expr> index;
    public:
        Index(std::unique_ptr<Expr>, std::unique_ptr<Expr>);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Group : public Expr {
        std::unique_ptr<Expr> expr;
    public:
        Group(std::unique_ptr<Expr>);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class List : public Expr {
        std::vector<std::unique_ptr<Expr>> elems;
    public:
        List(std::vector<std::unique_ptr<Expr>>);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Tuple : public Expr {
        std::vector<std::unique_ptr<Expr>> elems;
    public:
        Tuple(std::vector<std::unique_ptr<Expr>>);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class ExprStmt : public Stmt {
        std::unique_ptr<Expr> expr;
    public:
        ExprStmt(std::unique_ptr<Expr>);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Decl : public Stmt {
        std::string_view name;
        std::unique_ptr<type::Type> type;
        std::unique_ptr<Expr> expr;
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Break : public Stmt {
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Continue : public Stmt {
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Return : public Stmt {
        std::unique_ptr<Expr> expr;
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class Block : public Stmt {
        std::vector<std::unique_ptr<Stmt>> stmts;
    public:
        Block(std::vector<std::unique_ptr<Stmt>>);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class While : public Stmt {
        std::unique_ptr<Expr> cond;
        std::unique_ptr<Stmt> stmt;
    public:
        While(std::unique_ptr<Expr>, std::unique_ptr<Stmt>);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class If : public Stmt {
        std::unique_ptr<Expr> cond;
        std::unique_ptr<Stmt> stmt_true;
        std::unique_ptr<Stmt> stmt_false;
    public:
        If(std::unique_ptr<Expr>, std::unique_ptr<Stmt>, std::unique_ptr<Stmt>);
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class DefExpr : public TopLevel {
        std::string_view name;
        std::vector<std::pair<std::string_view, std::unique_ptr<type::Type>>> args;
        std::unique_ptr<type::Type> type;
        std::unique_ptr<Expr> expr;
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
    class DefBlock : public TopLevel {
        std::string_view name;
        std::vector<std::pair<std::string_view, std::unique_ptr<type::Type>>> args;
        std::unique_ptr<type::Type> type;
        std::vector<std::unique_ptr<Stmt>> stmts;
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };
}

#endif

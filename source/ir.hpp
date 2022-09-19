/**
 * @file ir.hpp
 * @brief IR を定義する．
 */
#ifndef IR_HPP
#define IR_HPP

#include <vector>
#include <memory>

namespace ir {
    /**
     * @brief 式
     */
    class Expr {
    public:
        virtual ~Expr();
    };
    /**
     * @brief 値
     */
    class Value : public Expr {
    public:
        virtual ~Value() override;
    };
    /**
     * @brief 関数
     */
    class Func : public Value {
    public:
        virtual ~Func() override;
    };
    /**
     * @brief 音
     */
    class Sound : public Value {
    public:
        virtual ~Sound() override;
    };
    /**
     * @brief 音 T
     */
    class T : public Sound {
    };
    /**
     * @brief 音，定数
     */
    class Const : public Sound {
        std::shared_ptr<Value> value;
    };
    /**
     * @brief 音，関数適用
     */
    class App : public Sound {
        std::shared_ptr<Func> func;
        std::vector<std::unique_ptr<Sound>> args;
    };
    /**
     * @brief ブロックの終端
     */
    class Term {
    public:
        virtual ~Term();
    };
    /**
     * @brief 関数からの値返し
     */
    class Ret : public Term {
        std::unique_ptr<Expr> expr;
    };
    /**
     * @brief ジャンプ
     */
    class Jmp : public Term {
        std::size_t dest;
    };
    /**
     * @brief 条件分岐
     */
    class Br : public Term {
        std::unique_ptr<Expr> cond;
        std::size_t dest_true, dest_false;
    };
    /**
     * @brief 式で定義された関数
     */
    class Def : public Func {
        std::vector<std::pair<std::vector<std::unique_ptr<Expr>>, std::unique_ptr<Term>>> blocks;
    };
    /**
     * @brief bool 値
     */
    class Bool : public Value {
        bool value;
    };
    /**
     * @brief int 値
     */
    class Int : public Value {
        int value;
    };
    /**
     * @brief rational 値
     */
    class Rational : public Value {
        int numer, denom;
    };
    /**
     * @brief float 値
     */
    class Float : public Value {
        double value;
    };
    /**
     * @brief str 値
     */
    class Str : public Value {
        std::string value;
    };
    /**
     * @brief 変数からの値の読み出し
     */
    class Var : public Expr {
        std::size_t index;
    };
    /**
     * @brief 関数呼び出し
     */
    class Call : public Expr {
        std::shared_ptr<Func> func;
        std::vector<std::unique_ptr<Expr>> args;
    };
    /**
     * @brief 変数への代入
     */
    class Subst : public Expr {
        std::size_t index;
        std::unique_ptr<Expr> expr;
    };
}

#endif

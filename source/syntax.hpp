#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <string>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <optional>

#include "pos.hpp"
#include "variable.hpp"

#include "llvm/IR/Value.h"

#include "type.hpp"
#include "value.hpp"

// for debug print
#include <iostream>
#include <iomanip>

namespace syntax {
    class Expression {
    public:
        virtual ~Expression();
        virtual bool is_lvalue();
        virtual value::Value rvalue(const Variables &, pos::Range &) = 0;

        // FOR DEBUG
        virtual void print(int = 0) = 0;
    };

    using PairRangeExpression = std::pair<pos::Range, std::unique_ptr<Expression>>;

    // 識別子
    class Identifier : public Expression {
        std::string name;
    public:
        Identifier(std::string &&);
        bool is_lvalue() override;
        value::Value rvalue(const Variables &, pos::Range &) override;
        void print(int) override;
    };

    // 整数リテラル
    class Integer : public Expression {
        std::int32_t value;
    public:
        Integer(std::int32_t);
        value::Value rvalue(const Variables &, pos::Range &) override;
        void print(int) override;
    };

    // 浮動小数点数リテラル
    class Real : public Expression {
        double value;
    public:
        Real(double);
        value::Value rvalue(const Variables &, pos::Range &) override;
        void print(int) override;
    };

    // 文字列リテラル
    class String : public Expression {
        std::string value;
    public:
        String(std::string &&);
        value::Value rvalue(const Variables &, pos::Range &) override;
        void print(int) override;
    };

    // 単項演算子
    enum class UnaryOperator {
        Minus, Reciprocal,
        Not,
        Print
    };
    std::ostream &operator<<(std::ostream &, const UnaryOperator &); // for debug print
    class Unary : public Expression {
        UnaryOperator unary_operator;
        PairRangeExpression operand;
    public:
        Unary(UnaryOperator, PairRangeExpression);
        value::Value rvalue(const Variables &, pos::Range &) override;
        void print(int) override;
    };

    // 二項演算子
    enum class BinaryOperator {
        Add, Sub, Mul, Div, Rem,
        Less, LessEqual,
        Greater, GreaterEqual,
        Equal, NotEqual,
        BitAnd, BitOr, Xor,
        LogicalAnd, LogicalOr,
        LeftShift, RightShift,
        ForwardShift, BackwardShift
    };
    std::ostream &operator<<(std::ostream &, const BinaryOperator &); // for debug print
    int precedence(BinaryOperator);
    class Binary : public Expression {
        BinaryOperator binary_operator;
        PairRangeExpression left, right;
    public:
        Binary(BinaryOperator, PairRangeExpression, PairRangeExpression);
        value::Value rvalue(const Variables &, pos::Range &) override;
        void print(int) override;
    };

    // 括弧でくくった部分
    class Group : public Expression {
        PairRangeExpression expression;
    public:
        Group(PairRangeExpression);
        value::Value rvalue(const Variables &, pos::Range &) override;
        void print(int) override;
    };

    // 関数呼び出し
    class Invocation : public Expression {
        PairRangeExpression function;
        std::vector<PairRangeExpression> arguments;
        std::unordered_map<std::string, PairRangeExpression> named_arguments;
    public:
        Invocation(PairRangeExpression, std::vector<PairRangeExpression>, std::unordered_map<std::string, PairRangeExpression>);
        value::Value rvalue(const Variables &, pos::Range &) override;
        void print(int) override;
    };

    class Sentence {
    public:
        virtual ~Sentence();
        virtual void compile(Variables &, GlobalVariables &, pos::Range &) = 0;
        void run(GlobalVariables &, pos::Range &, int);

        // for debug print
        virtual void print(int = 0) = 0;
    };

    using PairRangeSentence = std::pair<pos::Range, std::unique_ptr<Sentence>>;

    class ExpressionSentence : public Sentence {
        PairRangeExpression expression;
    public:
        ExpressionSentence(PairRangeExpression);
        void compile(Variables &, GlobalVariables &, pos::Range &) override;
        void print(int) override;
    };

    class Substitution : public Sentence {
        PairRangeExpression left, right;
    public:
        Substitution(PairRangeExpression, PairRangeExpression);
        void compile(Variables &, GlobalVariables &, pos::Range &) override;
        void print(int) override;
    };

    class Declaration : public Sentence {
        std::string name;
        PairRangeExpression expression;
    public:
        Declaration(std::string, PairRangeExpression);
        void compile(Variables &, GlobalVariables &, pos::Range &) override;
        void print(int) override;
    };
}

#endif

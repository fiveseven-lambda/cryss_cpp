#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <string>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <optional>

#include "pos.hpp"


// for debug print
#include <iostream>
#include <iomanip>

namespace syntax {
    class Expression {
    public:
        virtual ~Expression();
        // FOR DEBUG
        virtual void print(int = 0) = 0;
        virtual std::optional<std::string> identifier();
    };

    using PairRangeExpression = std::pair<pos::Range, std::unique_ptr<Expression>>;

    // 識別子
    class Identifier : public Expression {
        std::string name;
    public:
        Identifier(std::string &&);
        void print(int) override;
        std::optional<std::string> identifier() override;
    };

    // 整数リテラル
    class Integer : public Expression {
        std::int32_t value;
    public:
        Integer(std::int32_t);
        void print(int) override;
    };

    // 浮動小数点数リテラル
    class Real : public Expression {
        double value;
    public:
        Real(double);
        void print(int) override;
    };

    // 文字列リテラル
    class String : public Expression {
        std::string value;
    public:
        String(std::string &&);
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
        void print(int) override;
    };

    // 括弧でくくった部分
    class Group : public Expression {
        PairRangeExpression expression;
    public:
        Group(PairRangeExpression);
        void print(int) override;
    };

    // 関数呼び出し
    class Invocation : public Expression {
        PairRangeExpression function;
        std::vector<PairRangeExpression> arguments;
        std::unordered_map<std::string, PairRangeExpression> named_arguments;
    public:
        Invocation(PairRangeExpression, std::vector<PairRangeExpression>, std::unordered_map<std::string, PairRangeExpression>);
        void print(int) override;
    };
}

#endif

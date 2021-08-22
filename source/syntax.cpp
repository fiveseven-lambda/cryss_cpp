#include "syntax.hpp"
#include "context.hpp"
#include "error.hpp"
#include "value.hpp"

#include "llvm/IR/Constants.h"
#include "llvm/IR/Module.h"

namespace syntax {
    Expression::~Expression() = default;

    Identifier::Identifier(std::string &&name):
        name(std::move(name)) {}
    Integer::Integer(std::int32_t value):
        value(value) {}
    Real::Real(double value):
        value(value) {}
    String::String(std::string &&value):
        value(value) {}
    Unary::Unary(UnaryOperator unary_operator, PairRangeExpression operand):
        unary_operator(unary_operator),
        operand(std::move(operand)) {}
    Binary::Binary(BinaryOperator binary_operator, PairRangeExpression left, PairRangeExpression right):
        binary_operator(binary_operator),
        left(std::move(left)),
        right(std::move(right)) {}
    Group::Group(PairRangeExpression expression):
        expression(std::move(expression)) {}
    Invocation::Invocation(PairRangeExpression function, std::vector<PairRangeExpression> arguments, std::unordered_map<std::string, PairRangeExpression> named_arguments):
        function(std::move(function)),
        arguments(std::move(arguments)),
        named_arguments(std::move(named_arguments)) {}

    int precedence(BinaryOperator op){
        switch(op){
            case BinaryOperator::ForwardShift:
            case BinaryOperator::BackwardShift: return 10;
            case BinaryOperator::Mul:
            case BinaryOperator::Div:
            case BinaryOperator::Rem: return 9;
            case BinaryOperator::Add:
            case BinaryOperator::Sub: return 8;
            case BinaryOperator::LeftShift:
            case BinaryOperator::RightShift: return 7;
            case BinaryOperator::BitAnd: return 6;
            case BinaryOperator::BitOr: return 5;
            case BinaryOperator::Xor: return 4;
            case BinaryOperator::Less:
            case BinaryOperator::LessEqual:
            case BinaryOperator::Greater:
            case BinaryOperator::GreaterEqual: return 3;
            case BinaryOperator::Equal:
            case BinaryOperator::NotEqual: return 2;
            case BinaryOperator::LogicalAnd: return 1;
            case BinaryOperator::LogicalOr: return 0;
        }
        std::terminate();
    }

    bool Expression::is_lvalue(){ return false; }
    bool Identifier::is_lvalue(){ return true; }

    Sentence::~Sentence() = default;
    ExpressionSentence::ExpressionSentence(PairRangeExpression expression):
        expression(std::move(expression)) {}
    Substitution::Substitution(PairRangeExpression left, PairRangeExpression right):
        left(std::move(left)), right(std::move(right)) {}
    Declaration::Declaration(std::string name, PairRangeExpression expression):
        name(std::move(name)), expression(std::move(expression)) {}

    value::Value Identifier::rvalue(const Variables &variables, pos::Range &range){
        auto it = variables.find(name);
        if(it == variables.end()){
            throw error::make<error::UndefinedVariable>(std::move(range));
        }
        return it->second.value();
    }
    value::Value Integer::rvalue(const Variables &, pos::Range &){
        return value::Value(llvm::ConstantInt::get(integer_type, value), std::make_unique<type::Integer>());
    }
    value::Value Real::rvalue(const Variables &, pos::Range &){
        return value::Value(llvm::ConstantFP::get(real_type, value), std::make_unique<type::Real>());
    }
    value::Value String::rvalue(const Variables &, pos::Range &){}
    value::Value Unary::rvalue(const Variables &variables, pos::Range &){
        auto operand_result = operand.second->rvalue(variables, operand.first);
        switch(unary_operator){
        case UnaryOperator::Minus:
            if(auto operand_value = operand_result.require(std::make_unique<type::Integer>())){
                return value::Value(builder.CreateNeg(operand_value), std::make_unique<type::Integer>());
            }
            break;
        }
        throw error::make<error::TypeMismatch>(std::move(operand.first));
    }
    value::Value Binary::rvalue(const Variables &, pos::Range &){}
    value::Value Group::rvalue(const Variables &, pos::Range &){}
    value::Value Invocation::rvalue(const Variables &, pos::Range &){}

    void Sentence::run(GlobalVariables &global_variables, pos::Range &range, int number){
        auto mod = std::make_unique<llvm::Module>("", *context.getContext());
        auto variables = declare(global_variables, *mod);
        std::stringstream ss;
        ss << number;
        auto function = llvm::Function::Create(function_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, ss.str(), *mod);
        auto basic_block = llvm::BasicBlock::Create(*context.getContext(), "entry", function);
        builder.SetInsertPoint(basic_block);
        compile(variables, global_variables, range);
        mod->print(llvm::errs(), nullptr);
        jit->addIRModule(llvm::orc::ThreadSafeModule(std::move(mod), context));
        auto compiled = reinterpret_cast<int (*)()>(jit->lookup(ss.str()).get().getAddress());
        std::cout << compiled() << std::endl;
    }
    void ExpressionSentence::compile(Variables &variables, GlobalVariables &global_variables, pos::Range &){
        // ちょっと今だけ関数に値を返させる　あとで消す
        builder.CreateRet(expression.second->rvalue(variables, expression.first).value);
    }
    void Substitution::compile(Variables &variables, GlobalVariables &, pos::Range &){ }
    void Declaration::compile(Variables &variables, GlobalVariables &, pos::Range &){ }

    // for debug
    constexpr int TAB = 4;
    void Identifier::print(int indent){
        std::cout << std::setw(indent) << "";
        std::cout << "Identifier(" << name << ")" << std::endl;
    }
    void Integer::print(int indent){
        std::cout << std::setw(indent) << "";
        std::cout << "Integer(" << value << ")" << std::endl;
    }
    void Real::print(int indent){
        std::cout << std::setw(indent) << "";
        std::cout << "Real(" << value << ")" << std::endl;
    }
    void String::print(int indent){
        std::cout << std::setw(indent) << "";
        std::cout << "String(" << value << ")" << std::endl;
    }
    std::ostream &operator<<(std::ostream &os, const UnaryOperator &op){
        switch(op){
            case UnaryOperator::Minus: return os << "-";
            case UnaryOperator::Reciprocal: return os << "/";
            case UnaryOperator::Not: return os << "!";
            case UnaryOperator::Print: return os << "?";
        }
        std::terminate();
    }
    void Unary::print(int indent){
        std::cout << std::setw(indent) << "";
        std::cout << "Unary" << unary_operator << std::endl;
        operand.second->print(indent + TAB);
    }
    void Group::print(int indent){
        std::cout << std::setw(indent) << "";
        std::cout << "Group" << std::endl;
        expression.second->print(indent + TAB);
    }
    std::ostream &operator<<(std::ostream &os, const BinaryOperator &op){
        switch(op){
            case BinaryOperator::Add: return os << "+";
            case BinaryOperator::Sub: return os << "-";
            case BinaryOperator::Mul: return os << "*";
            case BinaryOperator::Div: return os << "/";
            case BinaryOperator::Rem: return os << "%";
            case BinaryOperator::Less: return os << "<";
            case BinaryOperator::LessEqual: return os << "<=";
            case BinaryOperator::Greater: return os << ">";
            case BinaryOperator::GreaterEqual: return os << ">=";
            case BinaryOperator::Equal: return os << "==";
            case BinaryOperator::NotEqual: return os << "!=";
            case BinaryOperator::BitAnd: return os << "&";
            case BinaryOperator::BitOr: return os << "|";
            case BinaryOperator::Xor: return os << "^";
            case BinaryOperator::LogicalAnd: return os << "&&";
            case BinaryOperator::LogicalOr: return os << "||";
            case BinaryOperator::LeftShift: return os << "<<";
            case BinaryOperator::RightShift: return os << ">>";
            case BinaryOperator::ForwardShift: return os << ">>>";
            case BinaryOperator::BackwardShift: return os << "<<<";
        }
        std::terminate();
    }
    void Binary::print(int indent){
        left.second->print(indent + TAB);
        std::cout << std::setw(indent) << "";
        std::cout << "Binary" << binary_operator << std::endl;
        right.second->print(indent + TAB);
    }
    void Invocation::print(int indent){
        std::cout << std::setw(indent) << "";
        std::cout << "Invocation" << std::endl;
        function.second->print(indent + TAB);
        for(std::size_t i = 0; i < arguments.size(); ++i){
            std::cout << std::setw(indent) << "";
            std::cout << "(" << i << ")" << std::endl;
            arguments[i].second->print(indent + TAB);
        }
        for(auto &[name, argument] : named_arguments){
            std::cout << std::setw(indent) << "";
            std::cout << "(" << name << ")" << std::endl;
            argument.second->print(indent + TAB);
        }
    }
    void ExpressionSentence::print(int indent){
        std::cout << std::setw(indent) << "";
        std::cout << "ExpressionSentence" << std::endl;
        if(expression.second) expression.second->print(indent + TAB);
    }
    void Substitution::print(int indent){
        std::cout << std::setw(indent) << "";
        std::cout << "Substitution" << std::endl;
        if(left.second) left.second->print(indent + TAB);
        if(right.second) right.second->print(indent + TAB);
    }
    void Declaration::print(int indent){
        std::cout << std::setw(indent) << "";
        std::cout << "Declaration: " << name << std::endl;
        if(expression.second) expression.second->print(indent + TAB);
    }

}

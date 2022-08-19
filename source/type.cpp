/**
 * @file type.cpp
 */
#include "type.hpp"

#include <boost/functional/hash.hpp>

/// @todo デバッグ出力用
#include <iostream>

namespace type {
    Type::~Type() = default;
    Primitive::Primitive(PrimitiveKind kind): kind(kind) {}
    Tuple::Tuple(const std::vector<std::reference_wrapper<const Type>> &elements_type): elements_type(elements_type) {}
    Function::Function(const Tuple &arguments_type, const Type &return_type) : arguments_type(arguments_type), return_type(return_type) {}

    PrimitiveKind Primitive::get_kind() const { return kind; }
    const std::vector<std::reference_wrapper<const Type>> &Tuple::get_elements_type() const { return elements_type; }
    const std::vector<std::reference_wrapper<const Type>> &Function::get_arguments_type() const { return arguments_type.get_elements_type(); }
    const Type &Function::get_return_type() const { return return_type; }
    std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> Function::into_pair() const { return {arguments_type.get_elements_type(), return_type}; }

    std::size_t PrimitiveHash::operator()(const PrimitiveKind &kind) const noexcept { return std::hash<PrimitiveKind>()(kind); }
    std::size_t PrimitiveHash::operator()(const std::unique_ptr<Primitive> &type) const noexcept { return (*this)(type->get_kind()); }
    bool PrimitiveEq::operator()(const PrimitiveKind &left, const PrimitiveKind &right) const noexcept { return left == right; }
    bool PrimitiveEq::operator()(const PrimitiveKind &left, const std::unique_ptr<Primitive> &right) const noexcept { return left == right->get_kind(); }
    bool PrimitiveEq::operator()(const std::unique_ptr<Primitive> &left, const std::unique_ptr<Primitive> &right) const noexcept { return left->get_kind() == right->get_kind(); }

    std::size_t TupleHash::operator()(const std::vector<std::reference_wrapper<const Type>> &elements_type) const noexcept {
        std::size_t seed = 0;
        // 注意：Type * 型のアドレス値を使う
        for(const Type &element_type : elements_type) boost::hash_combine<const Type *>(seed, &element_type);
        return seed;
    }
    std::size_t TupleHash::operator()(const std::unique_ptr<Tuple> &type) const noexcept { return (*this)(type->get_elements_type()); }
    bool TupleEq::operator()(const std::vector<std::reference_wrapper<const Type>> &left, const std::vector<std::reference_wrapper<const Type>> &right) const noexcept {
        if(left.size() != right.size()) return false;
        for(std::size_t i = 0; i < left.size(); i++) if(&left[i].get() != &right[i].get()) return false;
        return true;
    }
    bool TupleEq::operator()(const std::vector<std::reference_wrapper<const Type>> &left, const std::unique_ptr<Tuple> &right) const noexcept { return (*this)(left, right->get_elements_type()); }
    bool TupleEq::operator()(const std::unique_ptr<Tuple> &left, const std::unique_ptr<Tuple> &right) const noexcept { return (*this)(left->get_elements_type(), right->get_elements_type()); }

    std::size_t FunctionHash::operator()(const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> & pair) const noexcept {
        std::size_t seed = TupleHash()(pair.first);
        boost::hash_combine<const Type *>(seed, &pair.second);
        return seed;
    }
    std::size_t FunctionHash::operator()(const std::unique_ptr<Function> &type) const noexcept {
        return (*this)(type->into_pair());
    }
    bool FunctionEq::operator()(const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> &left, const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> &right) const noexcept {
        return TupleEq()(left.first, right.first) && (&left.second == &right.second);
    }
    bool FunctionEq::operator()(const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> &left, const std::unique_ptr<Function> &right) const noexcept { return (*this)(left, right->into_pair()); }
    bool FunctionEq::operator()(const std::unique_ptr<Function> &left, const std::unique_ptr<Function> &right) const noexcept { return (*this)(left->into_pair(), right->into_pair()); }

    const Primitive &TypeContext::primitive(PrimitiveKind kind){
        auto it = primitives.find(kind);
        if(it == primitives.end()) it = primitives.insert(std::make_unique<Primitive>(kind)).first;
        return **it;
    }
    const Tuple &TypeContext::tuple(const std::vector<std::reference_wrapper<const Type>> &elements_type){
        auto it = tuples.find(elements_type);
        if(it == tuples.end()) it = tuples.insert(std::make_unique<Tuple>(elements_type)).first;
        return **it;
    }
    const Function &TypeContext::function(const std::vector<std::reference_wrapper<const Type>> &arguments_type, const Type &return_type){
        auto it = functions.find(std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &>(arguments_type, return_type));
        if(it == functions.end()) it = functions.insert(std::make_unique<Function>(tuple(arguments_type), return_type)).first;
        return **it;
    }

    /// @todo デバッグ出力用
    static void indent(int depth){
        for(int i = 0; i < depth; i++) std::cout << "    ";
    }
    void Primitive::debug_print(int depth) const {
        indent(depth);
        std::string_view name;
        switch(kind){
            case PrimitiveKind::Boolean: name = "boolean"; break;
            case PrimitiveKind::Integer: name = "integer"; break;
            case PrimitiveKind::Rational: name = "rational"; break;
            case PrimitiveKind::Float: name = "float";
        }
        std::cout << name << std::endl;
    }
    void Tuple::debug_print(int depth) const {
        indent(depth);
        std::cout << "tuple(" << elements_type.size() << ")" << std::endl;
        for(const Type &element_type : elements_type){
            element_type.debug_print(depth + 1);
        }
    }
    void Function::debug_print(int depth) const {
        indent(depth);
        std::cout << "function(" << arguments_type.get_elements_type().size() << ") (" << std::endl;
        for(const Type &argument_type: arguments_type.get_elements_type()){
            argument_type.debug_print(depth + 1);
        }
        indent(depth);
        std::cout << ") ->" << std::endl;
        return_type.debug_print(depth + 1);
    }
    void TypeContext::debug_print(int depth) const {
        for(auto &type : primitives) type->debug_print(depth);
        for(auto &type : tuples) type->debug_print(depth);
        for(auto &type : functions) type->debug_print(depth);
    }
}

/**
 * @file type.cpp
 */
#include "type.hpp"

#include <boost/functional/hash.hpp>

/// @todo デバッグ出力用
#include <iostream>

namespace type {
    Type::~Type() = default;
    PrimitiveType::PrimitiveType(PrimitiveTypeKind kind): kind(kind) {}
    Tuple::Tuple(const std::vector<std::reference_wrapper<Type>> &elements_type): elements_type(elements_type) {}

    PrimitiveTypeKind PrimitiveType::get_kind() const { return kind; }
    const std::vector<std::reference_wrapper<Type>> &Tuple::get_elements_type() const { return elements_type; }

    std::size_t PrimitiveTypeHash::operator()(const PrimitiveTypeKind &kind) const noexcept { return std::hash<PrimitiveTypeKind>()(kind); }
    std::size_t PrimitiveTypeHash::operator()(const std::unique_ptr<PrimitiveType> &type) const noexcept { return (*this)(type->get_kind()); }
    bool PrimitiveTypePred::operator()(const PrimitiveTypeKind &left, const PrimitiveTypeKind &right) const noexcept { return left == right; }
    bool PrimitiveTypePred::operator()(const PrimitiveTypeKind &left, const std::unique_ptr<PrimitiveType> &right) const noexcept { return left == right->get_kind(); }

    std::size_t TupleHash::operator()(const std::vector<std::reference_wrapper<Type>> &elements_type) const noexcept {
        std::size_t seed = 0;
        // 注意：Type * 型のアドレス値を使う
        for(Type &element_type : elements_type) boost::hash_combine<Type *>(seed, &element_type);
        return seed;
    }
    std::size_t TupleHash::operator()(const std::unique_ptr<Tuple> &type) const noexcept { return (*this)(type->get_elements_type()); }

    const PrimitiveType &TypeContext::primitive_type(PrimitiveTypeKind kind){
        auto it = primitive_types.find<PrimitiveTypeKind>(kind);
    }

    /// @todo デバッグ出力用
    static void indent(int depth){
        for(int i = 0; i < depth; i++) std::cout << "    ";
    }
    void PrimitiveType::debug_print(int depth) const {
        indent(depth);
        std::string_view name;
        switch(kind){
            case PrimitiveTypeKind::Boolean: name = "boolean"; break;
            case PrimitiveTypeKind::Integer: name = "integer"; break;
            case PrimitiveTypeKind::Rational: name = "rational"; break;
            case PrimitiveTypeKind::Float: name = "float";
        }
        std::cout << name << std::endl;
    }
    void Tuple::debug_print(int depth) const {
        indent(depth);
        std::cout << "tuple" << std::endl;
        for(Type &element_type : elements_type){
            element_type.debug_print(depth);
        }
    }
}

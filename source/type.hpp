/**
 * @file type.hpp
 */
#ifndef TYPE_HPP
#define TYPE_HPP

#include <vector>
#include <memory>
#include <functional>
#include <unordered_set>

/**
 * @brief 型を定義する．
 */
namespace type {
    /**
     * @brief 全ての型の基底クラス
     */
    class Type {
    public:
        virtual ~Type();
        /// @todo debug用出力の削除
        virtual void debug_print(int) const = 0;
    };

    /**
     * @brief プリミティブ型の種類を表す
     */
    enum class PrimitiveTypeKind {
        Boolean,
        Integer,
        Rational,
        Float,
    };

    /**
     * @brief プリミティブ型
     */
    class PrimitiveType : public Type {
        PrimitiveTypeKind kind;
    public:
        PrimitiveType(PrimitiveTypeKind);
        PrimitiveTypeKind get_kind() const;
        virtual void debug_print(int) const override;
    };

    /**
     * @brief タプル
     */
    class Tuple : public Type {
        const std::vector<std::reference_wrapper<Type>> elements_type;
    public:
        Tuple(const std::vector<std::reference_wrapper<Type>> &);
        const std::vector<std::reference_wrapper<Type>> &get_elements_type() const;
        virtual void debug_print(int) const override;
    };

    struct PrimitiveTypeHash {
        using is_transparent = void;
        std::size_t operator()(const PrimitiveTypeKind &) const noexcept;
        std::size_t operator()(const std::unique_ptr<PrimitiveType> &) const noexcept;
    };
    struct PrimitiveTypePred {
        using is_transparent = void;
        bool operator()(const PrimitiveTypeKind &, const PrimitiveTypeKind &) const noexcept;
        bool operator()(const PrimitiveTypeKind &, const std::unique_ptr<PrimitiveType> &) const noexcept;
    };
    struct TupleHash {
        using is_transparent = void;
        std::size_t operator()(const std::vector<std::reference_wrapper<Type>> &) const noexcept;
        std::size_t operator()(const std::unique_ptr<Tuple> &) const noexcept;
    };
    struct TuplePred {
        using is_transparent = void;
        bool operator()(const std::vector<std::reference_wrapper<Type>> &, const std::vector<std::reference_wrapper<Type>> &) const noexcept;
        bool operator()(const std::vector<std::reference_wrapper<Type>> &, const std::unique_ptr<Tuple> &) const noexcept;
    };

    /**
     * @brief 型を管理する．
     */
    class TypeContext {
        std::unordered_set<std::unique_ptr<PrimitiveType>, PrimitiveTypeHash, PrimitiveTypeKind> primitive_types;
        std::unordered_set<std::unique_ptr<Tuple>, TupleHash, TuplePred> tuples;
    public:
        const PrimitiveType &primitive_type(PrimitiveTypeKind kind);
        const Tuple &tuple();
    };
}

#endif

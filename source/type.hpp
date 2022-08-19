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
        const std::vector<std::reference_wrapper<const Type>> elements_type;
    public:
        Tuple(const std::vector<std::reference_wrapper<const Type>> &);
        const std::vector<std::reference_wrapper<const Type>> &get_elements_type() const;
        virtual void debug_print(int) const override;
    };

    struct PrimitiveTypeHash {
        using is_transparent = void;
        std::size_t operator()(const PrimitiveTypeKind &) const noexcept;
        std::size_t operator()(const std::unique_ptr<PrimitiveType> &) const noexcept;
    };
    struct PrimitiveTypeEq {
        using is_transparent = void;
        bool operator()(const PrimitiveTypeKind &, const PrimitiveTypeKind &) const noexcept;
        bool operator()(const PrimitiveTypeKind &, const std::unique_ptr<PrimitiveType> &) const noexcept;
        bool operator()(const std::unique_ptr<PrimitiveType> &, const std::unique_ptr<PrimitiveType> &) const noexcept;
    };
    struct TupleHash {
        using is_transparent = void;
        std::size_t operator()(const std::vector<std::reference_wrapper<const Type>> &) const noexcept;
        std::size_t operator()(const std::unique_ptr<Tuple> &) const noexcept;
    };
    struct TupleEq {
        using is_transparent = void;
        bool operator()(const std::vector<std::reference_wrapper<const Type>> &, const std::vector<std::reference_wrapper<const Type>> &) const noexcept;
        bool operator()(const std::vector<std::reference_wrapper<const Type>> &, const std::unique_ptr<Tuple> &) const noexcept;
        bool operator()(const std::unique_ptr<Tuple> &, const std::unique_ptr<Tuple> &) const noexcept;
    };

    /**
     * @brief 型を管理する．
     */
    class TypeContext {
        std::unordered_set<std::unique_ptr<PrimitiveType>, PrimitiveTypeHash, PrimitiveTypeEq> primitive_types;
        std::unordered_set<std::unique_ptr<Tuple>, TupleHash, TupleEq> tuples;
    public:
        const PrimitiveType &primitive_type(PrimitiveTypeKind);
        const Tuple &tuple(const std::vector<std::reference_wrapper<const Type>> &);
        /**
         * @todo デバッグ出力
         */
        void debug_print(int) const;
    };
}

#endif

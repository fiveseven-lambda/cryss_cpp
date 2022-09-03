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
#ifdef DEBUG
        virtual void debug_print(int) const = 0;
#endif
    };

    /**
     * @brief プリミティブ型の種類を表す
     */
    enum class PrimitiveKind {
        Boolean,
        Integer,
        Rational,
        Float,
    };

    /**
     * @brief プリミティブ型
     */
    class Primitive : public Type {
        PrimitiveKind kind;
    public:
        Primitive(PrimitiveKind);
        PrimitiveKind get_kind() const;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };

    /**
     * @brief タプル
     */
    class Tuple : public Type {
        const std::vector<std::reference_wrapper<const Type>> elements_type;
    public:
        Tuple(const std::vector<std::reference_wrapper<const Type>> &);
        const std::vector<std::reference_wrapper<const Type>> &get_elements_type() const;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };

    /**
     * @brief 関数型
     */
    class Function : public Type {
        const Tuple &arguments_type;
        const Type &return_type;
    public:
        Function(const Tuple &, const Type &);
        const std::vector<std::reference_wrapper<const Type>> &get_arguments_type() const;
        const Type &get_return_type() const;
        std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> into_pair() const;
#ifdef DEBUG
        virtual void debug_print(int) const override;
#endif
    };

    /**
     * @brief `std::unordered_set<std::unique_ptr<Primitive>>`に用いるハッシュ関数オブジェクト
     */
    struct PrimitiveHash {
        using is_transparent = void;
        std::size_t operator()(const PrimitiveKind &) const noexcept;
        std::size_t operator()(const std::unique_ptr<Primitive> &) const noexcept;
    };
    /**
     * @brief `std::unordered_set<std::unique_ptr<Primitive>>`に用いる比較関数オブジェクト
     */
    struct PrimitiveEq {
        using is_transparent = void;
        bool operator()(const PrimitiveKind &, const PrimitiveKind &) const noexcept;
        bool operator()(const PrimitiveKind &, const std::unique_ptr<Primitive> &) const noexcept;
        bool operator()(const std::unique_ptr<Primitive> &, const std::unique_ptr<Primitive> &) const noexcept;
    };
    /**
     * @brief `std::unordered_set<std::unique_ptr<Tuple>>`に用いるハッシュ関数オブジェクト
     */
    struct TupleHash {
        using is_transparent = void;
        std::size_t operator()(const std::vector<std::reference_wrapper<const Type>> &) const noexcept;
        std::size_t operator()(const std::unique_ptr<Tuple> &) const noexcept;
    };
    /**
     * @brief `std::unordered_set<std::unique_ptr<Tuple>>`に用いる比較関数オブジェクト
     */
    struct TupleEq {
        using is_transparent = void;
        bool operator()(const std::vector<std::reference_wrapper<const Type>> &, const std::vector<std::reference_wrapper<const Type>> &) const noexcept;
        bool operator()(const std::vector<std::reference_wrapper<const Type>> &, const std::unique_ptr<Tuple> &) const noexcept;
        bool operator()(const std::unique_ptr<Tuple> &, const std::unique_ptr<Tuple> &) const noexcept;
    };
    /**
     * @brief `std::unordered_set<std::unique_ptr<Function>>`に用いるハッシュ関数オブジェクト
     */
    struct FunctionHash {
        using is_transparent = void;
        std::size_t operator()(const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> &) const noexcept;
        std::size_t operator()(const std::unique_ptr<Function> &) const noexcept;
    };
    /**
     * @brief `std::unordered_set<std::unique_ptr<Function>>`に用いる比較関数オブジェクト
     */
    struct FunctionEq {
        using is_transparent = void;
        bool operator()(const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> &, const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> &) const noexcept;
        bool operator()(const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> &, const std::unique_ptr<Function> &) const noexcept;
        bool operator()(const std::unique_ptr<Function> &, const std::unique_ptr<Function> &) const noexcept;
    };

    /**
     * @brief 型を管理する．
     *
     * `std::unique_ptr` で型を持つ．同じ型を表すオブジェクトが複数作られることはないため，アドレスで比較できる．
     */
    class TypeContext {
        std::unordered_set<std::unique_ptr<Primitive>, PrimitiveHash, PrimitiveEq> primitives;
        std::unordered_set<std::unique_ptr<Tuple>, TupleHash, TupleEq> tuples;
        std::unordered_set<std::unique_ptr<Function>, FunctionHash, FunctionEq> functions;
    public:
        /**
         * @brief プリミティブ型を得る．
         */
        const Primitive &primitive(PrimitiveKind);
        /**
         * @brief タプルを得る．
         */
        const Tuple &tuple(const std::vector<std::reference_wrapper<const Type>> &);
        /**
         * @brief 関数型を得る．
         */
        const Function &function(const std::vector<std::reference_wrapper<const Type>> &, const Type &);
#ifdef DEBUG
        void debug_print(int) const;
#endif
    };
}

#endif

/**
 * @file type.hpp
 * @brief 型を定義する．
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
     * @brief bool 型
     */
    class Bool : public Type {
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };

    /**
     * @brief int 型
     */
    class Int : public Type {
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };

    /**
     * @brief rational 型
     */
    class Rational : public Type {
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };

    /**
     * @brief float 型
     */
    class Float : public Type {
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };

    /**
     * @brief str 型
     */
    class Str : public Type {
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };

    /**
     * @brief 関数型
     */
    class Func : public Type {
        std::vector<std::reference_wrapper<const Type>> args;
        const Type &ret;
    public:
        Func(const std::vector<std::reference_wrapper<const Type>> &, const Type &);
        const std::vector<std::reference_wrapper<const Type>> &get_args() const;
        const Type &get_ret() const;
        std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> get_pair() const;
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };

    /**
     * @brief `std::unique_ptr<Func>` をもつ `std::unordered_set`に用いるハッシュ関数オブジェクト
     */
    struct FuncHash {
        using is_transparent = void;
        std::size_t operator()(const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> &) const noexcept;
        std::size_t operator()(const std::unique_ptr<Func> &) const noexcept;
    };
    /**
     * @brief `std::unique_ptr<Func>` をもつ `std::unordered_set`に用いる比較関数オブジェクト
     */
    struct FuncEq {
        using is_transparent = void;
        bool operator()(const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> &, const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> &) const noexcept;
        bool operator()(const std::pair<const std::vector<std::reference_wrapper<const Type>> &, const Type &> &, const std::unique_ptr<Func> &) const noexcept;
        bool operator()(const std::unique_ptr<Func> &, const std::unique_ptr<Func> &) const noexcept;
    };

    /**
     * @brief Sound 型
     */
    class Sound : public Type {
        const Type &result;
    public:
        Sound(const Type &);
        const Type &get_result() const;
#ifdef DEBUG
        void debug_print(int) const override;
#endif
    };

    /**
     * @brief `std::unique_ptr<Sound>` をもつ `std::unordered_set`に用いるハッシュ関数オブジェクト
     */
    struct SoundHash {
        using is_transparent = void;
        std::size_t operator()(const Type &) const noexcept;
        std::size_t operator()(const std::unique_ptr<Sound> &) const noexcept;
    };
    /**
     * @brief `std::unique_ptr<Sound>` をもつ `std::unordered_set`に用いる比較関数オブジェクト
     */
    struct SoundEq {
        using is_transparent = void;
        bool operator()(const Type &, const Type &) const noexcept;
        bool operator()(const Type &, const std::unique_ptr<Sound> &) const noexcept;
        bool operator()(const std::unique_ptr<Sound> &, const std::unique_ptr<Sound> &) const noexcept;
    };

    /**
     * @brief 型を管理する．
     *
     * 同じ型を表すオブジェクトを複数作ることはないため，アドレスで比較できる．
     */
    class TypeContext {
        Bool bool_ty;
        Int int_ty;
        Rational rational_ty;
        Float float_ty;
        Str str_ty;
        std::unordered_set<std::unique_ptr<Func>, FuncHash, FuncEq> funcs;
        std::unordered_set<std::unique_ptr<Sound>, SoundHash, SoundEq> sounds;
    public:
        /**
         * @brief bool 型を得る．
         */
        const Bool &get_bool() &;
        /**
         * @brief int 型を得る．
         */
        const Int &get_int() &;
        /**
         * @brief rational 型を得る．
         */
        const Rational &get_rational() &;
        /**
         * @brief float 型を得る．
         */
        const Float &get_float() &;
        /**
         * @brief str 型を得る．
         */
        const Str &get_str() &;
        /**
         * @brief 関数型を得る．
         */
        const Func &get_func(const std::vector<std::reference_wrapper<const Type>> &, const Type &) &;
        /**
         * @brief 音を得る．
         */
        const Sound &get_sound(const Type &);
#ifdef DEBUG
        void debug_print(int) const;
#endif
    };
}

#endif

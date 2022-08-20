/**
 * @file token.hpp
 * @brief トークンを定義する
 */
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "pos.hpp"
#include <string_view>

/**
 * @brief トークンを定義する．
 */
namespace token {
    /**
     * @brief 全てのトークンの基底クラス
     */
    class Token {
    public:
        //! ソースコード中の位置
        pos::Range pos;
        virtual ~Token();
    };
    /**
     * @brief 識別子 `[a-zA-Z_$][a-zA-Z0-9_$]*`
     */
    class Identifier : public Token {
        std::string_view name;
    public:
        Identifier(std::string_view);
    };
    /**
     * @brief 整数リテラル `[0-9]+`
     */
    class Integer : public Token {
        std::string_view value;
    public:
        Integer(std::string_view);
    };
    //! 加算 `+`
    class Plus : public Token {
    };
}

#endif

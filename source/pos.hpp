/**
 * @file pos.hpp
 * @brief エラー出力のための位置情報をもつクラスを定義する．
 */
#ifndef POS_HPP
#define POS_HPP

#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

/**
 * @brief エラー出力のための位置情報をもつクラスを定義する．
 */
namespace pos {
    /**
     * @brief ソースコード上の文字の位置
     */
    class Pos {
        std::size_t line;
        std::size_t byte;
    public:
        Pos();
        Pos(std::size_t, std::size_t);
        std::pair<std::size_t, std::size_t> into_pair() const;
        friend std::ostream &operator<<(std::ostream &, const Pos &);
        void eprint(const std::vector<std::string> &) const;
    };

    /**
     * @brief ソースコード上の式や文の範囲
     */
    class Range {
        Pos start;
        Pos end;
    public:
        Range();
        Range(std::size_t, std::size_t, std::size_t);
        Range(Pos, Pos);
        Range(const Range &) = delete;
        Range &operator=(const Range &) = delete;
        Range(Range &&);
        Range &operator=(Range &&);
        Range &operator+=(const Range &);
        friend Range operator+(const Range &, const Range &);
        Range clone();
        friend std::ostream &operator<<(std::ostream &, const Range &);
        void eprint(const std::vector<std::string> &) const;
    };
}

#endif

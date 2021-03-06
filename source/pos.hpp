#ifndef POS_HPP
#define POS_HPP
#include <iostream>
#include <cstddef>
#include <string>

namespace pos {
    class Pos {
        std::size_t line, byte;
    public:
        Pos();
        Pos(std::size_t, std::size_t);
        std::size_t get_line() const, get_byte() const;
        void display(const std::string &, std::ostream & = std::cerr);
    };
    std::ostream &operator<<(std::ostream &os, const Pos &);

    class Range {
        Pos start, end;
        Range(const Range &) = delete;
        Range &operator=(const Range &) = delete;
    public:
        Range();
        Range(Pos, Pos);
        Range(Range &&);
        Range &operator=(Range &&);
        Range &&clone() const;
        Pos get_start() const, get_end() const;
        Range &operator+=(const Range &), &operator-=(const Range &);
        std::string substr(const std::string &);
        void display(const std::string &, std::ostream & = std::cerr);
    };
    Range add_range(const Range &, const Range &);
    std::ostream &operator<<(std::ostream &os, const Range &);
    Range operator+(Range, const Range &), operator-(Range, const Range &);
}

#endif

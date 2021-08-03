#ifndef POS_H
#define POS_H
#include <cstddef>
#include <string>

namespace pos {
    class Pos {
        std::size_t line, byte;
    public:
        Pos(std::size_t, std::size_t);
        std::size_t get_line() const, get_byte() const;
    };
    std::ostream &operator<<(std::ostream &os, const Pos &);

    class Range {
        Pos start, end;
    public:
        Range(Pos, Pos);
        Pos get_start() const, get_end() const;
        Range &operator+=(const Range &);
        std::string substr(const std::string &);
    };
    std::ostream &operator<<(std::ostream &os, const Range &);
    Range operator+(Range, const Range &);
}

#endif

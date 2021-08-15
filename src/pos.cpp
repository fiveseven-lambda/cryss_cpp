#include <iostream>
#include "pos.hpp"

namespace pos {
    Pos::Pos() = default;
    Pos::Pos(std::size_t line, std::size_t byte): line(line), byte(byte) {}
    std::size_t Pos::get_line() const { return line; }
    std::size_t Pos::get_byte() const { return byte; }
    std::ostream &operator<<(std::ostream &os, const Pos &pos){
        return os << "line " << pos.get_line() + 1;
    }
    void Pos::display(const std::string &log, std::ostream &os){
        // pos を含む行全体を出力したい
    }
    Range::Range() = default;
    Range::Range(Pos start, Pos end): start(start), end(end) {}
    Range::Range(Range &&) = default;
    Range &Range::operator=(Range &&) = default;
    Range &Range::operator+=(const Range &other) {
        end = other.end;
        return *this;
    }
    Range &Range::operator-=(const Range &other) {
        start = other.start;
        return *this;
    }
    Pos Range::get_start() const { return start; }
    Pos Range::get_end() const { return end; }
    std::ostream &operator<<(std::ostream &os, const Range &range){
        return os << "line " << range.get_start().get_line() + 1 << "-" << range.get_end().get_line() + 1;
    }
    Range operator+(Range left, const Range &right) {
        return std::move(left += right);
    }
    Range operator-(Range left, const Range &right) {
        return std::move(left -= right);
    }
    Range add_range(const Range &left, const Range &right){
        return Range(left.get_start(), right.get_end());
    }
    std::string Range::substr(const std::string &log){
        return log.substr(start.get_byte(), end.get_byte() - start.get_byte());
    }
    void Range::display(const std::string &log, std::ostream &os){
        // range を含む行全体を出力したい
    }
}

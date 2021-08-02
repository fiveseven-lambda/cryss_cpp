#include "pos.h"

namespace pos {
    Pos::Pos(std::size_t line, std::size_t byte): line(line), byte(byte) {}
    std::size_t Pos::get_byte() {
        return byte;
    }
    Range::Range(Pos start, Pos end): start(start), end(end) {}
    Range &Range::operator+=(const Range &other) {
        end = other.end;
        return *this;
    }
    Range operator+(Range left, const Range &right) {
        return left += right;
    }
}

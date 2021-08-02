#include <cstddef>

namespace pos {
    class Pos {
        std::size_t line, byte;
    public:
        Pos(std::size_t, std::size_t);
        std::size_t get_byte();
    };
    class Range {
        Pos start, end;
    public:
        Range(Pos, Pos);
        Range &operator+=(const Range &);
    };
    Range operator+(Range, const Range &);
}
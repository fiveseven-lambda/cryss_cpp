/**
 * @file pos.hpp
 */
#ifndef POS_HPP
#define POS_HPP

#include <cstddef>
#include <optional>

namespace pos {
    class Start {
        std::size_t line, byte;
    public:
        Start(std::size_t, std::size_t);
    };
    class End {
        std::size_t line;
        std::optional<std::size_t> byte;
    public:
        End(std::size_t, std::optional<std::size_t>);
    };
    class Range {
        Start start;
        End end;
    public:
        Range(Start, End);
        Range(std::size_t, std::size_t, std::optional<std::size_t>);
    };
}

#endif

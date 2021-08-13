#include <iostream>
#include "pos.hpp"

namespace pos {
    Pos::Pos(std::size_t line, std::size_t byte): line(line), byte(byte) {}
    std::size_t Pos::get_line() const {
        return line;
    }
    std::size_t Pos::get_byte() const {
        return byte;
    }
    std::ostream &operator<<(std::ostream &os, const Pos &pos){
        return os << "line " << pos.get_line() + 1;
    }
    void Pos::display(const std::string &log, std::ostream &os){
        auto left = log.rfind('\n', byte) + 1;
        auto right = log.find('\n', byte) + 1;
        os
            << log.substr(left, byte - left)
            << " !-> "
            << log.substr(byte, right - byte);
    }
    Range::Range(Pos start, Pos end): start(start), end(end) {}
    Range::Range(Range &&) = default;
    Range &Range::operator=(Range &&) = default;
    Range &Range::operator+=(const Range &other) {
        end = other.end;
        return *this;
    }
    Pos Range::get_start() const {
        return start;
    }
    Pos Range::get_end() const {
        return end;
    }
    std::ostream &operator<<(std::ostream &os, const Range &range){
        return os << "line " << range.get_start().get_line() + 1 << "-" << range.get_end().get_line() + 1
            << " byte " << range.get_start().get_byte() << "-" << range.get_end().get_byte()
        ;
    }
    Range operator+(Range left, const Range &right) {
        return std::move(left += right);
    }
    std::string Range::substr(const std::string &log){
        return log.substr(start.get_byte(), end.get_byte() - start.get_byte());
    }
    void Range::display(const std::string &log, std::ostream &os){
        auto start_byte = start.get_byte();
        auto end_byte = start.get_byte();
        auto left = log.rfind('\n', start_byte) + 1;
        auto right = log.find('\n', end_byte) + 1;
        os
            << log.substr(left, start_byte - left)
            << " !-> "
            << log.substr(start_byte, end_byte - start_byte)
            << " <-! "
            << log.substr(end_byte, right - end_byte);
    }
}

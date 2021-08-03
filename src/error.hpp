#ifndef ERROR_H
#define ERROR_H

#include <string>
#include "pos.hpp"

namespace error {
    class Error {
    public:
        void virtual print(const std::string &) = 0;
        virtual ~Error() = default;
    };
    class InvalidCharacter: public Error {
        pos::Pos pos;
    public:
        InvalidCharacter(pos::Pos &&);
        void print(const std::string &) override;
        virtual ~InvalidCharacter() override = default;
    };
    class UnexpectedCharacter: public Error {
        pos::Range range;
    public:
        UnexpectedCharacter(pos::Range &&);
        void print(const std::string &) override;
        virtual ~UnexpectedCharacter() override = default;
    };
}
#endif

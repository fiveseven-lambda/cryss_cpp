#ifndef ERROR_H
#define ERROR_H

#include <string>
#include "pos.h"

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
        void print(const std::string &);
        virtual ~InvalidCharacter() = default;
    };
    class UnexpectedCharacter: public Error {
        pos::Range range;
    public:
        UnexpectedCharacter(pos::Range &&);
        void print(const std::string &);
        virtual ~UnexpectedCharacter() = default;
    };
}
#endif
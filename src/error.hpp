#ifndef ERROR_H
#define ERROR_H

#include <string>
#include "pos.hpp"

namespace error {
    class Error {
    public:
        void virtual print(const std::string &) = 0;
        virtual ~Error();
    };
    class UnexpectedCharacter: public Error {
        pos::Range range;
    public:
        UnexpectedCharacter(pos::Range &&);
        void print(const std::string &) override;
        ~UnexpectedCharacter() override;
    };
}
#endif

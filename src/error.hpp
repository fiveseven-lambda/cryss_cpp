#ifndef ERROR_HPP
#define ERROR_HPP

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
    class UnexpectedToken: public Error {
        pos::Range range;
    public:
        UnexpectedToken(pos::Range &&);
        void print(const std::string &) override;
        ~UnexpectedToken() override;
    };
}
#endif

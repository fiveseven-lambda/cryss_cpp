#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <memory>
#include "pos.hpp"

namespace error {
    class Error {
    public:
        void virtual print(const std::string &) = 0;
        virtual ~Error();
    };

    template<class Err, class... Args>
    std::unique_ptr<Error> make(Args&&... args){
        return std::make_unique<Err>(std::forward<Args>(args)...);
    }

    class UnexpectedCharacter : public Error {
        pos::Range range;
    public:
        UnexpectedCharacter(pos::Range &&);
        void print(const std::string &) override;
    };
    class UnterminatedComment : public Error {
        pos::Pos pos;
    public:
        UnterminatedComment(pos::Pos &&);
        void print(const std::string &) override;
    };
    class UnterminatedStringLiteral : public Error {
        pos::Pos pos;
    public:
        UnterminatedStringLiteral(pos::Pos &&);
        void print(const std::string &) override;
    };
    class IncompleteScientificNotation : public Error {
        pos::Range range;
    public:
        IncompleteScientificNotation(pos::Range &&);
        void print(const std::string &) override;
    };
    class UnexpectedToken : public Error {
        pos::Range range;
    public:
        UnexpectedToken(pos::Range &&);
        void print(const std::string &) override;
    };
    class UndefinedVariable : public Error {
        pos::Range range;
    public:
        UndefinedVariable(pos::Range &&);
        void print(const std::string &) override;
    };
    class TypeMismatch : public Error {
        pos::Range range;
    public:
        TypeMismatch(pos::Range &&);
        void print(const std::string &) override;
    };
}
#endif

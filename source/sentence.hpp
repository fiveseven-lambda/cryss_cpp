/**
 * @file sentence.hpp
 */
#ifndef SENTENCE_HPP
#define SENTENCE_HPP

#include "pos.hpp"

namespace sentence {
    class Sentence {
    public:
        pos::Range pos;
        virtual ~Sentence();
        virtual void compile_global(
        );
        virtual void compile_local(
        );
    };
}

#endif

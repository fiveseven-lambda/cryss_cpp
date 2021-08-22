#include "context.hpp"
#include "environment.hpp"

namespace environment {
    Environment::Environment():
        number(0) {}
    void Environment::run(syntax::PairRangeSentence sentence){
        sentence.second->print();
        sentence.second->run(global_variables, sentence.first, number);
        ++number;
    }
}

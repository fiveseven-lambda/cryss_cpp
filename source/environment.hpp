#include <unordered_map>

#include "syntax.hpp"
#include "llvm/IR/Value.h"

namespace environment {
    class Environment {
        GlobalVariables global_variables;
        int number;
    public:
        Environment();
        void run(syntax::PairRangeSentence);
    };
}

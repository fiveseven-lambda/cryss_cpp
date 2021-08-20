#include <unordered_map>

#include "syntax.hpp"
#include "llvm/IR/Value.h"

namespace environment {
    class Environment {
    public:
        Environment();
        bool run(syntax::PairRangeSentence);
    };
}
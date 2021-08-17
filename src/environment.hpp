#include <unordered_map>

#include "syntax.hpp"
#include "llvm/IR/Value.h"

namespace environment {
    class Environment {
        std::unordered_map<std::string, llvm::Value *> variables;
    public:
        Environment();
        bool run(syntax::PairRangeSentence);
    };
}
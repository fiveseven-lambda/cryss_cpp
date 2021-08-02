#include <vector>
#include <string>
#include <utility>
#include <optional>
#include <queue>
#include "error.h"
#include "token.h"

namespace lexer {
    class Inner {
        std::vector<pos::Pos> comment;
        std::optional<std::pair<pos::Pos, std::u8string>> string;
        std::optional<Error> error;
    public:
        Inner();
        void run(const std::u8string &, std::queue<std::pair<pos::Range, Token>>);
    };
}
/**
 * @file error.cpp
 */

#include "error.hpp"

namespace error {
    Error::~Error() = default;
    /**
     * @brief コンストラクタ
     * @param pos 予期せぬ文字のあった場所
     */
    UnexpectedCharacter::UnexpectedCharacter(pos::Pos pos): pos(pos) {}
    /**
     * @brief コンストラクタ
     * @param poss コメントの開始位置．ネストしていた場合それら全て
     */
    UnterminatedComment::UnterminatedComment(std::vector<pos::Pos> poss): poss(std::move(poss)) {}
    /**
     * @brief コンストラクタ
     * @param pos 文字列リテラルの開始位置．
     */
    UnterminatedStringLiteral::UnterminatedStringLiteral(pos::Pos pos): pos(pos) {}

    void UnexpectedCharacter::eprint(const std::vector<std::string> &log) const {
        std::cerr << "unexpected character at " << pos << std::endl;
        pos.eprint(log);
    }
    void UnterminatedComment::eprint(const std::vector<std::string> &log) const {
        std::cerr << "unterminated comment" << std::endl;
        for(const pos::Pos &pos : poss){
            std::cerr << "started at " << pos << std::endl;
            pos.eprint(log);
        }
    }
    void UnterminatedStringLiteral::eprint(const std::vector<std::string> &log) const {
        std::cerr << "unterminated string literal (started at " << pos << ")" << std::endl;
        pos.eprint(log);
    }
}

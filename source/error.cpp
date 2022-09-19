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
    UnexpectedCharacter::UnexpectedCharacter(pos::Pos pos):
        pos(pos) {}
    /**
     * @brief コンストラクタ
     * @param poss コメントの開始位置．ネストしていた場合それら全て
     */
    UnterminatedComment::UnterminatedComment(std::vector<pos::Pos> poss):
        poss(std::move(poss)) {}
    /**
     * @brief コンストラクタ
     * @param pos 文字列リテラルの開始位置．
     */
    UnterminatedStringLiteral::UnterminatedStringLiteral(pos::Pos pos):
        pos(pos) {}
    /**
     * @brief コンストラクタ
     * @param prefix 前置演算子の位置
     * @param token 予期せぬトークンの位置
     */
    UnexpectedTokenAfterPrefix::UnexpectedTokenAfterPrefix(pos::Range prefix, pos::Range token):
        prefix(std::move(prefix)),
        token(std::move(token)) {}
    /**
     * @brief コンストラクタ
     * @param prefix 前置演算子の位置
     */
    EOFAfterPrefix::EOFAfterPrefix(pos::Range prefix):
        prefix(std::move(prefix)) {}
    /**
     * @brief コンストラクタ
     * @param open 開き括弧の位置
     */
    NoClosingBracket::NoClosingBracket(pos::Range open):
        open(std::move(open)) {}
    /**
     * @brief コンストラクタ
     * @param open 開き括弧の位置
     * @param token 予期せぬトークンの位置
     */
    UnexpectedTokenInBracket::UnexpectedTokenInBracket(pos::Range open, pos::Range token):
        open(std::move(open)),
        token(std::move(token)) {}
    DifferentClosingBracket::DifferentClosingBracket(pos::Range open, pos::Range close):
        open(std::move(open)),
        close(std::move(close)) {}
    EmptyIndex::EmptyIndex(pos::Range open, pos::Range close):
        open(std::move(open)),
        close(std::move(close)) {}
    MultipleIndices::MultipleIndices(pos::Range open, pos::Range close):
        open(std::move(open)),
        close(std::move(close)) {}
    /**
     * @brief コンストラクタ
     * @param infix 前置演算子の位置
     * @param token 予期せぬトークンの位置
     */
    UnexpectedTokenAfterInfix::UnexpectedTokenAfterInfix(pos::Range infix, pos::Range token):
        infix(std::move(infix)),
        token(std::move(token)) {}
    /**
     * @brief コンストラクタ
     * @param infix 前置演算子の位置
     */
    EOFAfterInfix::EOFAfterInfix(pos::Range infix):
        infix(std::move(infix)) {}
    /**
     * @brief コンストラクタ
     * @param comma 
     */
    EmptyItemInList::EmptyItemInList(pos::Range comma):
        comma(std::move(comma)) {}
    EOFAfterExpr::EOFAfterExpr(pos::Range expr):
        expr(std::move(expr)) {}
    UnexpectedTokenAfterExpr::UnexpectedTokenAfterExpr(pos::Range expr, pos::Range token):
        expr(std::move(expr)),
        token(std::move(token)) {}
    EOFAfterIf::EOFAfterIf(pos::Range keyword):
        keyword(std::move(keyword)) {}
    UnexpectedTokenAfterIf::UnexpectedTokenAfterIf(pos::Range keyword, pos::Range token):
        keyword(std::move(keyword)),
        token(std::move(token)) {}
    EOFAfterWhile::EOFAfterWhile(pos::Range keyword):
        keyword(std::move(keyword)) {}
    UnexpectedTokenAfterWhile::UnexpectedTokenAfterWhile(pos::Range keyword, pos::Range token):
        keyword(std::move(keyword)),
        token(std::move(token)) {}
    EOFAfterBreak::EOFAfterBreak(pos::Range keyword):
        keyword(std::move(keyword)) {}
    UnexpectedTokenAfterBreak::UnexpectedTokenAfterBreak(pos::Range keyword, pos::Range token):
        keyword(std::move(keyword)),
        token(std::move(token)) {}
    EOFAfterContinue::EOFAfterContinue(pos::Range keyword):
        keyword(std::move(keyword)) {}
    UnexpectedTokenAfterContinue::UnexpectedTokenAfterContinue(pos::Range keyword, pos::Range token):
        keyword(std::move(keyword)),
        token(std::move(token)) {}
    Unimplemented::Unimplemented(const char *file, unsigned line):
        file(file),
        line(line) {}

    void UnexpectedCharacter::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected character at " << pos << std::endl;
        pos.eprint(log);
    }
    void UnterminatedComment::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unterminated comment" << std::endl;
        for(const pos::Pos &pos : poss){
            std::cerr << "started at " << pos << std::endl;
            pos.eprint(log);
        }
    }
    void UnterminatedStringLiteral::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unterminated string literal (started at " << pos << ")" << std::endl;
        pos.eprint(log);
    }   
    void UnexpectedTokenAfterPrefix::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected token at " << token << std::endl;
        token.eprint(log);
        std::cerr << "after prefix operator at " << prefix << std::endl;
        prefix.eprint(log);
    }
    void EOFAfterPrefix::eprint(const std::deque<std::string> &log) const {
        std::cerr << "expected token, found EOF after prefix operator at " << prefix << std::endl;
        prefix.eprint(log);
    }
    void NoClosingBracket::eprint(const std::deque<std::string> &log) const {
        std::cerr << "no closing bracket corresponding to opening bracket at " << open << std::endl;
        open.eprint(log);
    }
    void UnexpectedTokenInBracket::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected token at " << token << std::endl;
        token.eprint(log);
        std::cerr << "bracket opened at " << open << std::endl;
        open.eprint(log);
    }
    void DifferentClosingBracket::eprint(const std::deque<std::string> &log) const {
        std::cerr << "closing bracket at " << close << std::endl;
        close.eprint(log);
        std::cerr << "does not match opening bracket at " << open << std::endl;
        open.eprint(log);
    }
    void UnexpectedTokenAfterInfix::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected token at " << token << std::endl;
        token.eprint(log);
        std::cerr << "after infix operator at " << infix << std::endl;
        infix.eprint(log);
    }
    void EOFAfterInfix::eprint(const std::deque<std::string> &log) const {
        std::cerr << "expected token, found EOF after infix operator at " << infix << std::endl;
        infix.eprint(log);
    }
    void EmptyItemInList::eprint(const std::deque<std::string> &log) const {
        std::cerr << "empty item, expected expression before comma at " << comma << std::endl;
        comma.eprint(log);
    }
    void EmptyIndex::eprint(const std::deque<std::string> &log) const {
        auto pos = open + close;
        std::cerr << "empty index at " << pos << std::endl;
        pos.eprint(log);
    }
    void MultipleIndices::eprint(const std::deque<std::string> &log) const {
        auto pos = open + close;
        std::cerr << "multiple indices at " << pos << std::endl;
        pos.eprint(log);
    }
    void UnexpectedTokenAfterExpr::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected token at " << token << std::endl;
        token.eprint(log);
        std::cerr << "expected semicolon after expression at " << expr << std::endl;
        expr.eprint(log);
    }
    void EOFAfterExpr::eprint(const std::deque<std::string> &log) const {
        std::cerr << "expected semicolon, found EOF after expression at " << expr << std::endl;
        expr.eprint(log);
    }
    void EOFAfterIf::eprint(const std::deque<std::string> &log) const {
        std::cerr << "expected condition, found EOF after `if` at " << keyword << std::endl;
        keyword.eprint(log);
    }
    void UnexpectedTokenAfterIf::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected token at " << token << std::endl;
        token.eprint(log);
        std::cerr << "expected condition after `if` at " << keyword << std::endl;
        keyword.eprint(log);
    }
    void EOFAfterWhile::eprint(const std::deque<std::string> &log) const {
        std::cerr << "expected condition, found EOF after `else` at " << keyword << std::endl;
        keyword.eprint(log);
    }
    void UnexpectedTokenAfterWhile::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected token at " << token << std::endl;
        token.eprint(log);
        std::cerr << "expected condition after `else` at " << keyword << std::endl;
        keyword.eprint(log);
    }
    void EOFAfterBreak::eprint(const std::deque<std::string> &log) const {
        std::cerr << "expected semicolon, found EOF after `break` at " << keyword << std::endl;
        keyword.eprint(log);
    }
    void UnexpectedTokenAfterBreak::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected token at " << token << std::endl;
        token.eprint(log);
        std::cerr << "expected semicolon after `break` at " << keyword << std::endl;
        keyword.eprint(log);
    }
    void EOFAfterContinue::eprint(const std::deque<std::string> &log) const {
        std::cerr << "expected semicolon, found EOF after `continue` at " << keyword << std::endl;
        keyword.eprint(log);
    }
    void UnexpectedTokenAfterContinue::eprint(const std::deque<std::string> &log) const {
        std::cerr << "unexpected token at " << token << std::endl;
        token.eprint(log);
        std::cerr << "expected semicolon after `continue` at " << keyword << std::endl;
        keyword.eprint(log);
    }
    void Unimplemented::eprint(const std::deque<std::string> &log) const {
        std::cerr << "error message unimplemented. file \"" << file << "\" line " << line << std::endl;
    }
}

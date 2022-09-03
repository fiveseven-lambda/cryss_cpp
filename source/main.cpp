/**
 * @file main.cpp
 */
#include "type.hpp"
#include "lexer.hpp"
#include "error.hpp"

#include <functional>
#include <iostream>

int main() {
    lexer::Lexer lexer;
    try {
        while(true){
            auto token = lexer.next();
            if(!token){
                break;
            }
            token->debug_print(0);
        }
    }catch(std::unique_ptr<error::Error> &error){
        error->eprint(lexer.get_log());
    }
    return 0;

    /*
    // グローバルな変数リスト：string → (const Type &, bool)
    // ローカルな変数リスト：string → vector<(Type &, llvm::Value *, bool)>
    // 
    // トップレベルで保管する：グローバル変数リスト
    // トップレベルの文のコンパイル：空のローカル変数リストを用意
    // ブロックのコンパイル：受け取ったグローバル／ローカル変数リストを各文に渡す
    // グローバル宣言のコンパイル：グローバルに定義
    // 式のコンパイル：ローカル変数リストを探す．見つからなかったらグローバル変数リストを参照してモジュールに宣言，ローカル変数リストに追加
    // ローカル宣言のコンパイル：スタックを確保して記録．ローカル変数リストに追加．
    //
    type::TypeContext type_context;
    auto get_integer = [&]{ return std::cref(type_context.primitive(type::PrimitiveKind::Integer)); };
    type_context.function(
        {
            type_context.function({get_integer()}, get_integer()),
            type_context.function({get_integer()}, get_integer())
        },
        type_context.function({get_integer()}, get_integer())
    );
    type_context.debug_print(0);
    */
}

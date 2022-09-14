/**
 * @file main.cpp
 */

/**
 * @mainpage Cryss (C++)
 */
#include "type.hpp"
#include "lexer.hpp"
#include "error.hpp"
#include "parser.hpp"

#include <iostream>
#include <fstream>

#include <getopt.h>

struct Config {
    std::istream &source;
    bool prompt;
};

static void run(const Config &config){
    lexer::Lexer lexer(config.source, config.prompt);
    try {
        while(true){
            auto item = parse_top_level(lexer);
            if(!item) break;
            item->debug_print(0);
        }
    }catch(std::unique_ptr<error::Error> &error){
        error->eprint(lexer.get_log());
    }
}

int main(int argc, char *argv[]) {
    if(argc == 1){
        run(Config{
            .source = std::cin,
            .prompt = true,
        });
    }else{
        std::ifstream source(argv[1]);
        run(Config{
            .source = source,
            .prompt = false,
        });
    }
    return 0;
}

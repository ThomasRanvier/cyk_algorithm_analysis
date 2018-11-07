#ifndef CYK_ALGORITHM_PARSER_H
#define CYK_ALGORITHM_PARSER_H

#include "Grammar.h"

typedef struct parser_result {
    unsigned long long int counter;
    int result;
    std::string corrected_string;
} parser_result;

class Parser {
public:
    Grammar grammar;
    static unsigned long long int counter;

    Parser(Grammar);

    virtual parser_result parse(std::string) = 0;
    virtual std::string get_name() = 0;
};


#endif
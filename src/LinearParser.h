#ifndef CYK_ALGORITHM_LINEARPARSER_H
#define CYK_ALGORITHM_LINEARPARSER_H

#include "Parser.h"
#include "LinearGrammar.h"

class LinearParser {
private:
    int ***table;
    LinearGrammar grammar;
    unsigned long long int counter;
    std::string string;

public:
    explicit LinearParser(LinearGrammar);

    parser_result parse(std::string);
    std::string get_name();
    bool parse(int, int, int);
};


#endif
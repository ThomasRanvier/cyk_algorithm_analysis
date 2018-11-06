#ifndef CYK_ALGORITHM_RECURSIVEPARSER_H
#define CYK_ALGORITHM_RECURSIVEPARSER_H

#include "Parser.h"

class NaiveParser : public Parser {
private:
    std::string string;
    bool parse(int, int, int);

public:
    explicit NaiveParser(Grammar);
    parser_result parse(std::string) override;
    std::string get_name() override;
};


#endif
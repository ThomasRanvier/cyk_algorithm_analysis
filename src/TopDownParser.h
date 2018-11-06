#ifndef CYK_ALGORITHM_TOPDOWNPARSER_H
#define CYK_ALGORITHM_TOPDOWNPARSER_H

#include "Parser.h"

class TopDownParser : public Parser {
private:
    int ***table;
    std::string string;
    bool parse(int, int, int);

public:
    explicit TopDownParser(Grammar);
    parser_result parse(std::string) override;
    std::string get_name() override;
};


#endif
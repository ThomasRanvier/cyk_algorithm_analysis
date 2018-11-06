#ifndef CYK_ALGORITHM_TOPDOWNPARSERCORRECTION_H
#define CYK_ALGORITHM_TOPDOWNPARSERCORRECTION_H

#include <climits>
#include "Parser.h"

typedef struct parse_result {
    int result;
    std::string corrected_string;
} parse_result;

class TopDownParserCorrection : public Parser {
private:
    parse_result ***table;
    std::string string;
    parse_result parse(int, int, int, std::string);
    parse_result get_min_parse_result(parse_result, parse_result, int, std::string);

public:
    explicit TopDownParserCorrection(Grammar);
    parser_result parse(std::string) override;
    std::string get_name() override;
};


#endif
#ifndef CYK_ALGORITHM_ITERATIVEPARSER_H
#define CYK_ALGORITHM_ITERATIVEPARSER_H

#include "Parser.h"
#include <iomanip>

class BottomUpParser : public Parser {
private:
    std::string concatenate(std::string, std::string);
    std::string generate_combinations(std::string, std::string);
    std::string search_production(int char_1, int char_2);
    void display_matrix(std::string **, int);

public:
    explicit BottomUpParser(Grammar);

    parser_result parse(std::string) override;
    std::string get_name() override;
};


#endif
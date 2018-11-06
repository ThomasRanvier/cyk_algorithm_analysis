#ifndef CYK_ALGORITHM_BOTTOMUPBOOLPARSER_H
#define CYK_ALGORITHM_BOTTOMUPBOOLPARSER_H

#include "Parser.h"

class BottomUpBoolParser : public Parser {
public:
    explicit BottomUpBoolParser(Grammar);

    parser_result parse(std::string) override;
    std::string get_name() override;
};


#endif
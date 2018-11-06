#include "NaiveParser.h"

NaiveParser::NaiveParser(Grammar grammar) : Parser(grammar) {}

parser_result NaiveParser::parse(std::string string) {
    this->counter = 0;
    this->string = string;

    parser_result parser_result;
    parser_result.result = parse(0, 0, string.length());
    parser_result.counter = this->counter;

    return parser_result;
}

bool NaiveParser::parse(int variable, int i, int j) {
    this->counter++;
    if (i == j - 1) {
        for (int right_hand(0); right_hand < this->grammar.terminal_rules[variable].size(); right_hand++) {
            if (this->grammar.terminal_rules[variable][right_hand] == this->string[i]) {
                return true;
            }
        }
    } else {
        for (int right_hand(0); right_hand < this->grammar.non_terminal_rules[variable].size(); right_hand++) {
            for (int k(i + 1); k < j; k++) {
                if (this->parse(this->grammar.non_terminal_rules[variable][right_hand][0], i, k) &&
                    this->parse(this->grammar.non_terminal_rules[variable][right_hand][1], k, j))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

std::string NaiveParser::get_name() {
    return "Naive parser";
}

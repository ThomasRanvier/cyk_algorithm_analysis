#include "TopDownParser.h"

TopDownParser::TopDownParser(Grammar grammar) : Parser(grammar) {}

parser_result TopDownParser::parse(std::string string) {
    this->counter = 0;
    this->string = string;

    this->table = new int **[this->grammar.terminal_rules.size()];
    for(int i = 0; i < this->grammar.terminal_rules.size(); i++) {
        this->table[i] = new int *[string.length()];
        for(int j = 0; j < string.length(); j++)
            this->table[i][j] = new int [string.length()]();
    }

    parser_result parser_result;
    parser_result.result = parse(0, 0, string.length());
    parser_result.counter = this->counter;
    return parser_result;
}

bool TopDownParser::parse(int variable, int i, int j) {
    this->counter++;

    if (this->table[variable][i][j - 1] != 0)
        return (this->table[variable][i][j - 1] == 1);

    if (i == j - 1) {
        for (int right_hand(0); right_hand < this->grammar.terminal_rules[variable].size(); right_hand++) {
            if (this->grammar.terminal_rules[variable][right_hand] == this->string[i]) {
                this->table[variable][i][j - 1] = 1;
                return true;
            }
        }
    } else {
        for (int right_hand(0); right_hand < this->grammar.non_terminal_rules[variable].size(); right_hand++) {
            for (int k(i + 1); k < j; k++) {
                if (this->parse(this->grammar.non_terminal_rules[variable][right_hand][0], i, k) &&
                    this->parse(this->grammar.non_terminal_rules[variable][right_hand][1], k, j))
                {
                    this->table[variable][i][j - 1] = 1;
                    return true;
                }
            }
        }
    }
    this->table[variable][i][j - 1] = 2;
    return false;
}

std::string TopDownParser::get_name() {
    return "Top down parser";
}

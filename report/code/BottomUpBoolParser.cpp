#include "BottomUpBoolParser.h"

BottomUpBoolParser::BottomUpBoolParser(Grammar grammar) : Parser(grammar) {}

parser_result BottomUpBoolParser::parse(std::string string) {
    this->counter = 0;

    bool ***matrix;
    matrix = new bool **[string.length()];
    for(int i = 0; i < string.length(); i++) {
        matrix[i] = new bool *[string.length()];
        for(int j = 0; j < string.length(); j++)
            matrix[i][j] = new bool [this->grammar.terminal_rules.size()]();
    }

    int step(0);
    for (int i(0); i < string.length(); i++) {
        for (int var: this->grammar.t_variables) {
            for (int right_hand(0); right_hand < this->grammar.terminal_rules[var].size(); right_hand++) {
                if (this->grammar.terminal_rules[var][right_hand] == string[i]) {
                    matrix[0][i][var] = true;
                }
                this->counter++;
            }
        }
    }

    step++;
    while (string.length() - step > 0) {
        for (int i(0); i < string.length() - step; i++) {
            for (int j(0); j < step; j++) {
                for (int var: this->grammar.nt_variables) {
                    for (int right_hand(0); right_hand < this->grammar.non_terminal_rules[var].size(); right_hand++) {
                        int var_1(this->grammar.non_terminal_rules[var][right_hand][0]);
                        int var_2(this->grammar.non_terminal_rules[var][right_hand][1]);

                        bool bool_1(matrix[j][i][var_1]);
                        bool bool_2(matrix[step - j - 1][i + j + 1][var_2]);

                        if (bool_1 && bool_2)
                            matrix[step][i][var] = true;

                        this->counter++;
                    }
                }
            }
        }
        step++;
    }

    parser_result parser_result;
    parser_result.result = matrix[string.length() - 1][0][0];
    parser_result.counter = this->counter;
    return parser_result;
}

std::string BottomUpBoolParser::get_name() {
    return "Boolean bottom up parser";
}
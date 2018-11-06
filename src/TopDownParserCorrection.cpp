#include "TopDownParserCorrection.h"

TopDownParserCorrection::TopDownParserCorrection(Grammar grammar) : Parser(grammar) {}

parser_result TopDownParserCorrection::parse(std::string string) {
    this->counter = 0;
    this->string = string;

    this->table = new parse_result **[this->grammar.terminal_rules.size()];
    for(int i = 0; i < this->grammar.terminal_rules.size(); i++) {
        this->table[i] = new parse_result *[string.length()];
        for(int j = 0; j < string.length(); j++)
            this->table[i][j] = new parse_result [string.length()]();
    }

    parser_result parser_result;
    parse_result parse_result(this->parse(0, 0, string.length(), string));
    parser_result.result = parse_result.result;
    parser_result.corrected_string = parse_result.corrected_string;
    parser_result.counter = this->counter;

    return parser_result;
}

parse_result TopDownParserCorrection::parse(int variable, int i, int j, std::string string_to_correct) {
    this->counter++;

    if (this->table[variable][i][j - 1].result != 0)
        return this->table[variable][i][j - 1];

    if (i == j - 1) {
        for (int right_hand(0); right_hand < this->grammar.terminal_rules[variable].size(); right_hand++) {
            if (this->grammar.terminal_rules[variable][right_hand] == this->string[i]) {
                this->table[variable][i][j - 1].result = 1;
                this->table[variable][i][j - 1].corrected_string = string_to_correct;
                return this->table[variable][i][j - 1];
            }
        }
        if (this->grammar.terminal_rules[variable].size() > 0) {
            this->table[variable][i][j - 1].result = 2;
            string_to_correct[0] = char(this->grammar.terminal_rules[variable][0]);
            this->table[variable][i][j - 1].corrected_string = string_to_correct;
            return this->table[variable][i][j - 1];
        }
    } else {
        int min(INT_MAX);
        std::string new_string("");

        parse_result del_1(this->parse(variable, i + 1, j,
                                            string_to_correct.substr(1, string_to_correct.size() - 1)));
        if (del_1.result < INT_MAX)
            del_1.result++;
        parse_result del_2(this->parse(variable, i, j - 1,
                                            string_to_correct.substr(0, string_to_correct.size() - 1)));
        if (del_2.result < INT_MAX)
            del_2.result++;

        for (int right_hand(0); right_hand < this->grammar.non_terminal_rules[variable].size(); right_hand++) {
            for (int k(i + 1); k < j; k++) {
                int var_1(this->grammar.non_terminal_rules[variable][right_hand][0]);
                parse_result res_1(this->parse(var_1, i, k, string_to_correct.substr(0, k - i)));

                if (res_1.result < INT_MAX) {
                    int var_2(this->grammar.non_terminal_rules[variable][right_hand][1]);
                    parse_result res_2(this->parse(var_2, k, j, string_to_correct.substr(k - i, j - k)));
                    if (res_2.result < INT_MAX) {
                        if (min > res_1.result + res_2.result - 1) {
                            min = res_1.result + res_2.result - 1;
                            new_string = res_1.corrected_string + res_2.corrected_string;
                        }
                    }
                }
            }
        }

        this->table[variable][i][j - 1] = get_min_parse_result(del_1, del_2, min, new_string);
        return this->table[variable][i][j - 1];
    }
    this->table[variable][i][j - 1].result = INT_MAX;
    this->table[variable][i][j - 1].corrected_string = string_to_correct;
    return this->table[variable][i][j - 1];
}

std::string TopDownParserCorrection::get_name() {
    return "Top down error correction parser";
}

parse_result TopDownParserCorrection::get_min_parse_result(parse_result res_1, parse_result res_2, int min,
                                                           std::string string) {
    if (res_2.result < res_1.result)
        res_1 = res_2;

    if (res_1.result > min) {
        res_1.result = min;
        res_1.corrected_string = string;
    }

    return res_1;
}

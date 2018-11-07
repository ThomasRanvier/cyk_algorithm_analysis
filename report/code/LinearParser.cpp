#include "LinearParser.h"

LinearParser::LinearParser(LinearGrammar grammar) : grammar(grammar) {}

std::string LinearParser::get_name() {
    return "Linear parser";
}

parser_result LinearParser::parse(std::string string) {
    this->counter = 0;
    this->string = string;

    clock_t begin, end;
    begin = clock();
    this->table = new int **[this->grammar.rules.size()];
    for(int i = 0; i < this->grammar.rules.size(); i++) {
        this->table[i] = new int *[string.length()];
        for(int j = 0; j < string.length(); j++)
            this->table[i][j] = new int [string.length()]();
    }
    end = clock();
    std::cout << "  " << "Time elapsed init (s) : " << double(end - begin) / CLOCKS_PER_SEC << "\n";

    parser_result parser_result;

    begin = clock();
    parser_result.result = this->parse(0, 0, string.size());
    end = clock();
    std::cout << "  " << "Time elapsed trt (s) : " << double(end - begin) / CLOCKS_PER_SEC << "\n";

    parser_result.counter = this->counter;
    return parser_result;
}

bool LinearParser::parse(int var, int i, int j) {
    this->counter++;

    if (this->table[var][i][j - 1] == 0)
        return (this->table[var][i][j - 1] == 1);

    for (int right_hand(0); right_hand < this->grammar.rules[var].size(); right_hand++) {
        if (this->grammar.rules[var][right_hand].size() == j - i && this->string.size() - i >= j - i) {
            bool is_equal(true);
            for (int k(0); k < this->grammar.rules[var][right_hand].size(); k++) {
                if (this->string[i + k] != this->grammar.rules[var][right_hand][k]) {
                    is_equal = false;
                    break;
                }
            }
            if (is_equal) {
                this->table[var][i][j - 1] = 1;
                return true;
            }
        }
        char var_1, var_2, var_3;
        if (this->grammar.rules[var][right_hand].size() == 1) {
            var_1 = this->grammar.rules[var][right_hand][0];
            if (var_1 >= 'A' && var_1 <= 'Z') {
                if (this->parse(this->grammar.non_terminals.find(var_1), i, j)) {
                    this->table[var][i][j - 1] = 1;
                    return true;
                }
            }
        } else if (j - i >= 2 && this->grammar.rules[var][right_hand].size() == 2) {
            var_1 = this->grammar.rules[var][right_hand][0];
            var_2 = this->grammar.rules[var][right_hand][1];
            if (var_1 >= 'A' && var_1 <= 'Z' && var_2 >= 'A' && var_2 <= 'Z') {
                for (int k(i + 1); k < j; k++) {
                    if (this->parse(this->grammar.non_terminals.find(var_1), i, k) &&
                        this->parse(this->grammar.non_terminals.find(var_2), k, j))
                    {
                        this->table[var][i][j - 1] = 1;
                        return true;
                    }
                }
            } else if ((var_1 < 'A' || var_1 > 'Z') && var_2 >= 'A' && var_2 <= 'Z') {
                if (this->string[i] == var_1) {
                    if (this->parse(this->grammar.non_terminals.find(var_2), i + 1, j)) {
                        this->table[var][i][j - 1] = 1;
                        return true;
                    }
                }
            } else if (var_1 >= 'A' && var_1 <= 'Z' && (var_2 < 'A' || var_2 > 'Z')) {
                if (this->string[j - 1] == var_2) {
                    if (this->parse(this->grammar.non_terminals.find(var_1), i, j - 1)) {
                        this->table[var][i][j - 1] = 1;
                        return true;
                    }
                }
            }
        } else if (j - i >= 3 && this->grammar.rules[var][right_hand].size() == 3) {
            var_1 = this->grammar.rules[var][right_hand][0];
            var_2 = this->grammar.rules[var][right_hand][1];
            var_3 = this->grammar.rules[var][right_hand][2];
            if (var_1 >= 'A' && var_1 <= 'Z' && (var_2 < 'A' || var_2 > 'Z') && var_3 >= 'A' && var_3 <= 'Z') {
                for (int k(i + 1); k < j - 1; k++) {
                    if (this->parse(this->grammar.non_terminals.find(var_1), i, k) &&
                        var_2 == this->string[k] &&
                        this->parse(this->grammar.non_terminals.find(var_3), k + 1, j))
                    {
                        this->table[var][i][j - 1] = 1;
                        return true;
                    }
                }
            } else if ((var_1 < 'A' || var_1 > 'Z') && var_2 >= 'A' && var_2 <= 'Z' && (var_3 < 'A' || var_3 > 'Z')) {
                if (var_1 == this->string[i] &&
                    this->parse(this->grammar.non_terminals.find(var_2), i + 1, j - 1) &&
                    var_3 == this->string[j - 1])
                {
                    this->table[var][i][j - 1] = 1;
                    return true;
                }
            }
        }
    }

    this->table[var][i][j - 1] = 2;
    return false;
}

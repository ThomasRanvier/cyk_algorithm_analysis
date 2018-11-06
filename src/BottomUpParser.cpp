#include "BottomUpParser.h"

BottomUpParser::BottomUpParser(Grammar grammar) : Parser(grammar) {}

parser_result BottomUpParser::parse(std::string string) {
    this->counter = 0;

    std::string **matrix;
    matrix = new std::string *[string.length()];
    for(int i = 0; i < string.length(); i++)
        matrix[i] = new std::string[string.length()];

    int step(0);
    for (int i(0); i < string.length(); i++) {
        for (int var: this->grammar.t_variables) {
            for (int right_hand(0); right_hand < this->grammar.terminal_rules[var].size(); right_hand++) {
                if (this->grammar.terminal_rules[var][right_hand] == string[i]) {
                    std::string variable("");
                    variable = var;
                    matrix[step][i] = concatenate(matrix[step][i], variable);
                }
                this->counter++;
            }
        }
    }

    step++;
    while (string.length() - step > 0) {
        for (int i(0); i < string.length() - step; i++) {
            for (int j(0); j < step; j++) {
                std::string cell_1(matrix[j][i]), cell_2(matrix[step - (j + 1)][i + j + 1]);
                if (cell_1 != "" && cell_2 != "")
                    matrix[step][i] = concatenate(matrix[step][i], generate_combinations(cell_1, cell_2));
                this->counter++;
            }
        }
        step++;
    }

    parser_result parser_result;
    parser_result.result = (matrix[string.length() - 1][0].find(char(0)) <= string.length());
    parser_result.counter = this->counter;

    //display_matrix(matrix, string.length());

    return parser_result;
}

std::string BottomUpParser::concatenate(std::string a, std::string b) {
    std::string result = a;
    for(int i(0); i < b.length(); i++) {
        if(result.find(b[i]) > result.length()) {
            result += b[i];
        }
    }
    return (result);
}

std::string BottomUpParser::generate_combinations(std::string cell_1, std::string cell_2) {
    std::string result("");
    for(int i(0); i < cell_1.length(); i++) {
        for(int j(0); j < cell_2.length(); j++) {
            result += search_production(cell_1[i], cell_2[j]);
        }
    }

    return result;
}

std::string BottomUpParser::search_production(int char_1, int char_2) {
    std::string result("");
    for (int var: this->grammar.nt_variables) {
        for (int right_hand(0); right_hand < this->grammar.non_terminal_rules[var].size(); right_hand++) {
            if (this->grammar.non_terminal_rules[var][right_hand][0] == char_1 &&
                this->grammar.non_terminal_rules[var][right_hand][1] == char_2)
            {
                std::string variable("");
                variable = var;
                result = concatenate(result, variable);
            }
            this->counter++;
        }
    }
    return result;
}

void BottomUpParser::display_matrix(std::string ** matrix, int size) {
    for(int i(0); i < size; i++) {
        std::cout << "  ";
        for(int j(0); j < size; j++) {
            std::cout << std::setw(8);
            for (int k(0); k < matrix[i][j].length(); k++) {
                std::cout << int(matrix[i][j][k]) << " ";
            }
        }
        std::cout << "\n";
    }
}

std::string BottomUpParser::get_name() {
    return "String bottom up parser";
}

#ifndef CYK_ALGORITHM_NEWGRAMMAR_H
#define CYK_ALGORITHM_NEWGRAMMAR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

class Grammar {
private:
    std::vector<std::vector<std::vector<int>>> raw_grammar;
    std::vector<std::vector<std::vector<int>>> converted_grammar;
    std::string non_terminals;
    bool start_symbol_in_raw_right_hand;

    void load_raw_grammar(std::string basic_string);
    void convert_to_chomsky();
    void replace_raw_non_terminals();
    void eliminate_start_symbol();
    void display_grammar(std::vector<std::vector<std::vector<int>>> grammar);
    void replace_terminals_by_new_non_terminals();
    void eliminate_right_hands_with_too_much_nt();
    void eliminate_unit_rules();
    void fill_final_variables();
public:
    std::vector<std::vector<std::vector<int>>> non_terminal_rules;
    std::vector<std::vector<int>> terminal_rules;
    std::string nt_variables, t_variables;

    explicit Grammar(std::string, bool = true);

    void display_raw_grammar();
    void display_converted_grammar();
    void display_final_grammar();
};


#endif
#include "Grammar.h"

Grammar::Grammar(std::string filename, bool convert) {
    this->non_terminals = "";
    this->nt_variables = "";
    this->t_variables = "";
    this->start_symbol_in_raw_right_hand = false;
    this->load_raw_grammar(filename);
    this->converted_grammar = this->raw_grammar;
    if (convert)
        this->convert_to_chomsky();
    this->fill_final_variables();
}

void Grammar::display_raw_grammar() {
    std::cout << "\nRaw grammar :\n";
    this->display_grammar(this->raw_grammar);
}

void Grammar::display_converted_grammar() {
    std::cout << "\nConverted grammar :\n";
    this->display_grammar(this->converted_grammar);
}

void Grammar::display_final_grammar() {
    std::cout << "\nFinal grammar :\n";
    std::cout << "Non-terminal rules :\n";
    for (int var: this->nt_variables) {
        std::cout << var << " -> ";
        for (int right_hand(0); right_hand < this->non_terminal_rules[var].size(); right_hand++) {
            std::cout << std::setw(5);
            std::cout << this->non_terminal_rules[var][right_hand][0]
                      << " " << this->non_terminal_rules[var][right_hand][1];
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\nTerminal rules :\n";
    for (int var: this->t_variables) {
        std::cout << var << " -> ";
        for (int right_hand(0); right_hand < this->terminal_rules[var].size(); right_hand++) {
            std::cout << std::setw(3);
            std::cout << char(this->terminal_rules[var][right_hand]) << " ";
        }
        std::cout << "\n";
    }
}

void Grammar::display_grammar(std::vector<std::vector<std::vector<int>>> grammar) {
    for (int i(0); i < grammar.size(); i++) {
        std::cout << i << " -> ";
        for (int j(0); j < grammar[i].size(); j++) {
            std::cout << std::setw(5);
            for (int k(0); k < grammar[i][j].size(); k++) {
                std::cout << grammar[i][j][k] << " ";
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

void Grammar::load_raw_grammar(std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            this->non_terminals += line[0];
            line = line.substr(3, line.length());
            std::vector<std::vector<int>> right_hands;
            while(line.length() > 0) {
                std::vector<int> right_hand;
                int separator = line.find("|");
                if(separator > line.length()) {
                    for (int i(0); i < line.size(); i++) {
                        right_hand.push_back((line[i] < 'A' || line[i] > 'Z') ? -(int(line[i])) : line[i]);
                    }
                    line = "";
                } else {
                    std::string sub(line.substr(0, separator));
                    for (int i(0); i < sub.size(); i++) {
                        right_hand.push_back((sub[i] < 'A' || sub[i] > 'Z') ? -(int(sub[i])) : sub[i]);
                    }
                    line = line.substr(separator + 1, line.length());
                }
                right_hands.push_back(right_hand);
            }
            this->raw_grammar.push_back(right_hands);
        }
        file.close();
    }
    this->replace_raw_non_terminals();
}

void Grammar::replace_raw_non_terminals() {
    for (int i(0); i < this->raw_grammar.size(); i++) {
        for (int j(0); j < this->raw_grammar[i].size(); j++) {
            for (int k(0); k < this->raw_grammar[i][j].size(); k++) {
                int index(this->non_terminals.find(this->raw_grammar[i][j][k]));
                if (index <= this->non_terminals.size())
                    this->raw_grammar[i][j][k] = index;
                if (index == 0)
                    this->start_symbol_in_raw_right_hand = true;
            }
        }
    }
}

void Grammar::convert_to_chomsky() {
    if (this->start_symbol_in_raw_right_hand)
        this->eliminate_start_symbol();
    this->replace_terminals_by_new_non_terminals();
    this->eliminate_right_hands_with_too_much_nt();
    this->eliminate_unit_rules();
}

void Grammar::eliminate_start_symbol() {
    for (int i(0); i < this->converted_grammar.size(); i++) {
        for (int j(0); j < this->converted_grammar[i].size(); j++) {
            for (int k(0); k < this->converted_grammar[i][j].size(); k++) {
                if (this->converted_grammar[i][j][k] >= 0)
                    this->converted_grammar[i][j][k]++;
            }
        }
    }
    std::vector<std::vector<int>> start_symbol_right_hand = {{1}};
    this->converted_grammar.insert(this->converted_grammar.begin(), start_symbol_right_hand);
}

void Grammar::replace_terminals_by_new_non_terminals() {
    int grammar_size(this->converted_grammar.size());
    for (int i(0); i < grammar_size; i++) {
        for (int j(0); j < this->converted_grammar[i].size(); j++) {
            if (this->converted_grammar[i][j].size() > 1) {
                for (int k(0); k < this->converted_grammar[i][j].size(); k++) {
                    if (this->converted_grammar[i][j][k] < 0) {
                        std::vector<std::vector<int>> new_right_hand = {{this->converted_grammar[i][j][k]}};
                        this->converted_grammar.push_back(new_right_hand);

                        int terminal_to_replace(this->converted_grammar[i][j][k]);
                        int replace_value(int(this->converted_grammar.size()) - 1);
                        for (int l(0); l < grammar_size; l++) {
                            for (int m(0); m < this->converted_grammar[l].size(); m++) {
                                for (int n(0); n < this->converted_grammar[l][m].size(); n++) {
                                    if (this->converted_grammar[l][m][n] == terminal_to_replace)
                                        this->converted_grammar[l][m][n] = replace_value;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Grammar::eliminate_right_hands_with_too_much_nt() {
    for (int i(0); i < this->converted_grammar.size(); i++) {
        for (int j(0); j < this->converted_grammar[i].size(); j++) {
            if (this->converted_grammar[i][j].size() > 2) {
                std::vector<std::vector<int>> new_right_hand_parent;
                std::vector<int> new_right_hand_child;
                for (int k(1); k < this->converted_grammar[i][j].size(); k++) {
                    new_right_hand_child.push_back(this->converted_grammar[i][j][k]);
                }
                new_right_hand_parent.push_back(new_right_hand_child);
                this->converted_grammar.push_back(new_right_hand_parent);
                this->converted_grammar[i][j] = {this->converted_grammar[i][j][0],
                                                 int(this->converted_grammar.size()) - 1};
            }
        }
    }
}

void Grammar::eliminate_unit_rules() {
    for (int i(this->converted_grammar.size() - 1); i >= 0; i--) {
        for (int j(0); j < this->converted_grammar[i].size(); j++) {
            if (this->converted_grammar[i][j].size() == 1 && this->converted_grammar[i][j][0] >= 0) {
                int nt(this->converted_grammar[i][j][0]);
                this->converted_grammar[i].erase(this->converted_grammar[i].begin() + j);
                for (int k(0); k < this->converted_grammar[nt].size(); k++) {
                    this->converted_grammar[i].push_back(this->converted_grammar[nt][k]);
                }
            }
        }
    }
}

void Grammar::fill_final_variables() {
    for (int i(0); i < this->converted_grammar.size(); i++) {
        std::vector<std::vector<int>> non_terminal_right_hands;
        std::vector<int> terminal_right_hands;
        bool nt(false), t(false);
        for (int j(0); j < this->converted_grammar[i].size(); j++) {
            if (this->converted_grammar[i][j].size() == 1) {
                terminal_right_hands.push_back(-this->converted_grammar[i][j][0]);
                t = true;
            } else {
                std::vector<int> non_terminal_right_hand = {this->converted_grammar[i][j][0],
                                                            this->converted_grammar[i][j][1]};
                non_terminal_right_hands.push_back(non_terminal_right_hand);
                nt = true;
            }
        }
        this->non_terminal_rules.push_back(non_terminal_right_hands);
        this->terminal_rules.push_back(terminal_right_hands);
        if (nt)
            this->nt_variables += i;
        if (t)
            this->t_variables += i;
    }
}

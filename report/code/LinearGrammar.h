#ifndef CYK_ALGORITHM_LINEARGRAMMAR_H
#define CYK_ALGORITHM_LINEARGRAMMAR_H

#include <iomanip>
#include <vector>
#include <fstream>
#include <iostream>

class LinearGrammar {
public:
    std::string non_terminals;
    std::vector<std::vector<std::string>> rules;

    explicit LinearGrammar(std::string);
    void display_rules();
};


#endif
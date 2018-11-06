#include "LinearGrammar.h"

LinearGrammar::LinearGrammar(std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            this->non_terminals += line[0];
            line = line.substr(3, line.length());
            std::vector<std::string> right_hands;
            while(line.length() > 0) {
                int separator = line.find("|");
                if(separator > line.length()) {
                    right_hands.push_back(line);
                    line = "";
                } else {
                    std::string sub(line.substr(0, separator));
                    right_hands.push_back(sub);
                    line = line.substr(separator + 1, line.length());
                }
            }
            this->rules.push_back(right_hands);
        }
        file.close();
    }
}

void LinearGrammar::display_rules() {
    std::cout << "Linear grammar :\n";
    for (int i(0); i < this->rules.size(); i++) {
        std::cout << i << " -> ";
        for (int j(0); j < this->rules[i].size(); j++) {
            std::cout << std::setw(5);
            std::cout << this->rules[i][j];
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

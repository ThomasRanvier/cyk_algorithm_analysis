#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include "Enumeration.h"

Enumeration::Enumeration(std::string filename) : filename(filename) {
    std::ifstream file(this->filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            this->initial_patterns.push_back(line);

            std::string string("");
            std::istringstream iss(line);
            std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                            std::istream_iterator<std::string>{}};

            for (int i(0); i < tokens.size(); i++) {
                if (tokens[i].find('^') <= tokens[i].size()) {
                    int iterations(std::stoi(tokens[i].substr(2, tokens[i].length())));
                    for (int j(0); j < iterations; j++) {
                        string += tokens[i][0];
                    }
                } else {
                    string += tokens[i];
                }
            }

            this->generated_strings.push_back(string);
        }
        file.close();
    }
}

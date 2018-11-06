#ifndef CYK_ALGORITHM_ENUMERATION_H
#define CYK_ALGORITHM_ENUMERATION_H

#include <string>
#include <vector>

class Enumeration {
private:
    std::string filename;
public:
    Enumeration(std::string);

    std::vector<std::string> generated_strings, initial_patterns;
};


#endif
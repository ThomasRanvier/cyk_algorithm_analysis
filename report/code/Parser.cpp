#include "Parser.h"

Parser::Parser(Grammar grammar) : grammar(grammar) {}

unsigned long long int Parser::counter = 0;
# CYK implementations

To run this program the first thing to do is to import the project in an IDE that handles C++.

In the main.cpp file there is a constant named GRAMMAR_FILE.
It corresponds to the path of the file that contains the grammar.

In the main.cpp file there is also a constant named STRINGS_FILE.
It corresponds to the path of the file that contains the patterns of the strings to generate.

In the main.cpp file there is also a constant named RUNNING_CASE.
It corresponds to the parser(s) that you want to include in the run, it can be set to:
..*"naive": Runs only the naive parser
..*"topdown": Runs only the top-down parser
..*"string": Runs only the 'string' bottom-up parser
..*"boolean": Runs only the 'boolean' bottom-up parser
..*"linear": Runs only the linear parser
..*"correction": Runs only the correction parser
..*"basic": Runs only the top-down, 'string' bottom-up and 'boolean' bottom-up parsers
..*"all": Runs all the parsers
..*"without_naive": Runs all the parsers except for the naive one

The directory contains several grammar and strings files that you can use as examples.

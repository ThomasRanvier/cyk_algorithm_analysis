#include "BottomUpParser.h"
#include "BottomUpBoolParser.h"
#include "NaiveParser.h"
#include "TopDownParser.h"
#include "Enumeration.h"
#include "Grammar.h"
#include "TopDownParserCorrection.h"
#include "LinearGrammar.h"
#include "LinearParser.h"

const char * GRAMMAR_FILE("../grammar_2.txt");
const char * STRINGS_FILE("../strings_2.txt");
const std::string RUNNING_CASE("without_naive");

const bool CONVERT_TO_CHOMSKY_NORMAL_FORM(true);

void run_parser(std::string, Parser *);
void run_linear_parser(std::string, LinearParser *);
void run_correction_parser(std::string, TopDownParserCorrection *);

int main(int argv, char **argc) {
    //Creation of the linear grammar, which can handle linear and Chomsky normal-form
    LinearGrammar linear_grammar = LinearGrammar(GRAMMAR_FILE);
    linear_grammar.display_rules();

    //Creation of the grammar
    Grammar grammar = Grammar(GRAMMAR_FILE, CONVERT_TO_CHOMSKY_NORMAL_FORM);
    //grammar.display_raw_grammar();
    //grammar.display_converted_grammar();
    grammar.display_final_grammar();

    //Instanciation of the enumeration with creation of the strings following the patterns in strings_file
    Enumeration enumeration = Enumeration(STRINGS_FILE);

    //Instanciation of the diverse parsers
    BottomUpParser string_bottom_up_parser = BottomUpParser(grammar);
    BottomUpBoolParser bool_bottom_up_parser = BottomUpBoolParser(grammar);
    TopDownParser top_down_parser = TopDownParser(grammar);
    NaiveParser naive_parser = NaiveParser(grammar);
    LinearParser linear_parser = LinearParser(linear_grammar);
    TopDownParserCorrection correction_top_down_parser = TopDownParserCorrection(grammar);

    //For each generated string run the parsers depending on the running case
    for (int i(0); i < enumeration.generated_strings.size(); i++) {
        std::cout << "\nPattern : " << enumeration.initial_patterns[i] << "\n";
        if (RUNNING_CASE == "naive") {
            run_parser(enumeration.generated_strings[i], &naive_parser);
        } else if (RUNNING_CASE == "topdown") {
            run_parser(enumeration.generated_strings[i], &top_down_parser);
        } else if (RUNNING_CASE == "string") {
            run_parser(enumeration.generated_strings[i], &string_bottom_up_parser);
        } else if (RUNNING_CASE == "boolean") {
            run_parser(enumeration.generated_strings[i], &bool_bottom_up_parser);
        } else if (RUNNING_CASE == "linear") {
            run_linear_parser(enumeration.generated_strings[i], &linear_parser);
        } else if (RUNNING_CASE == "correction") {
            run_correction_parser(enumeration.generated_strings[i], &correction_top_down_parser);
        } else if (RUNNING_CASE == "basic") {
            run_parser(enumeration.generated_strings[i], &top_down_parser);
            run_parser(enumeration.generated_strings[i], &string_bottom_up_parser);
            run_parser(enumeration.generated_strings[i], &bool_bottom_up_parser);
        } else if (RUNNING_CASE == "all") {
            run_parser(enumeration.generated_strings[i], &naive_parser);
            run_parser(enumeration.generated_strings[i], &top_down_parser);
            run_parser(enumeration.generated_strings[i], &string_bottom_up_parser);
            run_parser(enumeration.generated_strings[i], &bool_bottom_up_parser);
            run_linear_parser(enumeration.generated_strings[i], &linear_parser);
            run_correction_parser(enumeration.generated_strings[i], &correction_top_down_parser);
        } else if (RUNNING_CASE == "without_naive") {
            run_parser(enumeration.generated_strings[i], &top_down_parser);
            run_parser(enumeration.generated_strings[i], &string_bottom_up_parser);
            run_parser(enumeration.generated_strings[i], &bool_bottom_up_parser);
            run_linear_parser(enumeration.generated_strings[i], &linear_parser);
            run_correction_parser(enumeration.generated_strings[i], &correction_top_down_parser);
        } else {
            std::cout << "The running case does not match any known case.\n";
            abort();
        }
    }

    return 0;
}

void run_correction_parser(std::string string, TopDownParserCorrection *parser) {
    clock_t begin, end;
    std::cout << "\n" << parser->get_name() << " : \n";
    begin = clock();
    parser_result correction_parser_result(parser->parse(string));
    end = clock();

    if (correction_parser_result.result == INT_MAX) {
        std::cout << "  " << "Result : Impossible\n";
    } else {
        int deletions(string.size() - correction_parser_result.corrected_string.size()),
                modifications(correction_parser_result.result - 1 - deletions);
        std::cout << "  " << "Result : needs " << modifications << " replacement(s)\n";
        std::cout << "  " << "Result : needs " << deletions << " deletion(s)\n";
        std::cout << "  " << "Corrected string : " << correction_parser_result.corrected_string << "\n";
    }
    std::cout << "  " << "Counter : " << correction_parser_result.counter << "\n";
    std::cout << "  " << "Time elapsed (s) : " << double(end - begin) / CLOCKS_PER_SEC << "\n";
}

void run_linear_parser(std::string string, LinearParser *parser) {
    clock_t begin, end;
    std::cout << "\n" << parser->get_name() << " : \n";
    begin = clock();
    parser_result linear_parser_result(parser->parse(string));
    end = clock();
    std::cout << "  " << "Result : " << (linear_parser_result.result ? "true" : "false") << "\n";
    std::cout << "  " << "Counter : " << linear_parser_result.counter << "\n";
    std::cout << "  " << "Time elapsed (s) : " << double(end - begin) / CLOCKS_PER_SEC << "\n";
}

void run_parser(std::string string, Parser *parser) {
    clock_t begin, end;
    std::cout << "\n" << parser->get_name() << " : \n";
    begin = clock();
    parser_result parser_result(parser->parse(string));
    end = clock();
    if (parser_result.result <= 1) {
        std::cout << "  " << "Result : " << (parser_result.result ? "true" : "false") << "\n";
    } else {
        std::cout << "  " << "Result : needs " << parser_result.result - 1 << " replacements\n";
    }
    std::cout << "  " << "Counter : " << parser_result.counter << "\n";
    std::cout << "  " << "Time elapsed (s) : " << double(end - begin) / CLOCKS_PER_SEC << "\n";
}

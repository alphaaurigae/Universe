#include "argument_parser.h"

#include "unicode_range.h"
#include "unicode_string.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>


int main(int argc, char* argv[]) {
    std::vector<std::string> ranges;
    std::string input;
    int print_flags = 0;
    bool newline = false;
    bool is_range = false;
    bool is_input = false;

    parseCommandLineArgs(argc, argv, ranges, input, print_flags, newline, is_range, is_input);

    if (is_range && ranges.empty()) {
        std::cerr << "Error: No range provided for unicode ranges." << std::endl;
        return 1;
    }
    
    if (!is_range && input.empty()) {
        std::cerr << "Error: No input string provided for unicode string." << std::endl;
        return 1;
    }

    bool print_numbers = print_flags & 1;
    bool print_hex = print_flags & 2;
    bool print_sym = print_flags & 4;

    std::string output;
    if (is_range) {
        printUnicodeRange(ranges, print_numbers, print_hex, print_sym, newline, output);
    } else {
        printUnicodeString(input, print_numbers, print_hex, print_sym, newline, output);
    }

    if (newline) {
        std::cout << output;
    } else {
        std::stringstream ss(output);
        std::string line;
        while (std::getline(ss, line)) {
            std::cout << line << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
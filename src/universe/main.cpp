#include "argument_parser.h"
#include "unicode_range.h"
#include "unicode_string.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

int main(int argc, char* argv[]) {
    std::vector<std::string> ranges;
    std::string input;
    uint8_t print_flags = 0;
    bool is_range = false;
    bool is_input = false;

    parseCommandLineArgs(argc, argv, ranges, input, print_flags, is_range, is_input);

    if (is_range && ranges.empty()) {
        std::cerr << "Error: No range provided for unicode ranges." << std::endl;
        return 1;
    }

    if (!is_range && input.empty()) {
        std::cerr << "Error: No input string provided for unicode string." << std::endl;
        return 1;
    }

    std::string output;

    if (is_range) {
        printUnicodeRange(ranges, print_flags, output);
    } else {
        printUnicodeString(input, print_flags, output);
    }

    if (print_flags & 0x8) { // Check if newline flag is set
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
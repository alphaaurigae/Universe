#include "argument_parser.h"
#include "unicode_range.h"
#include "unicode_string.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

#include <nlohmann/json.hpp>

void generateJsonOutput(int argc, char* argv[], const std::string& input, uint8_t print_flags, char main_delimiter, char block_delimiter, bool is_json) {
    nlohmann::json json_output;

    std::string symbols, decimals, hexadecimals;

    for (char c : input) {
        if (print_flags & 0x4) {  // Symbol
            symbols += std::string(1, c) + (main_delimiter != '\0' ? std::string(1, main_delimiter) : "");
        }
        if (print_flags & 0x1) {  // Decimal
            decimals += std::to_string(static_cast<int>(c)) + (main_delimiter != '\0' ? std::string(1, main_delimiter) : "");
        }
        if (print_flags & 0x2) {  // Hexadecimal
            std::stringstream hex_stream;
            hex_stream << "0x" << std::hex << static_cast<int>(c);
            hexadecimals += hex_stream.str() + (main_delimiter != '\0' ? std::string(1, main_delimiter) : "");
        }
    }

    if (is_json) {
        std::string arguments;
        for (int i = 1; i < argc; ++i) {
            arguments += argv[i];
            if (i < argc - 1) arguments += " ";
        }

        json_output["arguments"] = arguments;
        json_output["input"] = input;
        json_output["output"]["symbols"] = symbols;
        json_output["output"]["decimals"] = decimals;
        json_output["output"]["hexadecimals"] = hexadecimals;
        std::cout << json_output.dump(4) << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> ranges;
    std::string input;
    uint8_t print_flags = 0;
    bool is_range = false;
    bool is_input = false;
    bool is_json = false;
    char main_delimiter = ' ';
    char block_delimiter = ' ';

    parseCommandLineArgs(argc, argv, ranges, input, print_flags, is_range, is_input, is_json, main_delimiter, block_delimiter);

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
        printUnicodeRange(ranges, print_flags, output, main_delimiter, block_delimiter);
    } else {
        printUnicodeString(input, print_flags, output, main_delimiter, block_delimiter);
    }

    if (is_json) {
        generateJsonOutput(argc, argv, input, print_flags, main_delimiter, block_delimiter, is_json);
    } else {
        if (print_flags & 0x8) {
            std::cout << output;
        } else {
            std::stringstream ss(output);
            std::string line;
            while (std::getline(ss, line)) {
                std::cout << line << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
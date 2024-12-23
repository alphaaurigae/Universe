#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cstdint>

inline void printHelpMenu() {
    std::cout << "Usage: ./universe [OPTIONS] [INPUT]\n\n"
              << "-h, --help      Show help menu.\n\n"
              << "Options:\n"
              << "-s, --symbol    Output Rendered Unicode Symbol\n"
              << "-d, --dnum      Output the Unicode code point as a base-10 decimal integer.\n"
              << "-x, --hnum      Output the Unicode code point as a base-16 hexadecimal integer, prefix '0x'.\n"
              << "-n, --newline   Print each output in a new line.\n\n"
              << "Input:\n"
              << "-r, --range     Input as a range of Unicode code points..\n"
              << "                The input can be one or more of the following formats e.g:\n"
              << "                 - Single base-10 (decimal) integer code point [65]\n"
              << "                 - Single base-16 (hexadecimal) integer code point [0x41]\n"
              << "                 - Range of decimal code points [60-90]\n"
              << "                 - Range of hexadecimal code points [0x41-0x5A]\n"
              << "                 - Comma-separated list of decimal code points and/or ranges [65,70-75]\n"
              << "                 - Comma-separated list of hexadecimal code points and/or ranges [0x41,0x46-0x4B]\n"
              << "                 - Mixed [65,0x67,70-75,0x41-0x5A]\n"
              << "-ia, --input-arg   Input as a UTF-8\n\n"
              << "Sample:\n"
              << "./universe -s -n -r \"60-9\"\n"
              << "./universe -s -x -n -r  \"60-90\"\n"
              << "./universe -s -x -d -n -r 60-90\n"
              << "./universe -s -x -d -n -r  \"0x41-0x5A\"\n"
              << "./universe -s -n -x -ia \"foo bar barr fooo 1337\"\n\n"
              << "Info:" << std::endl
              << "\"argument\" or \'argument\' or arguments as input" << std::endl
              << "Ranges can be specified in the following formats:" << std::endl
              << "Single: e.g. 65" << std::endl
              << "Range: e.g. 0x41-0x5A" << std::endl
              << "Comma-separated list single and range: 0x41,0x43,0x46-0x4B" << std::endl;
}


inline void parseCommandLineArgs(int argc, char* argv[], std::vector<std::string>& ranges, std::string& input, uint8_t& print_flags, bool& is_range, bool& is_input) {
    if (argc == 1) {
        printHelpMenu();
        exit(0);
    }

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            printHelpMenu();
            exit(0);
        } else if (arg == "-r" || arg == "--range") {
            is_range = true;
            i++;
            while (i < argc && argv[i][0] != '-') {
                std::string range = argv[i];
                std::replace(range.begin(), range.end(), ' ', ',');
                ranges.push_back(range);
                i++;
            }
            i--;
        } else if (arg == "-d" || arg == "--dnum") {
            print_flags |= 1;
        } else if (arg == "-x" || arg == "--hnum") {
            print_flags |= 2;
        } else if (arg == "-s" || arg == "--symbol") {
            print_flags |= 4;
        } else if (arg == "-n" || arg == "--newline") {
            print_flags |= 8;
        } else if (arg == "-ia" || arg == "--input-arg") {
            is_input = true;
            i++;
            if (i < argc) {
                input = argv[i];
            }
        } else {
            std::cerr << "Error: Invalid argument: " << arg << std::endl;
            exit(1);
        }
    }
}


#endif
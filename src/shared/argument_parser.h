#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

inline void printHelpMenu() {
    std::cout << "Usage: ./universe [OPTIONS] -r range1 range2 ... OR -ia input\n\n"
              << "OPTIONS:\n"
              << "  -h, --help         Show help menu.\n"
              << "  -r, --range        Treat input as a range of Unicode numbers.\n"
              << "  -s, --symbol       Print symbol of each character.\n"
              << "  -d, --dnum         Print decimal code point value of each character.\n"
              << "  -x, --hnum         Print hexadecimal code point value of each character.\n"
              << "  -n, --newline      Print each output in a new line.\n"
              << "  -ia, --input-arg   Treat input as a string.\n"
              << "EXAMPLES:\n"
              << "bin/universe -s -n -r \"60-9\"\n"
              << "bin/universe -s -x -n -r  \"60-90\"\n"
              << "bin/universe -s -x -d -n -r 60-90\n"
              << "bin/universe -s -x -d -n -r  \"0x41-0x5A\"\n"
              << "bin/universe -s -n -x -ia \"foo bar barr fooo 1337\"\n"
              << "  may use \"argument\" for arguments" << std::endl
              << "  The ranges of Unicode numbers to print. Can be specified in the following formats:" << std::endl
              << "  - Single number: e.g. 65 (0x41)" << std::endl
              << "  - Range of numbers: e.g. 65-90 (0x41-0x5A)" << std::endl
              << "  - Comma-separated list of numbers and/or ranges: e.g. 65,67,70-75 (0x41,0x43,0x46-0x4B)" << std::endl
              << "Note: The hexadecimal values shown in parentheses are the code point values." << std::endl
              << "If -ia option is used, the input will be treated as a string instead of Unicode ranges." << std::endl;
}

inline void parseCommandLineArgs(int argc, char* argv[], std::vector<std::string>& ranges, std::string& input, int& print_flags, bool& newline, bool& is_range, bool& is_input) {
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
            newline = true;
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

#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <bitset>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cstdint>

inline void printHelpMenu() {
    std::cout << "Usage: ./universe [OUPUT OPTIONS] [DELIMETER OPTIONS] [INPUT]\n\n"
              << "-h, --help      Show help menu.\n\n"
              << "Output print:\n"
              << "-s, --symbol    Unicode rendered Symbol\n"
              << "-d, --dnum      Unicode decimal.\n"
              << "-x, --utf8      Unicode utf-8 hexadecimal, prefix '0x'.\n"
              << "-t, --utf16     Unicode utf-16 hexadecimal, prefix '0x'.\n"
              << "-u, --utf32     Unicode utf-32 hexadecimal, prefix '0x'.\n\n"
              << "Output format (optionally):\n"
              << "-n, --newline   Each output in a new line.\n"
              // << "-j, --json      (optionally) JSON format.\n\n"
              << "Delimeter options:\n"
              << " to separate main output e.g 0x101,e, \n"
              << "--main_delimiter_space   \n"
              << "--main_delimiter_none   \n"
              << "--main_delimiter_comma   \n"
              << "--main_delimiter_semicolon   \n"
              << " to separate blocks output e.g ;0x69,E,;;0x70,F,;\n"
              << "--block_delimiter_space   \n"
              << "--block_delimiter_none  \n"
              << "--block_delimiter_comma   \n"
              << "--block_delimiter_semicolon   \n"
              << "Input:\n"
              << "-r, --range | Input as base-10 decimal & base-16 hexadecimal singles and ranges\n"
              << "-ia, --input-arg   Input as a UTF-8\n\n"
              << "The input can be one or more of the following formats:\n"
              << "For -r \n"
              << "1. Single (decimal) [65]\n"
              << "2. Single (hexadecimal) [0x41] [0xe2/0x81/0xb5] [0x2074] [0x000000e2] , \n"
              << "3. Range of decimal code points [60-90]\n"
              << "4. Range of hexadecimal [0x41-0x5A]\n"
              << "5. Comma-separated list of decimal code points and/or ranges [65,70-75]\n"
              << "6. Comma-separated list of hexadecimal code points and/or ranges [0x41,0x46-0x4B]\n"
              << "7. Mixed [65,0x67,70-75,0x41-0x5A]\n"
              << "Samples -r:\n"
              << "./universe -s -n -r \"60-9\"\n"
              << "./universe -s -x -n -r  \"60-90\"\n"
              << "./universe -s -x -d -n -r 60-90\n"
              << "./universe -s -x -d -n -r  \"0x41-0x5A\"\n"
              << "Ranges can be specified in the following formats:\n"
              << "Single: e.g. 65\n"
              << "Range: e.g. 0x41-0x5A\n"
              << "Comma-separated list single and range: 0x41,0x43,0x46-0x4B\n\n"
              << "Samples --ia \n"
              << "\"UTF-8 input e.g [\"input\"] \n"
              << " For -ia ALL CHARACTERS are input unless \\ escaped.\n"
              << "./universe -s -n --main_delimiter_comma --block_delimiter_semicolon -ia \"tux\""
              << "./universe -s -n -x -ia \"foo bar barr fooo 1337\"\n\n"
              << "Info:\n"
              << "Default delimiter is space!\n"
              << "For -r and -ia input as \"argument\" or 'argument' or in quotes or direct e.g -ia input\n";
}


inline void parseCommandLineArgs(
    int argc,
    char* argv[],
    std::vector<std::string>& ranges,
    std::string& input,
    std::bitset<8>& print_flags,
    bool& is_range,
    bool& is_input,
    char& main_delimiter,
    char& block_delimiter
) {
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
            print_flags.set(0);
        } else if (arg == "-x" || arg == "--utf8") {
            print_flags.set(1);
        } else if (arg == "-t" || arg == "--utf16") {
            print_flags.set(4);
        } else if (arg == "-u" || arg == "--utf32") {
            print_flags.set(5);
        } else if (arg == "-s" || arg == "--symbol") {
            print_flags.set(2);
        } else if (arg == "-n" || arg == "--newline") {
            print_flags.set(3);
        } else if (arg == "-ia" || arg == "--input-arg") {
            is_input = true;
            i++;
            if (i < argc) {
                input = argv[i];
            }
        } else if (arg == "--main_delimiter_space") {
            main_delimiter = ' ';
        } else if (arg == "--main_delimiter_none") {
            main_delimiter = '\0';
        } else if (arg == "--main_delimiter_comma") {
            main_delimiter = ',';
        } else if (arg == "--main_delimiter_semicolon") {
            main_delimiter = ';';
        } else if (arg == "--block_delimiter_space") {
            block_delimiter = ' ';
        } else if (arg == "--block_delimiter_none") {
            block_delimiter = '\0';
        } else if (arg == "--block_delimiter_comma") {
            block_delimiter = ',';
        } else if (arg == "--block_delimiter_semicolon") {
            block_delimiter = ';';
        } else {
            std::cerr << "Error: Invalid argument: " << arg << std::endl;
            exit(1);
        }
    }
}

#endif
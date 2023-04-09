#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <thread>
#include <locale>
#include <codecvt>
#include <regex>
#include <unordered_map>

bool isHex(const std::string& input) {
    return input.substr(0, 2) == "0x" || input.substr(0, 2) == "0X";
}

void printUnicodeRange(const std::vector<std::string>& ranges, bool print_dec, bool print_hex, bool print_sym, bool newline, std::string& output) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    for (const auto& range : ranges) {
        std::vector<std::string> subranges;
        std::istringstream iss(range);
        std::string subrange;
        while (std::getline(iss, subrange, ',')) {
            subranges.push_back(subrange);
        }
        for (const auto& subrange : subranges) {
            std::istringstream iss(subrange);
            std::string start, end;
            std::getline(iss, start, '-');
            std::getline(iss, end);

            int start_num = 0, end_num = 0;
            if (isHex(start)) {
                start_num = std::stoi(start, nullptr, 16);
                end_num = end.empty() ? start_num : std::stoi(end, nullptr, 16);
            } else if (!std::regex_match(start, std::regex("[0-9]+"))) {
                std::cerr << "Error: Invalid input. The input with option -r should be hexadecimal values or code point values." << std::endl;
                return;
            } else {
                start_num = std::stoi(start);
                end_num = end.empty() ? start_num : std::stoi(end);
            }

            for (int char_num = start_num; char_num <= end_num; char_num++) {
                if (print_dec) {
                    output += std::to_string(char_num) + " ";
                }
                if (print_hex) {
                    std::stringstream ss;
                    ss << "0x" << std::hex << char_num << " ";
                    output += ss.str();
                }
                if (print_sym) {
                    // Create a wstring with a single Unicode character
                    std::wstring wstr = { static_cast<wchar_t>(char_num) };
                    // Convert the wstring to UTF-8
                    std::string utf8_str = converter.to_bytes(wstr);
                    // Print the UTF-8 string
                    output += utf8_str + " ";
                }
                if (newline) {
                    output += "\n";
                }
            }
            if (!newline) {
                output += "\n";
            }
        }
    }
}

void printUnicodeString(const std::string& input, bool print_dec, bool print_hex, bool print_sym, bool newline, std::string& output) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wstr = converter.from_bytes(input);
    for (const auto& ch : wstr) {
        int char_num = static_cast<int>(ch);
        if (print_dec) {
            output += std::to_string(char_num) + " ";
        }
        if (print_hex) {
            std::stringstream ss;
            ss << "0x" << std::hex << char_num << " ";
            output += ss.str();
        }
        if (print_sym) {
            // Convert the wstring to UTF-8
            std::string utf8_str = converter.to_bytes(std::wstring(1, ch));
            // Print the UTF-8 string
            output += utf8_str + " ";
        }
        if (newline) {
            output += "\n";
        }
    }
    if (!newline) {
        output += "\n";
    }
}

void printHelpMenu() {
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
              << "./universe -s -n -r \"60-9\"\n"
              << "./universe -s -x -n -r  \"60-90\"\n"
              << "./universe -s -x -d -n -r 60-90\n"
              << "./universe -s -x -d -n -r  \"0x41-0x5A\"\n"
              << "./universe -s -n -x -ia \"foo bar barr fooo 1337\"\n"
              << "  may use \"argument\" for arguments" << std::endl
              << "  The ranges of Unicode numbers to print. Can be specified in the following formats:" << std::endl
              << "  - Single number: e.g. 65 (0x41)" << std::endl
              << "  - Range of numbers: e.g. 65-90 (0x41-0x5A)" << std::endl
              << "  - Comma-separated list of numbers and/or ranges: e.g. 65,67,70-75 (0x41,0x43,0x46-0x4B)" << std::endl
              << "Note: The hexadecimal values shown in parentheses are the code point values." << std::endl
              << "If -ia option is used, the input will be treated as a string instead of Unicode ranges." << std::endl;
}

void parseCommandLineArgs(int argc, char* argv[], std::vector<std::string>& ranges, std::string& input, int& print_flags, bool& newline, bool& is_range, bool& is_input) {
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            printHelpMenu();
            exit(0);
        } else if (arg == "-r" || arg == "--range") {
            is_range = true;
            i++;
            while (i < argc && argv[i][0] != '-') {
                ranges.push_back(argv[i]);
                i++;
            }
            i--;
        } else if (arg == "-d" || arg == "--dnum") {
            print_flags |= 1; // set the first bit
        } else if (arg == "-x" || arg == "--hnum") {
            print_flags |= 2; // set the second bit
        } else if (arg == "-s" || arg == "--symbol") {
            print_flags |= 4; // set the third bit
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

void handleErrors(bool is_range, bool is_input, const std::vector<std::string>& ranges, const std::string& input, int print_flags) {
    if (is_range && is_input) {
        std::cerr << "Error: -r and -ia options are not compatible." << std::endl;
        printHelpMenu();
        exit(1);
    }

    if (!is_range && !is_input) {
        std::cerr << "Error: Either -r or -ia option must be specified." << std::endl;
        printHelpMenu();
        exit(1);
    }

    if (is_range) {
        if (ranges.empty()) {
            std::cerr << "Error: No Unicode range specified." << std::endl;
            exit(1);
        }

        if (!(print_flags & 1) && !(print_flags & 2) && !(print_flags & 4)) {
            // if none of the flags are set, print decimal and hexadecimal values by default
            print_flags |= 1;
            print_flags |= 2;
        }
    } else {
        if (!(print_flags & 1) && !(print_flags & 2) && !(print_flags & 4)) {
            // if none of the flags are set, print symbols by default
            print_flags |= 4;
        }

        if (isHex(input)) {
            std::cerr << "Error: Invalid input. The input with option -ia should be a string." << std::endl;
            printHelpMenu();
            exit(1);
        }
    }
}


int main(int argc, char* argv[]) {
    std::vector<std::string> ranges;
    std::string input;
    int print_flags = 0;
    bool newline = false;
    bool is_range = false;
    bool is_input = false;

    parseCommandLineArgs(argc, argv, ranges, input, print_flags, newline, is_range, is_input);

    handleErrors(is_range, is_input, ranges, input, print_flags);

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
#ifndef UNICODE_RANGE_H
#define UNICODE_RANGE_H

#include <unicode/unistr.h>
#include <unicode/ustream.h>

#include <iostream>
#include <sstream>
#include <locale>
#include <regex>
#include <stdexcept>
#include <vector>
#include <string>


inline bool isHex(const std::string& input) {
    return input.substr(0, 2) == "0x" || input.substr(0, 2) == "0X";
}

inline void printUnicodeRange(const std::vector<std::string>& ranges, bool print_dec, bool print_hex, bool print_sym, bool newline, std::string& output) {

    for (const auto& range : ranges) {
        std::vector<std::string> subranges;
        std::istringstream iss(range);
        std::string subrange;

        while (std::getline(iss, subrange, ',')) {
            subranges.push_back(subrange);
        }

        for (const auto& subrange : subranges) {
            std::istringstream subrangeStream(subrange);
            std::string start, end;
            std::getline(subrangeStream, start, '-');
            std::getline(subrangeStream, end);

            int start_num = 0, end_num = 0;
            try {
                if (isHex(start)) {
                    start_num = std::stoi(start.substr(2), nullptr, 16);
                    end_num = end.empty() ? start_num : std::stoi(end.empty() ? start : end, nullptr, 16);
                } else if (!std::regex_match(start, std::regex("[0-9]+"))) {
                    std::cerr << "Error: Invalid input. The range should contain valid hexadecimal or code point values." << std::endl;
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
                        icu::UnicodeString unicodeChar(static_cast<UChar>(char_num));
                        std::string utf8_str;
                        unicodeChar.toUTF8String(utf8_str);
                        output += utf8_str + " ";
                    }
                    if (newline) {
                        output += "\n";
                    }
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid number format in range." << std::endl;
                return;
            } catch (const std::out_of_range& e) {
                std::cerr << "Error: Number out of range in range." << std::endl;
                return;
            }
            if (!newline) {
                output += "\n";
            }
        }
    }
}

#endif
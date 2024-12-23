#ifndef UNICODE_STRING_H
#define UNICODE_STRING_H

#include <iostream>
#include <stdexcept>
#include <sstream>

inline void printUnicodeString(const std::string& input, uint8_t print_flags, std::string& output) {
    if (input.empty()) {
        return;
    }

    icu::UnicodeString unicodeStr(input.c_str(), "UTF-8");

    if (unicodeStr.isBogus()) {
        throw std::invalid_argument("Input contains invalid UTF-8 sequences.");
    }

    bool print_dec = print_flags & 0x1;
    bool print_hex = print_flags & 0x2;
    bool print_sym = print_flags & 0x4;
    bool newline = print_flags & 0x8;

    output.clear();

    for (int32_t i = 0; i < unicodeStr.length(); ++i) {
        UChar ch = unicodeStr[i];
        int char_num = static_cast<int>(ch);

        if (print_dec) {
            output += std::to_string(char_num);
            if (newline) {
                output += "\n";
            } else {
                output += " ";
            }
        }

        if (print_hex) {
            output += "0x" + std::to_string(char_num);
            if (newline) {
                output += "\n";
            } else {
                output += " ";
            }
        }

        if (print_sym) {
            icu::UnicodeString singleChar(ch);
            std::string utf8_str;
            singleChar.toUTF8String(utf8_str);
            output += utf8_str;
            if (newline) {
                output += "\n";
            } else {
                output += " ";
            }
        }
    }
}
#endif
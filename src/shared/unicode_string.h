#ifndef UNICODE_STRING_H
#define UNICODE_STRING_H

#include <iostream>
#include <stdexcept>
#include <sstream>

inline void printUnicodeString(const std::string& input, uint8_t print_flags, std::string& output, char main_delimiter, char block_delimiter) {
    if (input.empty()) {
        return;
    }

    icu::UnicodeString unicodeStr(input.c_str(), "UTF-8");

    if (unicodeStr.isBogus()) {
        throw std::invalid_argument("Input contains invalid UTF-8 sequences.");
    }

    output.clear();

    for (int32_t i = 0; i < unicodeStr.length(); ++i) {
        UChar ch = unicodeStr[i];
        int32_t char_num = static_cast<int>(ch);

        output += block_delimiter;

        if (print_flags & 0x1) {
            output += std::to_string(char_num);
            output += main_delimiter;
        }

        if (print_flags & 0x2) {
            output += "0x" + std::to_string(char_num);
            output += main_delimiter;
        }

        if (print_flags & 0x4) {
            icu::UnicodeString singleChar(ch);
            std::string utf8_str;
            singleChar.toUTF8String(utf8_str);
            output += utf8_str;
            output += main_delimiter;
        }

        output += block_delimiter;

        if (print_flags & 0x8) {
            output += "\n";
        }
    }
}

#endif
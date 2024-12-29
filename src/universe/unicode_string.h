#ifndef UNICODE_STRING_H
#define UNICODE_STRING_H

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <bitset>

#include "format_unicode_char.h"

inline void printUnicodeString(const std::string& input, const std::bitset<8>& print_flags, std::string& output, char main_delimiter, char block_delimiter) {
    if (input.empty()) {
        return;
    }

    icu::UnicodeString unicodeStr(input.c_str(), "UTF-8");

    if (unicodeStr.isBogus()) {
        throw std::invalid_argument("Input contains invalid UTF-8 sequences.");
    }

    output.clear();

for (int32_t i = 0; i < unicodeStr.length();) {
    UChar32 ch;
    int32_t prevIndex = i;
    U16_NEXT(unicodeStr.getBuffer(), i, unicodeStr.length(), ch);

    if (i == prevIndex) {
        throw std::runtime_error("Infinite loop detected in U16_NEXT processing.");
    }

    output += block_delimiter;

    formatUnicodeChar(ch, print_flags, output, main_delimiter);

    output += block_delimiter;

    if (print_flags.test(3)) {
        output += "\n";
    }
}
}

#endif
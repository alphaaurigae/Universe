#include "unicode_string.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <unicode/unistr.h>

void printUnicodeString(const std::string& input, bool print_dec, bool print_hex, bool print_sym, bool newline, std::string& output) {
    // Create a UnicodeString from the input UTF-8 string
    icu::UnicodeString unicodeStr(input.c_str(), "UTF-8");

    // Handle invalid input errors if necessary
    if (unicodeStr.isBogus()) {
        std::cerr << "Error: Input contains invalid UTF-8 sequences." << std::endl;
        return;
    }

    for (int32_t i = 0; i < unicodeStr.length(); ++i) {
        UChar ch = unicodeStr[i];
        int char_num = static_cast<int>(ch);  // Convert to int for easy formatting
        if (print_dec) {
            output += std::to_string(char_num) + " ";
        }
        if (print_hex) {
            std::stringstream ss;
            ss << "0x" << std::hex << char_num << " ";
            output += ss.str();
        }
        if (print_sym) {
            // Convert the single character (ch) back to UTF-8 string
            icu::UnicodeString singleChar(ch);  // Create a UnicodeString with a single character
            std::string utf8_str;
            singleChar.toUTF8String(utf8_str);  // Convert the single character to UTF-8
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
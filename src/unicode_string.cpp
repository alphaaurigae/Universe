#include "unicode_string.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <unicode/unistr.h>

void printUnicodeString(const std::string& input, bool print_dec, bool print_hex, bool print_sym, bool newline, std::string& output) {

    icu::UnicodeString unicodeStr(input.c_str(), "UTF-8");

    if (unicodeStr.isBogus()) {
        std::cerr << "Error: Input contains invalid UTF-8 sequences." << std::endl;
        return;
    }

    for (int32_t i = 0; i < unicodeStr.length(); ++i) {
        UChar ch = unicodeStr[i];
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
            icu::UnicodeString singleChar(ch);
            std::string utf8_str;
            singleChar.toUTF8String(utf8_str);
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
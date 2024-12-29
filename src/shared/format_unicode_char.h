#ifndef FORMAT_UNICODE_CHAR_H
#define FORMAT_UNICODE_CHAR_H

#include <unicode/unistr.h>
#include <unicode/ustream.h>
#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

inline void formatUnicodeChar(UChar32 ch, const std::bitset<8>& print_flags, std::string& output, char main_delimiter) {
    if (print_flags.test(0)) {
        output += std::to_string(static_cast<int32_t>(ch));
        output += main_delimiter;
    }

    if (print_flags.test(1)) {
        std::ostringstream utf8_stream;
        icu::UnicodeString singleChar(ch);
        std::string utf8_str;
        singleChar.toUTF8String(utf8_str);

        bool first = true;
        for (unsigned char c : utf8_str) {
            if (!first) {
                utf8_stream << "/";
            }
            utf8_stream << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
            first = false;
        }

        output += utf8_stream.str();
        output += main_delimiter;
    }

    if (print_flags.test(4)) {
        std::ostringstream utf16_stream;
        utf16_stream << "0x" << std::hex << std::setw(4) << std::setfill('0') << static_cast<uint16_t>(ch);
        output += utf16_stream.str();
        output += main_delimiter;
    }

    if (print_flags.test(5)) {
        std::ostringstream utf32_stream;
        utf32_stream << "0x" << std::hex << std::setw(8) << std::setfill('0') << static_cast<uint32_t>(ch);
        output += utf32_stream.str();
        output += main_delimiter;
    }

    if (print_flags.test(2)) {
        icu::UnicodeString singleChar(ch);
        std::string utf8_str;
        singleChar.toUTF8String(utf8_str);
        output += utf8_str;
        output += main_delimiter;
    }
}

#endif
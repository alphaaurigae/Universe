#ifndef UNICODE_STRING_UTILS_H
#define UNICODE_STRING_UTILS_H

#include <string>


void printUnicodeString(
    const std::string& input,
    bool print_dec,
    bool print_hex,
    bool print_sym,
    bool newline,
    std::string& output);

#endif
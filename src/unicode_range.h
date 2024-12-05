#ifndef UNICODE_RANGE_HPP
#define UNICODE_RANGE_HPP

#include <string>
#include <vector>


bool isHex(const std::string& input);


void printUnicodeRange(
    const std::vector<std::string>& ranges, 
    bool printDec, 
    bool printHex, 
    bool printSym, 
    bool newLine, 
    std::string& output
);

#endif
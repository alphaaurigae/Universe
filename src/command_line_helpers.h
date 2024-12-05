#ifndef COMMAND_LINE_HELPERS_H
#define COMMAND_LINE_HELPERS_H

#include <vector>
#include <string>


void printHelpMenu();
void parseCommandLineArgs(
    int argc, 
    char* argv[], 
    std::vector<std::string>& ranges, 
    std::string& input, 
    int& printFlags, 
    bool& newLine, 
    bool& isRange, 
    bool& isInput
);

#endif
#!/bin/bash

BOLD='\033[1m'
BRIGHT_WHITE='\033[1;37m'
RESET='\033[0m' 

BUILD_DIR="build"
BIN_DIR="bin"

clean() {
    echo -e "${BOLD}${BRIGHT_WHITE}Cleaning build and bin directories...${RESET}"
    rm -rf ${BUILD_DIR} ${BIN_DIR}
}


configure() {
    echo -e "${BOLD}${BRIGHT_WHITE}Configuring project with cmake...${RESET}"
    mkdir -p ${BUILD_DIR}
    cmake -S . -B ${BUILD_DIR} -DCMAKE_VERBOSE_MAKEFILE=ON
}

build() {
    echo -e "${BOLD}${BRIGHT_WHITE}Building project...${RESET}"
    cmake --build ${BUILD_DIR} --target all -- -j$(nproc) --debug
}

echo -e "${BOLD}${BRIGHT_WHITE}Clean old build${RESET}"
clean

echo -e "${BOLD}${BRIGHT_WHITE}Create build directories and config cmake${RESET}"
configure

echo -e "${BOLD}${BRIGHT_WHITE}Build${RESET}"
build

echo -e "${BOLD}${BRIGHT_WHITE}Unit test shunit2 (unit/)${RESET}"
./shunit2_run.sh



echo ""
echo -e "${BOLD}${BRIGHT_WHITE}See unit test results and check build success ... bin should be in $BIN_DIR e.g bin/universe${RESET}"
echo ""
echo -e "${BOLD}${BRIGHT_WHITE}E.g:${RESET}"
echo ""
echo -e "${BOLD}${BRIGHT_WHITE}bin/universe -s --main_delimiter_none --block_delimiter_semicolon -ia \"Hello Binary\""

# Universe

> String or range to rendered Unicode symbol, decimal, hexadecimal utf-8, utf-16, utf-32 [0x41] [0xe2/0x81/0xb5] [0x2074] [0x000000e2]


## Build

... cmake ...
- ```./build_cmake.sh``` - 1. Tidy build && dirs build; 2. Build; 3. Unittest shunit2
- ```./clean_cmake.sh``` - Tidy build && dirs


## Deps

Test OS ubuntu 24.04
```
- libicu-dev | https://github.com/unicode-org/icu | https://icu.unicode.org/

Optional:
- shunit2 | https://github.com/kward/shunit2

// experimental (commented)
// - nlohmann-json3-dev | https://github.com/nlohmann/json
```


## Usage

- See src/shared/argument_parser.h or bin/universe -h

E.g:
> Range = symbol
```
bin/universe  -s -r '60-62'
 <   =   >  
```
- SEE unit/shunit2test.sh ; src/shared/argument_parser.h


The ranges of Unicode numbers to print can be specified in the following formats:

- Single dec or hex: e.g. 65 [0x41] [0xe2/0x81/0xb5]
- Range of numbers: e.g. 65-90 [0x41-0x43]
- Comma-separated list of numbers and/or ranges: e.g. [65,67,70-75] [0x41,0x43,0x46-0x4B]


If `-ia` option is used, the input will be treated as a string instead of Unicode ranges.


## Json
-  (// experimental (commented))
```
 bin/universe -s -x -n --json  --main_delimiter_semicolon --block_delimiter_comma -ia 'Hello World'
{
    "arguments": "-s -x -n --json --main_delimiter_semicolon --block_delimiter_comma -ia Hello World",
    "input": "Hello World",
    "output": {
        "decimals": "",
        "hexadecimals": "0x48;0x65;0x6c;0x6c;0x6f;0x20;0x57;0x6f;0x72;0x6c;0x64;",
        "symbols": "H;e;l;l;o; ;W;o;r;l;d;"
    }
}
```


## Test (needs update)
```
$ '/home/mmmm/Desktop/Universe/shunit2_run.sh' 
test_print1
TEST PASSED: test_print005
DEBUG: Expected:
 <   =   >   
DEBUG: Got:
 <   =   >   
test_print002

.....


Ran 13 tests.

OK
```


## Todo

- Add input/output format variations?
- decimal output check
- Optimize output formatting?
- Beauty code
- Sec?
- Range input for multi singles, currently not workign for range input e.g "0xc3/0xa2-0xc3/0xa9" ?

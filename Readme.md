# Universe

> utf-8 string or range to rendered Unicode symbol, base-10 decimal, base-16 hexadecimal

## Build

... cmake ...
- ```./build_cmake.sh``` - build
- ```./clean_cmake.sh``` - tidy build && dirs


## Deps

Test OS ubuntu 24.04
```
- libicu-dev | https://github.com/unicode-org/icu | https://icu.unicode.org/

// experimental (commented)
// - nlohmann-json3-dev | https://github.com/nlohmann/json
```

## Usage

```
    std::cout << "Usage: ./universe [OUPUT OPTIONS] [DELIMETER OPTIONS] [INPUT]\n\n"
              << "-h, --help      Show help menu.\n\n"
              << "Output options:\n"
              << "-s, --symbol    Output Rendered Unicode Symbol\n"
              << "-d, --dnum      Output the Unicode code point as a base-10 decimal integer.\n"
              << "-x, --hnum      Output the Unicode code point as a base-16 hexadecimal integer, prefix '0x'.\n"
              << "-n, --newline   Print each output in a new line.\n\n"
              << "Delimeter options:\n"
              << " to separate main output e.g 0x101,e, \n"
              << "--main_delimiter_space   \n"
              << "--main_delimiter_none   \n"
              << "--main_delimiter_comma   \n"
              << "--main_delimiter_semicolon   \n"
              << " to separate blocks output e.g ;0x69,E,;;0x70,F,;\n"
              << "--block_delimiter_space   \n"
              << "--block_delimiter_none  \n"
              << "--block_delimiter_comma   \n"
              << "--block_delimiter_semicolon   \n"
              << "Input:\n"
              << "-r, --range | Input as a range of Unicode code points..\n"
              << "The input can be one or more of the following formats e.g:\n"
              << "- Single base-10 (decimal) integer code point [65]\n"
              << "- Single base-16 (hexadecimal) integer code point [0x41]\n"
              << "- Range of decimal code points [60-90]\n"
              << "- Range of hexadecimal code points [0x41-0x5A]\n"
              << "- Comma-separated list of decimal code points and/or ranges [65,70-75]\n"
              << "- Comma-separated list of hexadecimal code points and/or ranges [0x41,0x46-0x4B]\n"
              << "- Mixed [65,0x67,70-75,0x41-0x5A]\n"
              << "-ia, --input-arg   Input as a UTF-8\n\n"
              << "Sample:\n"
              << "./universe -s -n --main_delimiter_comma --block_delimiter_semicolon -ia \"tux\""
              << "./universe -s -n -r \"60-9\"\n"
              << "./universe -s -x -n -r  \"60-90\"\n"
              << "./universe -s -x -d -n -r 60-90\n"
              << "./universe -s -x -d -n -r  \"0x41-0x5A\"\n"
              << "./universe -s -n -x -ia \"foo bar barr fooo 1337\"\n\n"
              << "Info:" << std::endl
              << "\"argument\" or \'argument\' or arguments as input" << std::endl
              << "Ranges can be specified in the following formats:" << std::endl
              << "Single: e.g. 65" << std::endl
              << "Range: e.g. 0x41-0x5A" << std::endl
              << "Comma-separated list single and range: 0x41,0x43,0x46-0x4B" << std::endl;

```

### Sample output dated after delimiter upgrade
- for -ia ALL CHARACTERS are input unless \ escaped.

- default delimiter is space!

> range = symbol
```
bin/universe  -s -r "60-62"
 <   =   >  
```
> range = symbol .. output to new line
```
./universe -s -n -r "60-62"
 <  
 =  
 >  
```
> range = decimal, hex symbol .. output to new line
```
bin/universe -s -x -d -n -r "60-62"
 60 0x60 <  
 61 0x61 =  
 62 0x62 >  
```
> range with single addition = decimal, hex symbol .. output to new line
```
bin/universe -s -x -d -n -r "0x22,0x41-0x42"
 34 0x34 "  
 65 0x65 A  
 66 0x66 B  

```
> range single only = symbol ... new line , w.o main delimiter
```
bin/universe -s -n --main_delimiter_none -r "49,51,51,55"
 1 
 3 
 3 
 7 
```
> some more variation....
```
bin/universe -s -n --main_delimiter_comma --block_delimiter_semicolon -ia "tux"
;t,;
;u,;
;x,;
```

```
bin/universe  -s -x -d   --main_delimiter_comma --block_delimiter_semicolon -ia "tux A bin A"
;116,0x116,t,;;117,0x117,u,;;120,0x120,x,;;32,0x32, ,;;65,0x65,A,;;32,0x32, ,;;98,0x98,b,;;105,0x105,i,;;110,0x110,n,;;32,0x32, ,;;65,0x65,A,; 

```

```
bin/universe  -s   --main_delimiter_none --block_delimiter_semicolon -ia "Hello Binary"
;H;;e;;l;;l;;o;; ;;B;;i;;n;;a;;r;;y; 
```

```
bin/universe  -s   --main_delimiter_none --block_delimiter_none -ia "cat /dev/null"
cat /dev/null 
```

```
bin/universe  -s   --main_delimiter_space --block_delimiter_space -ia "cat /dev/null | grep dev"
 c   a   t       /   d   e   v   /   n   u   l   l       |       g   r   e   p       d   e   v   
```

```
bin/universe  -d   --main_delimiter_comma --block_delimiter_space -ia "♫   "
 9835,  32,  32,  32, 
```

```
 bin/universe  -d   --main_delimiter_space --block_delimiter_space -ia "\"♫  \\\\ \ \""
 34   9835   32   32   92   92   32   92   32   34   
```

```
bin/universe  -d   --main_delimiter_space --block_delimiter_space -ia "\""
 34   
```


The ranges of Unicode numbers to print can be specified in the following formats:

- Single number: e.g. 65 (0x41)
- Range of numbers: e.g. 65-90 (0x41-0x5A)
- Comma-separated list of numbers and/or ranges: e.g. 65,67,70-75 (0x41,0x43,0x46-0x4B)

Note: The hexadecimal values shown in parentheses are the code point values.

If `-ia` option is used, the input will be treated as a string instead of Unicode ranges.



## json experimental (// experimental (commented))
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
$ shunit2 unit_test/test.sh 
/usr/bin/shunit2: 8: ./unit_test/test.sh: .....: not found
test_print1
test_print2
test_print3
test_print4
test_print5
test_print6
test_print7
test_print8

Ran 8 tests.

OK
```

## Todo

- unit tests need update!
- menu / arg handling  input output
- input format / reading ... e.g file .. json?
- beauty code
- sec?


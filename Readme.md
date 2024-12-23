# Universe

> Universe is a command-line program that allows you to print Unicode characters and their code point values in decimal and/or hexadecimal format. You can specify Unicode ranges or a string as input.


## Build

... cmake ...
- ```./build_cmake.sh``` - build
- ```./clean_cmake.sh``` - tidy build && dirs


## Deps

Test OS ubuntu 24.04
```
- libicu-dev | https://github.com/unicode-org/icu | https://icu.unicode.org/
```

## Usage

```
Usage: ./universe [OPTIONS] [INPUT]\n
-h, --help      Show help menu.\n
Options:
-s, --symbol    Output Rendered Unicode Symbol
-d, --dnum      Output the Unicode code point as a base-10 decimal integer.
-x, --hnum      Output the Unicode code point as a base-16 hexadecimal integer, prefix '0x'.
-n, --newline   Print each output in a new line.\n
Input:
-r, --range     Input as a range of Unicode code points..
                  The input can be one or more of the following formats e.g:
                  - Single base-10 (decimal) integer code point [65]
                  - Single base-16 (hexadecimal) integer code point [0x41]
                  - Range of decimal code points [60-90]
                  - Range of hexadecimal code points [0x41-0x5A]
                  - Comma-separated list of decimal code points and/or ranges [65,70-75]
                  - Comma-separated list of hexadecimal code points and/or ranges [0x41,0x46-0x4B]
                  - Mixed [65,0x67,70-75,0x41-0x5A]
                  -ia, --input-arg   Input as a UTF-8\n
Sample:
./universe -s -n -r \"60-9\"
./universe -s -x -n -r  \"60-90\"
./universe -s -x -d -n -r 60-90
./universe -s -x -d -n -r  \"0x41-0x5A\"
./universe -s -n -x -ia \"foo bar barr fooo 1337\"\n
Info:" << std::endl
\"argument\" or \'argument\' or arguments as input" << std::endl
Ranges can be specified in the following formats:" << std::endl
Single: e.g. 65" << std::endl
Range: e.g. 0x41-0x5A" << std::endl
Comma-separated list single and range: 0x41,0x43,0x46-0x4B" << std::endl;

```
./universe -s -n -r "60-90"
< 
= 
> 
? 
@ 
A 
B 
C 
D 
E 
F 
G 
H 
I 
J 
K 
L 
M 
N 
O 
P 
Q 
R 
S 
T 
U 
V 
W 
X 
Y 
Z 

./universe -s -x -n -r "60-90"
0x3c < 
0x3d = 
0x3e > 
0x3f ? 
0x40 @ 
0x41 A 
0x42 B 
0x43 C 
0x44 D 
0x45 E 
0x46 F 
0x47 G 
0x48 H 
0x49 I 
0x4a J 
0x4b K 
0x4c L 
0x4d M 
0x4e N 
0x4f O 
0x50 P 
0x51 Q 
0x52 R 
0x53 S 
0x54 T 
0x55 U 
0x56 V 
0x57 W 
0x58 X 
0x59 Y 
0x5a Z 

./universe -s -x -d -n -r 60-90
60 0x3c < 
61 0x3d = 
62 0x3e > 
63 0x3f ? 
64 0x40 @ 
65 0x41 A 
66 0x42 B 
67 0x43 C 
68 0x44 D 
69 0x45 E 
70 0x46 F 
71 0x47 G 
72 0x48 H 
73 0x49 I 
74 0x4a J 
75 0x4b K 
76 0x4c L 
77 0x4d M 
78 0x4e N 
79 0x4f O 
80 0x50 P 
81 0x51 Q 
82 0x52 R 
83 0x53 S 
84 0x54 T 
85 0x55 U 
86 0x56 V 
87 0x57 W 
88 0x58 X 
89 0x59 Y 
90 0x5a Z 

./universe -s -x -d -n -r "0x41-0x5A"
65 0x41 A 
66 0x42 B 
67 0x43 C 
68 0x44 D 
69 0x45 E 
70 0x46 F 
71 0x47 G 
72 0x48 H 
73 0x49 I 
74 0x4a J 
75 0x4b K 
76 0x4c L 
77 0x4d M 
78 0x4e N 
79 0x4f O 
80 0x50 P 
81 0x51 Q 
82 0x52 R 
83 0x53 S 
84 0x54 T 
85 0x55 U 
86 0x56 V 
87 0x57 W 
88 0x58 X 
89 0x59 Y 
90 0x5a Z 

 ./universe -s -n -x -ia "foo bar barr fooo 1337"
0x66 f 
0x6f o 
0x6f o 
0x20   
0x62 b 
0x61 a 
0x72 r 
0x20   
0x62 b 
0x61 a 
0x72 r 
0x72 r 
0x20   
0x66 f 
0x6f o 
0x6f o 
0x6f o 
0x20   
0x31 1 
0x33 3 
0x33 3 
0x37 7 

./universe -s -x -ia "foo bar barr fooo 1337"
0x66 f 0x6f o 0x6f o 0x20   0x62 b 0x61 a 0x72 r 0x20   0x62 b 0x61 a 0x72 r 0x72 r 0x20   0x66 f 0x6f o 0x6f o 0x6f o 0x20   0x31 1 0x33 3 0x33 3 0x37 7 
```

The ranges of Unicode numbers to print can be specified in the following formats:

- Single number: e.g. 65 (0x41)
- Range of numbers: e.g. 65-90 (0x41-0x5A)
- Comma-separated list of numbers and/or ranges: e.g. 65,67,70-75 (0x41,0x43,0x46-0x4B)

Note: The hexadecimal values shown in parentheses are the code point values.

If `-ia` option is used, the input will be treated as a string instead of Unicode ranges.



## Test
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
- punycode
- menu / arg handling
- input format / reading ... e.g file .. json?
- beauty code
- sec?
- improve shunit?

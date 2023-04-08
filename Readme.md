# Universe

> Universe is a command-line program that allows you to print Unicode characters and their code point values in decimal and/or hexadecimal format. You can specify Unicode ranges or a string as input.

## Usage

```
./universe [OPTIONS] -r range1 range2 ... OR -ia input
```

### Options

- `-h`, `--help`: Show help menu.
- `-r`, `--range`: Treat input as a range of Unicode numbers.
- `-s`, `--symbol`: Print symbol of each character.
- `-d`, `--dnum`: Print decimal code point value of each character.
- `-x`, `--hnum`: Print hexadecimal code point value of each character.
- `-n`, `--newline`: Print each output in a new line.
- `-ia`, `--input-arg`: Treat input as a string.

### Examples

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

## How to Build

1. Clone the repository: `git clone https://github.com/kevinjl321/universe.git`
2. Change directory: `cd universe`
3. Build the program: `make`
4. Run the program: `./universe [OPTIONS] -r range1 range2 ... OR -ia input`


## Dependencies

This program requires C++11 or later and the following standard libraries:

- iostream
- string
- vector
- cstdlib
- sstream
- algorithm
- thread
- locale
- codecvt
- regex
- unordered_map
# Turing Machine Emulator
## Build
Make sure that you have installed CMake at least version 3.20

Configure project:
```shell
cmake -B build -DCMAKE_BUILD_TYPE="Build type" -G "Generator name"
```
"Build type" is one of the following:
- Debug
- Release
- RelWithDebInfo
- MinSizeRel

"Generator name" is generator you would like to use.

Build and install project:
```shell  
cmake --build build && cmake --install build
```
Now you can use it from terminal:
```shell
turing-machine "config".csv
```
## Usage
Program must be launched with one command line argument which is the configuration file name. Configuration file is simple CSV file that can be opened with any spreadsheet software such as LibreOffice Calc. This file contains:
- Initial tape configuration
- Initial cursor position
- Alphabet of machine
- States of machine
- Commands consisting of three components:
	+ Alpha from machine alphabet to write to the current cell
	+ Action the head must perform:
		* Move left ('L')
		* Move right ('R')
		* Halt the machine ('H')
		* Do nothing (any other value)
	+ State of the head as command is performed

Example configuration file is given in root directory of the repository:
```
 -BAAABBABBBAAABABBAAA- | MR 
 Q ,   ,   , - |   ,   , A |   ,   , B |
 1 ,   , R , 2 |   ,   ,   |   ,   ,   |
 2 ,   , H ,   | B , R ,   | A , R ,   |
```
First line must containt initial tape configuration (first cell) and initial cursor position (second cell):
- Left ('L')
- Right ('R')
- Middle left ('ML')
- Middle right ('MR')

Second line describes machine's alphabet. Emulator will consider every third cell starting with 4th one. Characters must be destinct otherwise the program will return an error.

All subsequent lines contain machine states and the commands, each is three cells long.

During machine running emulator can append tape in one of two directions (left or right) if cursor is about to go outside of existing tape range.

Output value is machine tape after successful machine execution or an error if something has gone wrong.
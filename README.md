# Single-Row-Height Cell Legalization using Abacus Method

## Overview

This project implements a single-row-height cell legalization algorithm using the abacus method. The algorithm is designed to efficiently legalize cell placements in a single row, ensuring that all cells on the row are properly aligned and do not overlap. The implementation is based on the principles outlined in the paper "Abacus: Fast Legalization of Standard Cell Circuits with Minimal Movement" by Peter Spindler, Ulf Schlichtmann, and Frank M. Johannes. 2008.

## Course Information

- Course: Software Development for Electronic Design Automation
- Instructor: Prof. Shao-Yun Fang
- Project: Single-Row-Height Cell Legalization

## Program Architecture

```
/root
│
├── /include
│   ├── Cell.hpp
│   ├── Cluster.hpp
│   ├── Layer.hpp
│   ├── Orientation.hpp
│   └── Row.hpp
│
├── /src
│   ├── Cluster.cpp
│   ├── Layer.hpp
│   ├── Row.hpp
│   └── main.cpp
│
├── Makefile
└── README.md
```

## Development Tools

- Programming Language:
  - Utilized: C++
  - Standard: C++17
  - Compiler: g++
- Development Environment:
  - Operating System: Ubuntu 24.04.1
  - Containerization: Docker
  - Local Platform: macOS
- Compilation Script:
  - Makefile

## Prerequisites

- Ensure that all dependencies required for compiling C++ code are installed.

## Compilation Process

1. Navigate to the directory containing the Makefile by using `cd <path_to_directory>`.
2. Execute the compilation by entering `make`.

## Usage

1. Change directory to the location where the executable 'legalizer' is present using `cd <path_to_directory>`.
2. Run the program using the following command (replace the contents of "[]" with the corresponding numerical values or textual arguments; **the input parameter ⍺ directly influences the algorithm's outcome**):

```
./legalizer [cell width (in terms of sites)] [alpha] [input file name] [output file name]
```

3. The program will produce an output file named [output file name] and display the following information on the standard output:

```
Execution time: [minutes] min and [seconds] sec
```

4. (Optional) Execute `make clean` to remove all object files and the executable.

**Notes**:

- Further details regarding the underlying data structures and algorithms will not be provided in this document.
- For any inquiries, please contact josker6969@gmail.com.

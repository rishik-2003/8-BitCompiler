# 8-Bit Compiler

## Overview
This project is an 8-bit compiler written in C++. It processes a simple language to generate assembly-like instructions, supporting basic operations such as addition, subtraction, multiplication, and logical operations.

## Features
- Supports variable assignment and arithmetic operations
- Logical operations: AND, OR
- Reads source code from a text file
- Outputs assembly instructions based on the input code

## Files
- `main.cpp`: Entry point for the compiler, reads source code and invokes compilation.
- `lexer.cpp`: Contains the lexer functionality (currently a placeholder).
- `parser.cpp`: Implements the compilation logic, translating the source code to assembly instructions.
- `compiler.h`: Header file containing function declarations and includes.
- `source.txt`: Example source code file (create your own based on the supported syntax).

## Compilation
To compile the project, use the following command in the terminal:

```bash
g++ -o main main.cpp lexer.cpp parser.cpp

./main input.txt
